#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "propa.h"

typedef double (WINAPI * DllCallrain_intensity) (double lat, double lon, double p);

int main(int argc, char *argv[]) {
  HMODULE propaDLL;
  DllCallrain_intensity rain_intensity;


  propaDLL = LoadLibrary("propa.dll");
  rain_intensity = (DllCallrain_intensity) GetProcAddress(propaDLL,"_rain_intensity@24");

  if (propaDLL == NULL) {
    printf("Problem while loading the PROPA DLL\n");
    return EXIT_FAILURE;
  }

  if (argc == 4) {
    double lat, lon, p;

    sscanf(argv[1], "%lf", &lat);
    sscanf(argv[2], "%lf", &lon);
    sscanf(argv[3], "%lf", &p);

    // Temperature
    printf("%f\n", rain_intensity(lat,lon,p));

    FreeLibrary(propaDLL);
    return EXIT_SUCCESS;
  } else {
    printf("Wrong number of arguments %i", argc-1);
    FreeLibrary(propaDLL);
    return EXIT_FAILURE;
  }
}
