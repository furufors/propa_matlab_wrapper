#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "propa.h"

typedef double (WINAPI * DllCalltemperature)  (double lat,double lon);

int main(int argc, char *argv[]) {
  HMODULE propaDLL;
  DllCalltemperature temperature;

  propaDLL = LoadLibrary("propa.dll");
  temperature = (DllCalltemperature) GetProcAddress(propaDLL,"_temperature@16");

  if (propaDLL == NULL) {
    printf("Problem while loading the PROPA DLL\n");
    return EXIT_FAILURE;
  }

  if (argc == 3) {
    double lat, lon;

    sscanf(argv[1], "%lf", &lat);
    sscanf(argv[2], "%lf", &lon);

    // Temperature
    printf("%f\n", temperature(lat,lon));

    FreeLibrary(propaDLL);

    return EXIT_SUCCESS;
  } else {
    printf("Wrong number of arguments %i", argc-1);
    return EXIT_FAILURE;
  }
}
