#include <catch.hpp>

#include <rawfx/core/composite.h>

using namespace ::rawfx::core;

class test_handler: public handler {

    virtual void on(const event &evt, engine &eng) {
        INFO("in test_handler");
    }

};

TEST_CASE("composite must remove killed handler", "[composite]") {


}

TEST_CASE("composite correctly calls attach", "[composite]") {

    engine eng;

    composite cmp;
    cmp.add(new test_handler());

    cmp.on(event(ATTACH), eng);

}
