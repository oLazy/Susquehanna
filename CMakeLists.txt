cmake_minimum_required(VERSION 3.20)
project(base VERSION 0.1.0 LANGUAGES CXX)

# Global C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Make compile commands (useful for IDEs / tooling)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Where to place built binaries (optional but tidy)
include(GNUInstallDirs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})

# Build the library from src/
add_subdirectory(src)

# Enable testing and add the unit-test tree
include(CTest)           # defines BUILD_TESTING option (ON by default for top level)
if(BUILD_TESTING)
  add_subdirectory(utest)
endif()

