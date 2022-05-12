# Building URI

## Recommended process


1 - Run CMake to generate the build system
2 - Run your favorite CMake-compatible build tool to compile the project and its tests
3 - Run tests

### Windows build from command prompt
Before building the project, you'll need the following third-party dependencies

1 - A C++ compiler with support for std::span and std::ranges
2 - [CMake](https://cmake.org/) version 3.15 or newer
3 - [Ninja](https://ninja-build.org/)

Open a command prompt and run the vcvars64.bat script located in `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build`, this will set up all required environment variables

`"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat`

Run the following command to create the build directory and cd into it
`mkdir build && cd build`

Run the following command to generate the build system
`cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DBUILD_TEST=ON -DCMAKE_C_COMPILER=cl.exe -DCMAKE_CXX_COMPILER=cl.exe ../`

You can replace cl.exe with your favorite C++ compiler

Run the following command to build the project

`cmake --build .`

Finally, you can run the tests with the following command
`ctest`


### Linux build
Before building the project, you'll need the following third-party dependencies

1 - A C++ compiler with support for std::span and std::ranges
2 - [CMake](https://cmake.org/) version 3.15 or newer
3 - [Ninja](https://ninja-build.org/)

Run the following command to create the build directory and cd into it
`mkdir build && cd build`

Run the following command to generate the build system
`cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug -DBUILD_TEST=ON -DCMAKE_C_COMPILER=gcc-10 -DCMAKE_CXX_COMPILER=g++-10 ../`

You can replace g++-10 with your favorite C++ compiler (e.g. clang++-12)

Run the following command to build the project

`cmake --build .`

Finally, you can run the tests with the following command
`ctest`

### Windows: Visual Studio

TODO :)



