#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "propa.h"

// Compile with gcc -o fileName fileName.c -L./ -lpropa -lm

typedef double (WINAPI * DllCallrain_height) (double lat, double lon);

int main(int argc, char *argv[]) {
  HMODULE propaDLL;
  DllCallrain_height rain_height;

  propaDLL = LoadLibrary("propa.dll");
  rain_height = (DllCallrain_height) GetProcAddress(propaDLL,"_rain_height@16");

  if (propaDLL == NULL) {
    printf("Problem while loading the PROPA DLL\n");
    return EXIT_FAILURE;
  }

  if (argc == 3) {
    double lat, lon;

    sscanf(argv[1], "%lf", &lat);
    sscanf(argv[2], "%lf", &lon);

    // RAIN HEIGHT
    printf("%f\n", rain_height(lat,lon));

    FreeLibrary(propaDLL);
    return EXIT_SUCCESS;
  } else {
    printf("Wrong number of arguments %i", argc-1);
    FreeLibrary(propaDLL);
    return EXIT_FAILURE;
  }
}
