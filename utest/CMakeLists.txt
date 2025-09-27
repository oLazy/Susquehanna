# Fetch Catch2 v3 for unit testing
include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.6.0   # pick a recent tag
)

FetchContent_MakeAvailable(catch2)  # defines Catch2::Catch2WithMain etc.

# Expose the path to data/ for tests (absolute path to the source tree's data dir)
# Tests can read input files using this path.
set(BASE_TEST_DATA_DIR "${CMAKE_SOURCE_DIR}/data")
message(STATUS "Tests will read data from: ${BASE_TEST_DATA_DIR}")

# Create a single test executable that compiles all test_*.cpp files
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/test_*.cpp")

add_executable(base_tests ${TEST_SOURCES})
target_link_libraries(base_tests PRIVATE base_lib Catch2::Catch2WithMain)
target_compile_features(base_tests PRIVATE cxx_std_17)

# Provide data dir as a compile-time constant & runtime env var
target_compile_definitions(base_tests PRIVATE BASE_TEST_DATA_DIR="${BASE_TEST_DATA_DIR}")
if (WIN32)
  # On Windows, env propagation differs; still helpful:
  set_property(TEST base_tests PROPERTY ENVIRONMENT "BASE_TEST_DATA_DIR=${BASE_TEST_DATA_DIR}")
endif()

# Let Catch2 discover individual tests so "ctest" runs them granularly
include(Catch)
catch_discover_tests(base_tests)

