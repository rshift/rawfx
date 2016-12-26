#pragma once

namespace rawfx {
namespace graphics {


template <typename T>
struct rgba {

    typedef T component_type;

    T r, g, b, a;

    rgba() : r(), g(), b(), a() {
    }

    rgba(const T& r, const T& g, const T& b, const T& a) {
    }

};

template <typename T>
class color: public T {
public:

    typedef T scheme;

    using scheme::scheme;

    static const color<T> RED;
    static const color<T> GREEN;
    static const color<T> BLUE;
    static const color<T> WHITE;
    static const color<T> BLACK;
};

template <typename T> const color<T> color<T>::RED =    color<rgba<typename T::component_type>>(1.f, 0.f, 0.f, 1.f);
template <typename T> const color<T> color<T>::GREEN =  color<rgba<typename T::component_type>>(0.f, 1.f, 0.f, 1.f);
template <typename T> const color<T> color<T>::BLUE =   color<rgba<typename T::component_type>>(0.f, 0.f, 1.f, 1.f);
template <typename T> const color<T> color<T>::WHITE =  color<rgba<typename T::component_type>>(1.f, 1.f, 1.f, 1.f);
template <typename T> const color<T> color<T>::BLACK =  color<rgba<typename T::component_type>>(0.f, 0.f, 0.f, 1.f);

}
}
