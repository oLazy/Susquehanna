//
// Created by Eric Mandolesi on 27/09/2025.
//
#include <catch2/catch_test_macros.hpp>
#include "component/array_viewer/array_viewer.hpp"


TEST_CASE("c-style array", "[array_view]") {
    int raw[] = {1,2,3,4};
    array_view<int> view(raw,4);
    REQUIRE(view.getSize() == 4);
    REQUIRE_FALSE(view.empty());
    REQUIRE(view[0] == 1);
    REQUIRE_THROWS(view.at(11));

    // test iterators
    int sum = 0;
    for (auto x : view){
        sum+=x;
    }
    REQUIRE(sum==10);
}

TEST_CASE("c-style array infers the right size", "[array-view]"){
    const float raw[] = {0.1f, 0.2f, 0.3f};
    array_view<const float> view(raw);
    REQUIRE(view.getSize()==3);
    REQUIRE(view[1] == 0.2f);
}
