#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "propa.h"

typedef double (WINAPI * DllCalltemperature)  (double lat,double lon);
typedef double (WINAPI * DllCallIWVC) (double lat, double lon, double p) ;
typedef double (WINAPI * DllCallSWVD) (double lat, double lon);
typedef double (WINAPI * DllCallgaseous_attenuation_exc)(double f,double E,double Temp, double WVC, double ro);

int main(int argc, char *argv[]) {
  HMODULE propaDLL;
  DllCalltemperature temperature;
  DllCallIWVC IWVC;
  DllCallSWVD SWVD;
  DllCallgaseous_attenuation_exc gaseous_attenuation_exc;

  propaDLL = LoadLibrary("propa.dll");
  temperature = (DllCalltemperature) GetProcAddress(propaDLL,"_temperature@16");
  IWVC = (DllCallIWVC) GetProcAddress(propaDLL,"_IWVC@24");
  SWVD = (DllCallSWVD) GetProcAddress(propaDLL,"_SWVD@16");
  gaseous_attenuation_exc = (DllCallgaseous_attenuation_exc) GetProcAddress(propaDLL,"_gaseous_attenuation_exc@40");

  if (propaDLL == NULL) {
    printf("Problem while loading the PROPA DLL\n");
    return EXIT_FAILURE;
  }

  if (argc == 6) {
    double lat, lon, f, E, p;
    double Temp, ro, WVC;
    double Agaseous;

    sscanf(argv[1], "%lf", &lat);
    sscanf(argv[2], "%lf", &lon);
    sscanf(argv[3], "%lf", &f);
    sscanf(argv[4], "%lf", &E);
    sscanf(argv[5], "%lf", &p);

    // Intermediate parameters computation
    Temp = temperature(lat,lon);
    ro = SWVD(lat,lon);
    WVC = IWVC(lat,lon,p);

    // GASEOUS ATTENUATION EXCEEDED FOR p% OF THE TIME
    printf("%f\n", gaseous_attenuation_exc(f,E,Temp,WVC,ro));

    FreeLibrary(propaDLL);
    return EXIT_SUCCESS;
  } else {
    printf("Wrong number of arguments %i", argc-1);
    FreeLibrary(propaDLL);
    return EXIT_FAILURE;
  }
}
