#include <catch.hpp>

#include <rawfx/comp/composite.h>

using namespace rawfx;

class test_helper {
public:

    test_helper(bool kill = false) : kill(kill) {
    }

    bool kill;
    std::vector<event_type> events;

};

std::vector<event_type> events(const std::initializer_list<event_type>& types) {
    return std::vector<event_type>(types);
}

class test_handler: public handler {
public:

    test_handler(test_helper& helper) : helper(helper) {
    }

    virtual void on(const event &evt, engine &eng) {
        helper.events.push_back(evt.type());
        if (helper.kill) {
            eng.kill_me();
        }
    }

private:
    test_helper& helper;
};

TEST_CASE("MUST detach and remove killed handler", "[composite]") {

    test_helper helper(true);

    engine eng;
    composite cmp;

    cmp.add(new test_handler(helper));
    cmp.on(event(ATTACH), eng);

    REQUIRE( helper.events == events({ATTACH}));
    REQUIRE( cmp.empty() );

}

TEST_CASE("MUST forward events", "[composite]") {

    test_helper helper;

    engine eng;
    composite cmp;

    cmp.add(new test_handler(helper));
    cmp.on(event(ATTACH), eng);
    cmp.on(event(INPUT), eng);

    REQUIRE( helper.events == events({ATTACH, INPUT}) );

}

TEST_CASE("MUST send ATTACH immediately if ATTACH was called before", "[composite]") {

    test_helper helper;

    engine eng;
    composite cmp;
    cmp.on(event(ATTACH), eng);

    cmp.add(new test_handler(helper));

    REQUIRE( helper.events == events({ATTACH}) );

}

TEST_CASE("SHOULD NOT send DETACH on destruction without ATTACH event", "[composite]") {
    test_helper helper;

    {
        composite cmp;
        cmp.add(new test_handler(helper));
    }

    REQUIRE( helper.events == events({}) );
}

TEST_CASE("MUST send DETACH on destruction if ATTACH was called", "[composite]") {

    test_helper helper;

    {
        engine eng;
        composite cmp;
        cmp.add(new test_handler(helper));
        cmp.on(event(ATTACH), eng);
    }

    REQUIRE( helper.events == events({ATTACH}) );

}
