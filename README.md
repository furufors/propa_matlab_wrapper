propa_matlab_wrapper
====================

Since some matlab versions won't accept the propa.dll file found at: http://logiciels.cnes.fr/PROPA/en/logiciel.htm I wrote minimalistic wrappers to provide system calls for the functions provided by the library.

## Compiling
Provided you have got GCC installed and that the propa.dll file is located in the working directory, compile with:
```
gcc -o filename filename.c -L./ -lpropa -lm
```

## Usage
If the executables as well as the matlab functions are in your Matlab working directory, you can call the functions like any other matlab-function.