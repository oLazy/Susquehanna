#include <catch2/catch_test_macros.hpp>
#include "component/foo.hpp"
#include <string>

TEST_CASE("add works", "[component]") {
    using base::component::add;
    REQUIRE(add(2, 2) == 4);
    REQUIRE(add(-1, 1) == 0);
}

TEST_CASE("load_first_line reads fixture", "[component]") {
    using base::component::load_first_line;

    // Get data path (from compile-time define)
    std::string dir = BASE_TEST_DATA_DIR; // defined in CMake
    std::string file = dir + "/hello.txt";

    auto line = load_first_line(file);
    REQUIRE(line == "hello");
}

