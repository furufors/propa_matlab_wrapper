#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "propa.h"

typedef double (WINAPI * DllCallNWET) (double lat, double lon);
typedef double (WINAPI * DllCallscintillation) (double Nwet, double f,double E,double p,double hs,double eta, double D);

int main(int argc, char *argv[]) {
  HMODULE propaDLL;
  DllCallNWET NWET;
  DllCallscintillation scintillation;

  propaDLL = LoadLibrary("propa.dll");
  NWET = (DllCallNWET) GetProcAddress(propaDLL,"_NWET@16");
  scintillation = (DllCallscintillation) GetProcAddress(propaDLL,"_scintillation@56");

  if (propaDLL == NULL) {
    printf("Problem while loading the PROPA DLL\n");
    return EXIT_FAILURE;
  }

  if (argc == 9) {
    double lat, lon, f, E, p, hs, eta, D;
    double Nwet;

    sscanf(argv[1], "%lf", &lat);
    sscanf(argv[2], "%lf", &lon);
    sscanf(argv[3], "%lf", &f);
    sscanf(argv[4], "%lf", &E);
    sscanf(argv[5], "%lf", &p);
    sscanf(argv[6], "%lf", &hs);
    sscanf(argv[7], "%lf", &eta);
    sscanf(argv[8], "%lf", &D);

    // Intermediate parameters computation
    Nwet = NWET(lat,lon);

    // IMPAIRMENT DUE TO SCINTILLATION EXCEEDED FOR p% OF THE TIME
    printf("%f", scintillation(Nwet,f,E,p,hs,eta,D));

    FreeLibrary(propaDLL);
    return EXIT_SUCCESS;
  } else {
    printf("Wrong number of arguments %i", argc-1);
    FreeLibrary(propaDLL);
    return EXIT_FAILURE;
  }
}
