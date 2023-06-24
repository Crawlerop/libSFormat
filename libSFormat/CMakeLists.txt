# CMakeList.txt : CMake project for libSFormat, include source and define
# project specific logic here.
#

# Specify the project info.
project(libSFormat VERSION 1.0.0 DESCRIPTION "Samsung format library")

# Declare the library target.
add_library(${PROJECT_NAME} SHARED
    libSFormat.cpp
    libSFormat.h
 "compressLZ.h" "utils.h" "lz16_32.h" "qmd.h" "crypt.h" "qmd (2).h")

# Configure the directories to search for header files.
target_include_directories(${PROJECT_NAME} PRIVATE source)
# Set the version property.
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
# Set the shared object version property to the project's major version.
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
# Set the public header property to the one with the actual API.
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER libSFormat.h)

# Add source to this project's executable.
# add_executable (libSFormat "libSFormat.cpp" "libSFormat.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET libSFormat PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
