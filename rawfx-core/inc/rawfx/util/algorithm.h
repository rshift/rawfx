#pragma once

#include <type_traits>

namespace rawfx {

template <typename Iter1, typename Iter2, typename OIter, typename Func>
OIter transform(Iter1 begin1, Iter1 end1, Iter2 begin2, Iter2 end2, OIter out, Func func) {

//    typedef typename std::remove_reference< decltype(*out) >::type out_type;

    while (begin1 != end1 && begin2 != end2) {
        *out = func(*begin1, *begin2);
        ++begin1;
        ++begin2;
        ++out;
    }
    return out;
}


}
