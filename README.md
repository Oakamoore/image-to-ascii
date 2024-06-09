# image-to-ascii

[![License](https://img.shields.io/badge/License-MIT-green)](https://github.com/Oakamoore/image-to-ascii/blob/main/LICENSE) [![stb_image](https://img.shields.io/badge/stb__image-2.29-orange)](https://github.com/nothings/stb/blob/master/stb_image.h) [![stb_image_write](https://img.shields.io/badge/stb__image__write_-1.16-orange)](https://github.com/nothings/stb/blob/master/stb_image_write.h) [![stb_image_resize2](https://img.shields.io/badge/stb__image__resize2_-2.06-orange)](https://github.com/nothings/stb/blob/master/stb_image_resize2.h) ![Cross Platform](https://img.shields.io/badge/Cross_Platform-blue)

## Overview

A command line tool for converting images to ASCII art. 

<p float="left">
<img src="https://github.com/Oakamoore/image-to-ascii/assets/57583938/3e4af5a1-4ef3-44ec-9dd8-bf10e5fa0457" width="200">
<img src="https://github.com/Oakamoore/image-to-ascii/assets/57583938/cacd0242-62b2-4419-a0b0-77c29994fd9b" width="200">
<img src="https://github.com/Oakamoore/image-to-ascii/assets/57583938/3e497a3f-3e8b-4171-8443-4b26302b060f" width="200">
<img src="https://github.com/Oakamoore/image-to-ascii/assets/57583938/77d348e1-f575-4b11-af7d-cca551123b22" width="200">
</p>

## Installation

1. Clone this project

```shell
git clone https://github.com/Oakamoore/image-to-ascii.git
```

2. Step into the repository

```shell
cd image-to-ascii
```

3. Build the project using CMake

```shell
cmake -S . -B build
cmake --build build
```

## Usage 

Once the project is built, navigate to the newly created build directory, `image-to-ascii/build/Debug` (where the executable is located) 

1. Run the program once, to create the `input/` and `output/` directories (if they do not already exist):

```shell
./image-to-ascii
```

2. Populate the `input/` directory with the images to be converted

3. Run the program again, this time supplying command line arguments - in the form of the names of images with their file extensions:

```shell
./image-to-ascii apple.png banana.png 
```

If the arguments provided are valid image names, the `output/` directory will be populated as follows:

```shell
# Place images to be converted here
input/
	apple.png
	banana.png

# Creates a directory based on the image's file name
# Holds the intermediate conversion steps (defaulted to 'png')
output/	
	apple/
		apple_resized.png
		apple_greyscale.png
		apple_ascii.txt
	banana/
		banana_resized.png
		banana_greyscale.png
		banana_ascii.txt
```

For subsequent uses the first step can be skipped, so long as the `intput/` directory exists. 

## Known Issues

#### Secure Functions

MSVC defaults to its implementation of secure `_s` functions (that are poorly supported).

`stb_image_write.h` (as of [this commit](https://github.com/nothings/stb/commit/a5e40739ac096711e6640babdf3038c8203f9978) ) defines `__STDC_LIB_EXT1__` to determine whether or not to use these `_s` functions, though certain versions of Visual Studio require `__STDC_WANT_SECURE_LIB__` to function. 

This project's workaround is defining `_CRT_SECURE_NO_WARNINGS` in [`image.cpp`](https://github.com/Oakamoore/image-to-ascii/blob/main/src/image.cpp), to suppress deprecation warnings, in favour of the non `_s` functions. 

#### Warnings as Errors

This project was built with [Visual Studio](https://visualstudio.microsoft.com/), and has both [**Warnings as Errors**](https://learn.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level?view=msvc-170) (`/WX`) and [**Warning Level Four**](https://learn.microsoft.com/en-us/cpp/build/reference/compiler-option-warning-level?view=msvc-170) (`/W4`) enabled. This project also makes use of the [stb](https://github.com/nothings/stb) image processing header libraries, which don't compile cleanly with `/W4`. 

This project's solution is wrapping the offending third party header library includes in [`#pragma warning(push, n)`](https://learn.microsoft.com/en-us/cpp/preprocessor/warning?view=msvc-170#push-and-pop) and [`#pragma warning(pop)`](https://learn.microsoft.com/en-us/cpp/preprocessor/warning?view=msvc-170#push-and-pop) to temporarily disable warnings:

```cpp
#pragma warning(push, 0)
#include "stb_image.h"
#include "stb_image_write.h"
#include "stb_image_resize2.h"
#pragma warning(pop)
```

This is of course implementation defined, so not all compilers will support this. If this doesn't work for your specific compiler, consider temporarily disabling your equivalent of `/W4` when using this project.