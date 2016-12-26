#include <catch.hpp>

#include <rawfx/defs/loader.h>

using rawfx::loader;

template <typename T>
class test_def {

public:

    typedef T value_type;

    test_def(const value_type& val = value_type(), const test_def<T>* ref = nullptr) : val(val), ref(ref) {
    }

    value_type load(loader& l) const {
        if (ref != nullptr) {
            l.of(*ref).load();
        }
        return val;
    }

    void unload(loader& l, value_type& v) const {

    }


private:
    T val;
    const test_def<T>* ref;

};

TEST_CASE("loader must correctly set references", "[loader]") {

    loader l;

    test_def<int> d1(123);
    test_def<int> d2(321, &d1);

    REQUIRE(l.of(d1).load() == 123);
    REQUIRE(l.of(d2).load() == 321);

    REQUIRE(l.of(d1).is_ref_by(d2));
    REQUIRE(l.of(d2).has_ref_to(d1));

    REQUIRE_FALSE(l.of(d2).is_ref_by(d1));
    REQUIRE_FALSE(l.of(d1).has_ref_to(d2));

    // simple unloading of `d1` wont work (because `d1` is referenced by `d2`),
    // however this call will remove 'explicit load mark' from d1
    // and allow this object to be automatically removed
    REQUIRE_FALSE(l.of(d1).unload());

    // unloading of `d2` also cascades to `d1`
    REQUIRE(l.of(d2).unload());

    REQUIRE_FALSE(l.of(d1).loaded());

}

// TODO tests: difference between dependency loading and explicit loading

// TODO unload_all tests (verify unloading order)

// TODO tests with parent
