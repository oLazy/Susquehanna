# Build the library target `base_lib` from everything under src/
# Each "component" can simply live in src/component/<name>/

# Collect sources (you can also list them explicitly if you prefer)
file(GLOB_RECURSE BASE_SOURCES
     CONFIGURE_DEPENDS
     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(base_lib ${BASE_SOURCES})

# Public headers live under src/ and subfolders
target_include_directories(base_lib
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}     # so you can #include "component/foo.hpp"
)

# Treat warnings strictly for this target (tweak as you like)
if (MSVC)
  target_compile_options(base_lib PRIVATE /W4)
else()
  target_compile_options(base_lib PRIVATE -Wall -Wextra -Wpedantic)
endif()

# If you later want to install the library/headers, you can add install() rules.

