propa_matlab_wrapper
====================
**The propagation dynamic linked library**, by Frédéric Lacoste, provides functionality to predict some propagation parameters based on the ITU-R recommendations.

Some matlab versions won't accept the propa.dll file found at: https://logiciels.cnes.fr/en/content/propa.
To quickly solve this, these minimalistic wrappers provide system calls for library's functions. This workaround is possible if your system can link against the library but Matlab can't.

The dll-file is not provided in this repository and should be downloaded from the above address.


## Compiling
Provided you have got GCC installed and that the propa.dll file is located in the working directory, compile with:
```
gcc -o filename filename.c -L./ -lpropa -lm
```


## Usage
If the executables as well as the matlab functions are in your Matlab working directory, you can call the functions like any other matlab-function.

**Function arguments**
```
lat = Latitude (°)
lon = Logitude (°)
hs  = Earth station altitude (km)
E   = Link elevation angle (rad)
f   = Link frequency (GHz)
to  = Tilt polarization angle (°)
D   = Earth station antenna diameter (m)
eta = Earth station antenna efficiency
p   = Percentage of the time (%)
```

**Function outputs**
```
cloud_attenuation -> for the given percentage the attenuation exceedes this value (db)
gaseous_attenuation -> (dB)
gaseous_attenuation_exc -> for the given percentage the attenuation exceedes this value (dB)
rain_attenuation -> for the given percentage the attenuation exceedes this value (dB)
rain_height -> ??
rain_intensity -> mm/h?
scintillation -> for the given percentage the attenuation exceedes this value (dB)
temperature -> (K)
```

## Further documentation
Users manual:
http://logiciels.cnes.fr/PROPA/en/usermanual.pdf (link broken)

Validation tables:
http://logiciels.cnes.fr/PROPA/en/validation_examples.pdf (link broken)
