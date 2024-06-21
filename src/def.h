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

namespace tut
{
  // Common types
  using VOID = void;
  using BOOL = bool;
  using CHAR = char;
  using UCHAR = unsigned char;
  using SHORT = short;
  using USHORT = unsigned short;
  using INT = int;
  using UINT = unsigned;
  using LONG = long;
  using ULONG = unsigned long;
  using LONGLONG = long long;
  using ULONGLONG = unsigned long long;
  using FLT = float;
  using DBL = double;

  // Strict types
  using UINT8 = std::uint8_t;
  using UINT16 = std::uint16_t;
  using UINT32 = std::uint32_t;
  using UINT64 = std::uint64_t;

  using INT8 = std::int8_t;
  using INT16 = std::int16_t;
  using INT32 = std::int32_t;
  using INT64 = std::int64_t;

  using BYTE = UINT8;
  using WORD = UINT16;
  using DWORD = UINT32;


  // Standard types
  using SIZE_T = std::size_t;

  // Come constants
  inline constexpr BOOL TRUE = true;
  inline constexpr BOOL FALSE = false;

} // end of 'tut' namespace

#endif // __def_h_
