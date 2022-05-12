cmake_minimum_required(VERSION 3.15)
project(AfterUri)
set(CMAKE_CXX_STANDARD 20)



# TODO: 
# Add address sanitizer for msvc: msvc seems to have support for address sanitizer (see: https://docs.microsoft.com/en-us/cpp/sanitizers/asan?view=msvc-170)
# For now we only have address sanitizer in debug mode for clang and gcc 

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/AfterUri/*.h)

# Compile flags 
if (MSVC OR (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" AND "x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC"))
# Flags for MSVC Compiler or clang-cl compiler
  add_compile_options("/GS" "/EHs" "$<$<CONFIG:RELEASE>:/O2>")
  # googletest throws thousands of warnings with /Wall, to avoid that we only set the /Wall flag for our files
  set_source_files_properties(${SOURCES} ${HEADERS} PROPERTIES
    COMPILE_FLAGS "/Wall")
else() 
  add_compile_options("-Wall" "-Wextra" "-Wshadow" "-Wconversion" "-Wpedantic" "$<$<CONFIG:RELEASE>:-O3>" "$<$<CONFIG:DEBUG>:-O0;-g3;-ggdb;-fsanitize=address>")
  if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" AND UNIX)
	  add_compile_options("-stdlib=libstdc++")
  endif()
endif()

# For lsp server
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set to ON for building tests or use -DBUILD_TEST=ON
option(BUILD_TEST "Build the unit tests" OFF)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} "$<$<CONFIG:DEBUG>:-fsanitize=address>")

if(WIN32)
  target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
endif()

if (BUILD_TEST)
  enable_testing()
  add_subdirectory(test)
endif()
