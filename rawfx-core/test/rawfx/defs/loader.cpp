#include <catch.hpp>

#include <rawfx/defs/loader.h>

#include <functional>

using rawfx::loader;

template <typename T>
class test_def {

public:

    typedef T value_type;

    test_def(const value_type& val = value_type(), const test_def* ref = nullptr) : _val(val), _ref(ref) {
        _load_idx = 0;
        _unload_idx = 0;
    }

    value_type load(loader& l) const {
        ++_load_idx;
        _load_order = _load_idx;

        if (_ref != nullptr) {
            l.of(*_ref).load();
        }
        return _val;
    }

    void unload(loader& l, value_type& v) const {
        ++_unload_idx;
        _unload_order = _unload_idx;
    }


    size_t load_order() const {
        return _load_order;
    }

    size_t unload_order() const {
        return _unload_order;
    }

private:
    T _val;
    const test_def<T>* _ref;

    static size_t _load_idx, _unload_idx;

    mutable size_t _load_order, _unload_order;

};

template <typename T> size_t test_def<T>::_load_idx = 0;
template <typename T> size_t test_def<T>::_unload_idx = 0;

TEST_CASE("loader must correctly set references", "[loader]") {

    loader l;

    test_def<int> d1(123), d2(321, &d1);

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

TEST_CASE("unload_all must return count of references objects which cant be removed", "[loader]") {

    test_def<int> d1(123), d2(321, &d1);

    loader p, c(&p);

    p.of(d1).load();
    c.of(d2).load();

    REQUIRE( p.unload_all() == 1);

}

TEST_CASE("unload order must follow dependency graph", "[loader]") {

    // d1 <- d2 <- d4
    //  \
    //   d3

    test_def<int> d1(123), d2(321, &d1), d3(444, &d1), d4(555, &d2);

    {
        loader l;
        l.of(d3).load();
        l.of(d4).load();
    }

    REQUIRE(d2.unload_order() < d1.unload_order());
    REQUIRE(d3.unload_order() < d1.unload_order());
    REQUIRE(d4.unload_order() < d2.unload_order());

}

TEST_CASE("unload_all must cascade unload to parent loader objects", "[loader]") {


    test_def<const char*> d1("d1"), d2("d2", &d1), d3("d3", &d1);

    loader p;

    // loading d2 which cascade load to d1
    p.of(d2).load();

    {
        loader c(&p);

        // loading d3 (d1 will be taken from parent loader)
        c.of(d3).load();

        // unloading d2 in parent
        p.of(d2).unload();

        // ensuring that d3 depends on d1
        REQUIRE( c.of(d3).has_ref_to(d1) );

        // ensuring that d1 is same in child and parent loaders
        REQUIRE( c.of(d1).get() == p.of(d1).get() );

    }

    // after destruction of child loader,
    // d1 must also be unloaded because there is no more references to d1
    REQUIRE_FALSE( p.of(d1).loaded() );

    // d1 must be unloaded after d3
    REQUIRE(d1.unload_order() > d3.unload_order());

}

TEST_CASE("loader must unload all objects", "[loader]") {

    test_def<int> d1(123), d2(321, &d1);

    loader p;
    p.of(d1).load();

    {

        loader c(&p);
        c.of(d2).load();

        REQUIRE_FALSE(p.of(d2).loaded());
        REQUIRE(c.of(d2).loaded());

        REQUIRE(c.of(d1).get() == p.of(d1).get());

    }

    REQUIRE(d2.unload_order() == 1);

}
