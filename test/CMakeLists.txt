cmake_minimum_required(VERSION 3.15)

project(Tests)
include(FetchContent)

# Using a custom fork of googletest because googletest can't compile with /Wall flag in windows
# This fork has /WX flag removed and also fixes some warnings 
FetchContent_Declare(googletest
  GIT_REPOSITORY https://github.com/Rebraws/googletest
  GIT_TAG release-1.11.2
  )

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE
  AfterUri
  gtest
  gtest_main
  )

add_test(
  NAME ${PROJECT_NAME}
  COMMAND ${PROJECT_NAME}
  )

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

