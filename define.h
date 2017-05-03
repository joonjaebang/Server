#ifndef DEFINE
#define DEFINE
#define DEBUG
#ifdef DEBUG
#define _(x) x
#else
#define _(x)
#endif

#ifdef ASSERT
#include <cassert>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif
#endif
