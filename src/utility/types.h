#ifndef __types_h_
#define __types_h_

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

  // Binary types
  using BYTE = UCHAR;
  using WORD = USHORT;
  using DWORD = ULONG;

  // Standard types
  using SIZE_T = std::size_t;
}

#endif // __types_h_