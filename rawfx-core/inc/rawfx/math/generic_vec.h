#pragma once

#include <array>
#include <algorithm>
#include <cmath>

#include <rawfx/util/algorithm.h>
#include <rawfx/util/range.h>
#include <rawfx/util/random_access_iterator.h>

namespace rawfx {

template <typename Impl, typename Base>
class generic_vec: public Base {
public:

    typedef Impl impl_type;
    typedef Base base_type;

    typedef typename base_type::value_type value_type;

    generic_vec() : base_type() {
    }

    template <typename Other>
    generic_vec(const Other& val) : base_type() {
        operator=(val);
    }

    template <typename Val>
    generic_vec(const std::initializer_list<Val>& val) : base_type() {
        operator=(val);
    }

    value_type length_square() const {
        value_type result = value_type();
        for (size_t i = 0; i < base_type::size(); i++) {
            const value_type& val = as_vec()[i];
            result += val * val;
        }
        return result;
    }

    value_type length() const {
        return sqrt(length_square());
    }

    template <typename Other>
    impl_type& operator=(const Other& other) {
        auto r = rawfx::range(other, base_type::size()),
            b = base_type::begin(), e = base_type::end(),
            rb = r.begin(), re = r.end();

        while (b != e && rb != re) {
            *b = *rb;
            ++b;
            ++rb;
        }
        while (b != e) {
            *b = value_type();
        }
        return as_vec();
    }

    template <typename Other>
    bool operator==(const Other& other) const {
        auto r = rawfx::range(other, base_type::size()),
            b = base_type::begin(), e = base_type::end(),
            rb = r.begin(), re = r.end();
        while (b != e) {
            if (rb == re) {
                return false;
            }
            if (*b == *rb) {
                ++b;
                ++rb;
            } else {
                return false;
            }
        }
        return rb == re;
    }

    template <typename Other>
    bool operator!=(const Other& other) const {
        return !operator==(other);
    }

    impl_type& negate() {
        std::transform(base_type::begin(), base_type::end(), base_type::begin(), std::negate<value_type>());
        return as_vec();
    }

    impl_type& operator-() const {
        return impl_type(as_vec()).negate();
    }

    template <typename Other>
    impl_type& operator+=(const Other& other) {
        return transform(other, std::plus<value_type>());
    }

    template <typename Other>
    impl_type& operator-=(const Other& other) {
        return transform(other, std::minus<value_type>());
    }

    template <typename Other>
    impl_type& operator*=(const Other& other) {
        return transform(other, std::multiplies<value_type>());
    }

    template <typename Other>
    impl_type& operator/=(const Other& other) {
        return transform(other, std::divides<value_type>());
    }

    template <typename Other>
    impl_type operator+(const Other& other) const {
        return impl_type(as_vec()) += other;
    }

    template <typename Other>
    impl_type operator-(const Other& other) const {
        return impl_type(as_vec()) -= other;
    }

    template <typename Other>
    impl_type operator*(const Other& other) const {
        return impl_type(as_vec()) *= other;
    }

    template <typename Other>
    impl_type operator/(const Other& other) const {
        return impl_type(as_vec()) /= other;
    }

protected:

    template <typename Other, typename Func>
    impl_type& transform(const Other& other, Func func) {
        auto i = base_type::begin();
        auto r = rawfx::range(other, base_type::size());
        rawfx::transform(i, base_type::end(), r.begin(), r.end(), i, func);
        return as_vec();
    }

private:

    const impl_type& as_vec() const {
        return *static_cast<const impl_type*>(this);
    }

    impl_type& as_vec() {
        return *static_cast<impl_type*>(this);
    }

};


}
