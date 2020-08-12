# BMD
BMD is a set of platform independent lightweight (mostly) utilities for C/C++

BMD can be used as a static library or as a header only version. Run cmake to build a static library for your compiler and platform of choice. To use the header only version, in a single source file, simply call `#define BMD_HEADERS_ONLY` before including `#include <bmd/core.h>` which gives access to all bmd headers, as well as provides the implementation.

To enable some of the debugging features for the header only version, use `#define BMD_DEBUGGING 1`

If using C++ and you wish to use the provided minimalistic profiler, use `#define BMD_PROFILE 1`
