#ifndef __def_h_
#define __def_h_

// STL

// Containers ad wrappers
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <print>
#include <array>
#include <variant>
#include <optional>
#include <functional>

// String
#include <string>
#include <string_view>
#include <format>

// Concurrency
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

// Other
#include <assert.h>

// Meta
#include <concepts>

// Debug memory allocation support
#if !defined(NDEBUG)
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h> 
#  define SetDbgMemHooks() \
     _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
     _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

// class for debug memory allocation support
static class __Dummy
{
public: 
  // Class constructor
  __Dummy( void )
  {
    //_CrtSetBreakAlloc(281); -- use for memory leak check
    SetDbgMemHooks(); 
  } // End of '__Dummy' constructor
} __ooppss;

#endif // _DEBUG


// Import types

#include "utility/math/mthdef.h"

namespace tut
{
  using namespace mth::common_types;

  constexpr static const char *BinDirPathPrefix {"../../bin/"};
} // end of 'tut' namespace

#endif // __def_h_
