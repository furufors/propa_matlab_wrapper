#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "propa.h"

typedef double (WINAPI * DllCalltemperature)  (double lat,double lon);
typedef double (WINAPI * DllCallSWVD) (double lat, double lon);
typedef double (WINAPI * DllCallgaseous_attenuation) (double f,double E,double Temp, double ro);

int main(int argc, char *argv[]) {
  HMODULE propaDLL;
  DllCalltemperature temperature;
  DllCallSWVD SWVD;
  DllCallgaseous_attenuation gaseous_attenuation;

  propaDLL = LoadLibrary("propa.dll");
  temperature = (DllCalltemperature) GetProcAddress(propaDLL,"_temperature@16");
  SWVD = (DllCallSWVD) GetProcAddress(propaDLL,"_SWVD@16");
  gaseous_attenuation = (DllCallgaseous_attenuation) GetProcAddress(propaDLL,"_gaseous_attenuation@32");

  if (propaDLL == NULL) {
    printf("Problem while loading the PROPA DLL\n");
    return EXIT_FAILURE;
  }

  if (argc == 5) {
    double lat, lon, f, E;
    double Temp, ro;
    double Agaseous;

    sscanf(argv[1], "%lf", &lat);
    sscanf(argv[2], "%lf", &lon);
    sscanf(argv[3], "%lf", &f);
    sscanf(argv[4], "%lf", &E);
    
    // Intermediate parameters computation
    Temp = temperature(lat,lon);
    ro = SWVD(lat,lon);

    // GASEOUS ATTENUATION
    printf("%f\n", gaseous_attenuation(f,E,Temp,ro));

    FreeLibrary(propaDLL);
    return EXIT_SUCCESS;
  } else {
    printf("Wrong number of arguments %i", argc-1);
    FreeLibrary(propaDLL);
    return EXIT_FAILURE;
  }
}
