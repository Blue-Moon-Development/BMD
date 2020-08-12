# BMD
BMD is a set of platform independent lightweight (mostly) utilities for C/C++

BMD can be used as a static library or as a header only version. Run cmake to build a static library for your compiler and platform of choice. To use the header only version, in a single source file, simply call `#define BMD_HEADERS_ONLY` before including `#include <bmd/core.h>` which gives access to all bmd headers, as well as provides the implementation.

To enable some of the debugging features for the header only version, use `#define BMD_DEBUGGING 1`

If you wish to use the provided minimalistic profiler, use `#define BMD_PROFILE 1` on C++ you will also have access to `PROFILER_SCOPE(some number)` which will start the profiler and automatically end it when the program leaves the given scope

The ultimate goal is for this library to be platform independent, but in it's early stages my sole focus is on Windows. I will work on Unix functions when I feel the windows version is complete enough. Unix version will be tested on Ubuntu 20. I don't have any experience working with C++ on a mac, so that version if different from Unix will be the last to come