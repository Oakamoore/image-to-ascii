# image-to-ascii

[![License](https://img.shields.io/badge/License-MIT-green)](https://github.com/Oakamoore/image-to-ascii/blob/main/LICENSE) [![stb_image](https://img.shields.io/badge/stb__image-2.30-orange)](https://github.com/nothings/stb/blob/master/stb_image.h) [![stb_image_write](https://img.shields.io/badge/stb__image__write_-1.16-orange)](https://github.com/nothings/stb/blob/master/stb_image_write.h) [![stb_image_resize2](https://img.shields.io/badge/stb__image__resize2_-2.07-orange)](https://github.com/nothings/stb/blob/master/stb_image_resize2.h) ![Cross Platform](https://img.shields.io/badge/Cross_Platform-blue)

## Overview

A command line tool for converting images to ASCII art. 

<p float="left">
<img src="https://private-user-images.githubusercontent.com/57583938/337928545-6173f5c8-95ff-4457-bd50-27dfef9e2f12.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MTc4NzY0OTgsIm5iZiI6MTcxNzg3NjE5OCwicGF0aCI6Ii81NzU4MzkzOC8zMzc5Mjg1NDUtNjE3M2Y1YzgtOTVmZi00NDU3LWJkNTAtMjdkZmVmOWUyZjEyLnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNDA2MDglMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjQwNjA4VDE5NDk1OFomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPTQyM2U0NTZiYTQyMDNiMzllNmRjNDBlMDNlOTExOTZhMTdhZDQ0OWFkZjJjZTIxZWQ4ZDMxMzQ0NGNjOTc5M2UmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0JmFjdG9yX2lkPTAma2V5X2lkPTAmcmVwb19pZD0wIn0.UCJJe1i8u_bHGy1JEA37Jfgv5hH1jlaUvylRd2CNgxg" width="200">
<img src="https://private-user-images.githubusercontent.com/57583938/337928551-442308fa-4093-4eab-8d5a-b6035bcd26bb.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MTc4NzY0OTgsIm5iZiI6MTcxNzg3NjE5OCwicGF0aCI6Ii81NzU4MzkzOC8zMzc5Mjg1NTEtNDQyMzA4ZmEtNDA5My00ZWFiLThkNWEtYjYwMzViY2QyNmJiLnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNDA2MDglMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjQwNjA4VDE5NDk1OFomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPWJhZjQ2ODhkYmQ0MDMyNThiNzQ2Zjg0YWE1NGE1OTU1YmNjZGFlOTliMmU4NWIwNTVhODNjZmNmZmE5MWEzYWQmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0JmFjdG9yX2lkPTAma2V5X2lkPTAmcmVwb19pZD0wIn0.idOKJdiBt3ZknEGFNtVcbP_s2rqR3gIC1yKKty3yJMY" width="200">
<img src="https://private-user-images.githubusercontent.com/57583938/337928553-35b3eb4f-5aae-43a6-853f-7db29dea0dec.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MTc4NzY0OTgsIm5iZiI6MTcxNzg3NjE5OCwicGF0aCI6Ii81NzU4MzkzOC8zMzc5Mjg1NTMtMzViM2ViNGYtNWFhZS00M2E2LTg1M2YtN2RiMjlkZWEwZGVjLnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNDA2MDglMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjQwNjA4VDE5NDk1OFomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPTg1N2NjYWFhN2Q0M2RkZjc5OGRjNDJjNTI0YmQ3MWM2ODE1ZjU1NTg4YzFjOGU5MTI4NTNjM2NjZWJlNDJlNTgmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0JmFjdG9yX2lkPTAma2V5X2lkPTAmcmVwb19pZD0wIn0.oTuhr3rizDZELZeE5HIGE89E6q-RNk74M75cSUEj1iI" width="200">
<img src="https://private-user-images.githubusercontent.com/57583938/337928556-4a4e2e42-abbc-450e-b4f0-a58a1a5915b6.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MTc4NzY0OTgsIm5iZiI6MTcxNzg3NjE5OCwicGF0aCI6Ii81NzU4MzkzOC8zMzc5Mjg1NTYtNGE0ZTJlNDItYWJiYy00NTBlLWI0ZjAtYTU4YTFhNTkxNWI2LnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNDA2MDglMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjQwNjA4VDE5NDk1OFomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPTJhY2Q0MGVhODdlZGViMzUxMzc1YTk3N2RkYmExMDVlZmZiZDUzM2ZkMDkzZmNmMDUzNDRkODNhNmQwYWRiMDcmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0JmFjdG9yX2lkPTAma2V5X2lkPTAmcmVwb19pZD0wIn0.fqy-1za16P2pqNBatymkJoGAZbMPcUfyHAcLnfVsb3E" width="200">
</p>

## Installation

1. Clone this project

```shell
git clone https://github.com/Oakamoore/cli-pong.git
```

2. Step into the repository

```shell
cd cli-pong
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

If the arguments provided are valid image names, the output directory will be populated as follows:

```shell
## Place images to be converted here
/input
	apple.png
	banana.png

# Creates a directory based on the image's file name
# Holds the intermediate conversion steps (defaulted to 'png')
/output	
	/apple
		apple_resized.png
		apple_greyscale.png
		apple_ascii.txt
	/banana
		banana_resized.png
		banana_greyscale.png
		banana_ascii.txt
```

For subsequent uses the first step can be skipped, so long as the `intput/` directory exists. 

## Known Issues

#### Secure Functions

MSVC defaults to it's implementation of secure `_s` functions (that are poorly supported).

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