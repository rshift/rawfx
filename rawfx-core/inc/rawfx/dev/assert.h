#pragma once

#ifndef NDEBUG
#include <iostream>
#define RAWFX_ASSERT(expr, cond, msg) ((expr cond) \
    ? static_cast<void>(0) \
    : (std::cerr << "Assertion failure. Expression (" << (#expr) << " " << (#cond) << ") in "  << \
    (__FILE__) << " at line " << (__LINE__) << ": " << msg << std::endl, abort()))
#else
#define RAWFX_ASSERT(expr, cond, msg) (expr)
#endif
