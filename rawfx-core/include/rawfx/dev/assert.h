#pragma once

#ifndef NDEBUG
#include <iostream>
#define RAWFX_ASSERT(cond, msg) ((cond) \
    ? static_cast<void>(0) \
    : (std::cerr << "Assertion failure. Expression (" << (#cond) << ") in "  << \
    (__FILE__) << " at line " << (__LINE__) << ": " << msg << std::endl, abort()))
#else
#define RAWFX_ASSERT(cond, msg) ;
#endif
