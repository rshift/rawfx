#include <catch.hpp>
#include <rawfx/math/vec.h>

#include <array>

TEST_CASE("iterator", "[vec]") {
    rawfx::vec<3, int> v = {1, 2, 3};
    REQUIRE( std::equal(v.begin(), v.end(), std::vector<int>({ 1, 2, 3}).begin()) );
}

TEST_CASE("reverse_iterator", "[vec]") {
    rawfx::vec<3, int> v = {3, 2, 1};
    REQUIRE( std::equal(v.rbegin(), v.rend(), std::vector<int>({ 1, 2, 3}).begin()) );
}

TEST_CASE("empty()", "[vec]") {
    REQUIRE( (rawfx::vec<0,int>()).empty() );
    REQUIRE_FALSE( (rawfx::vec<1,int>()).empty() );
}

TEST_CASE("operator=", "[vec]") {
    rawfx::vec<3, int> v1;
    v1 = {1, 2, 3};
    REQUIRE( v1 == (rawfx::vec<3, int>({1, 2, 3})) );
    REQUIRE( v1.length_square() == 14 );
}

TEST_CASE("operator==", "[vec]") {
    rawfx::vec<3, int> v1 = { 1, 2, 3 };
    std::vector<int> v2 = {1, 2, 3};
    REQUIRE( v1 == v2 );
}

TEST_CASE("negate()", "[vec]") {
    rawfx::vec<3, int> v1 = { 1, 2, 3 };
    REQUIRE( v1.negate() == (rawfx::vec<3, int>({ -1, -2, -3 })) );
}

TEST_CASE("-operator()", "[vec]") {
    rawfx::vec<4, int> v = { 1, 2, 3, 4 };
    REQUIRE( (-v) == (rawfx::vec<4, int>({ -1, -2, -3, -4 })));
}

TEST_CASE("operator+", "[vec]") {
    rawfx::vec<3, int> v1 = { 1, 2, 3 };
    REQUIRE( (v1 + rawfx::vec<3, float>({4, 5, 6})) == (rawfx::vec<3, int>({5, 7, 9})) );
    REQUIRE( (v1 + std::initializer_list<float>({ 4.75, 5.32, 6.9 })) == (rawfx::vec<3, int>({5, 7, 9})) );
    REQUIRE( (v1 + 4) == (rawfx::vec<3, int>({5, 6, 7})) );
}

TEST_CASE("operator-", "[vec]") {
    rawfx::vec<3, int> v1 = { 1, 2, 3 };
    REQUIRE( (v1 - rawfx::vec<3, float>({6, 5, 4})) == (rawfx::vec<3, int>({-5, -3, -1})) );
    REQUIRE( (v1 - std::initializer_list<float>({ 6.75, 5.32, 4.9 })) == (rawfx::vec<3, int>({-5, -3, -1})) );
    REQUIRE( (v1 - 2) == (rawfx::vec<3, int>({-1, 0, 1})) );
}

TEST_CASE("operator*", "[vec]") {
    rawfx::vec<3, int> v1 = { 1, 2, 3 };
    REQUIRE( (v1 * rawfx::vec<3, float>({3, 2, 1})) == (rawfx::vec<3, int>({3, 4, 3})) );
    REQUIRE( (v1 * std::initializer_list<float>({ 3, 2, 1 })) == (rawfx::vec<3, int>({3, 4, 3})) );
    REQUIRE( (v1 * 2) == (rawfx::vec<3, int>({2, 4, 6})) );
}

TEST_CASE("operator/", "[vec]") {
    rawfx::vec<3, int> v1 = { 4, 5, 6 };
    REQUIRE( (v1 / rawfx::vec<3, float>({1, 2, 3})) == (rawfx::vec<3, int>({4, 2, 2})) );
    REQUIRE( (v1 / std::initializer_list<float>({ 1, 2, 3 })) == (rawfx::vec<3, int>({4, 2, 2})) );
    REQUIRE( (v1 / 2) == (rawfx::vec<3, int>({2, 2, 3})) );
}

TEST_CASE("scalar_product()", "[vec]") {
    rawfx::vec<3, int> v = { 1, 2, 3 };
    rawfx::vec<3, int> v2 = { 4, 5, 6 };
    REQUIRE( v.scalar_product(v2) == 32 );
}

TEST_CASE("length()", "[vec]") {
    rawfx::vec<3, int> v = { 3, 0, 4 };
    REQUIRE( v.length() == 5 );
}
