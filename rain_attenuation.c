#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "propa.h"

typedef double (WINAPI * DllCallrain_height) (double lat, double lon);
typedef double (WINAPI * DllCallrain_intensity) (double lat, double lon, double p);
typedef double (WINAPI * DllCallrain_attenuation) (double lat,double f,double E,double p,double hs,double hr,double R001, double to);

int main(int argc, char *argv[]) {
  HMODULE propaDLL;
  DllCallrain_height rain_height;
  DllCallrain_intensity rain_intensity;
  DllCallrain_attenuation rain_attenuation;

  propaDLL = LoadLibrary("propa.dll");
  rain_height = (DllCallrain_height) GetProcAddress(propaDLL,"_rain_height@16");
  rain_intensity = (DllCallrain_intensity) GetProcAddress(propaDLL,"_rain_intensity@24");
  rain_attenuation = (DllCallrain_attenuation) GetProcAddress(propaDLL,"_rain_attenuation@64");

  if (propaDLL == NULL) {
    printf("Problem while loading the PROPA DLL\n");
    return EXIT_FAILURE;
  }

  if (argc == 8) {
    double lat,lon,f,E,p,hs,R001,to;
    double hr;

    sscanf(argv[1], "%lf", &lat);
    sscanf(argv[2], "%lf", &lon);
    sscanf(argv[3], "%lf", &f);
    sscanf(argv[4], "%lf", &E);
    sscanf(argv[5], "%lf", &p);
    sscanf(argv[6], "%lf", &hs);
    sscanf(argv[7], "%lf", &to);

    // INTERMEDIATE PARAMETERS
    hr = rain_height(lat,lon);
    R001 = rain_intensity(lat,lon,0.01);
    
    // RAIN ATTENUATION EXCEEDED FOR p% OF THE TIME
    printf("%f", rain_attenuation(lat,f,E,p,hs,hr,R001,to));

    FreeLibrary(propaDLL);
    return EXIT_SUCCESS;
  } else {
    printf("Wrong number of arguments %i", argc-1);
    FreeLibrary(propaDLL);
    return EXIT_FAILURE;
  }
}
