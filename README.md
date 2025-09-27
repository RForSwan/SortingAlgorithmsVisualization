# SortingAlgorithmsVisualization

## Description :
Full tool to compare visually and with statistics the different sorting algorithms

gcc : v11.4.0
Ubuntu : 22.04.2

## Compilation :
```bash
gcc -o SAV.out *.c -lSDL2 -lSDL2_ttf -lSDL2_gfx -Werror && ./SAV.out
```
## Development guidelines :
If you want to write code to continue the project, please follow the current development guidelines :
### For header files :
* refrain from using ``#pragma once``
* if you add a header of your own, please add it to ``settings.h``
* do all the definitions, structs, enums, ... at the top and finish by the functions detailed using doxygen

### For C files :
* import ``settings.h`` to have all the necessary files 
* 