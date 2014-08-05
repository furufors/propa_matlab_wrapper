#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "propa.h"

typedef double (WINAPI * DllCallLWCC) (double lat, double lon, double p);
typedef double (WINAPI * DllCallcloud_attenuation) (double f,double E,double L);

int main(int argc, char *argv[]) {
  HMODULE propaDLL;
  DllCallLWCC LWCC;
  DllCallcloud_attenuation cloud_attenuation;

  propaDLL = LoadLibrary("propa.dll");
  LWCC = (DllCallLWCC) GetProcAddress(propaDLL,"_LWCC@24");
  cloud_attenuation = (DllCallcloud_attenuation) GetProcAddress(propaDLL,"_cloud_attenuation@24");

  if (propaDLL == NULL) {
    printf("Problem while loading the PROPA DLL\n");
    return EXIT_FAILURE;
  }

  if (argc == 6) {
    double lat, lon, f, E, p;
    double LWC;
    double Aclouds;

    sscanf(argv[1], "%lf", &lat);
    sscanf(argv[2], "%lf", &lon);
    sscanf(argv[3], "%lf", &f);
    sscanf(argv[4], "%lf", &E);
    sscanf(argv[5], "%lf", &p);
    // Intermediate parameters computation
    LWC = LWCC(lat,lon,p);

    // CLOUD ATTENUATION EXCEEDED FOR p% OF THE TIME
    printf("%f", cloud_attenuation(f,E,LWC));

    FreeLibrary(propaDLL);
    return EXIT_SUCCESS;
  } else {
    printf("Wrong number of arguments %i", argc-1);
    FreeLibrary(propaDLL);
    return EXIT_FAILURE;
  }
}
