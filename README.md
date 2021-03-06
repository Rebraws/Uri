# Uri

Uri is a C++20 cross-platorm library for parsing Uniform Resource Identifier (URI)


## Getting Started

### Prerequisites

- CMake 3.15 or newer to generate the build system 
- Any CMake-compatible toolchain for compiling and linking

At least a C++20 compiler with the following C++20 features
- std::span
- std::ranges

### Build system generation

Please see [BUILDING](https://github.com/rebraws/Uri/blob/main/docs/BUILDING.md) for a more detail description about building the project

```
git clone git@github.com:Rebraws/Uri.git
cd Uri
mkdir build
cd build
cmake ../
```

### Compiling and linking

```
cd build
cmake --build .  
```
Note: You can specify your compiler of preference by using -DCMAKE_CXX_COMPILER and -DCMAKE_C_COMPILER flags or by setting
CXX and CC environment variables on linux

### Running the tests
Before running the tests, you need to compile the project with the BUILD_TEST option
```
mkdir build
cd build
cmake -DBUILD_TEST=ON ../
```

Then you have two ways to run the tests
- Using ctest (e.g.``` ctest ```)
- Running them manually (e.g.``` ./test/Test ```)


### Dependencies
- [googletest](https://github.com/google/googletest) only for running tests



### Usage example
```
#include <AfterUri/AfterUri.h>

int main() {
  std::string url{"http://www.example.com:80/foo/bar?foo=bar"};
  
  AfterUri::Uri parsed_uri;

  parsed_uri.parseFrom(url);

  std::cout << "Scheme: " << parsed_uri.getScheme() << '\n';
  std::cout << "Authority: " << parsed_uri.getAuthority() << '\n';
  
  if (parsed_uri.hasPort()) {
    std::cout << "Port: " << parsed_uri.getPort() << '\n';
  }
  return 0;
}

```

### License
MIT


