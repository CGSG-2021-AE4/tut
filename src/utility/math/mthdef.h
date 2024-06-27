/*************************************************************
 * Copyright (C) 2022
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mthdef.h
 * PURPOSE     : Raytracing project.
 *               Math default module.
 * PROGRAMMER  : CGSG-SummerCamp'2022.
 *               Andrey Egorov.
 * LAST UPDATE : 23.07.2022.
 * NOTE        : Module namespace 'tmp'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mthdef_h_
#define __mthdef_h_


namespace mth::common_types
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
} // end of 'mth::common_types' namespace

namespace mth
{
  using namespace common_types;

  template<typename Type> class vec2;
  template<typename Type> class vec3;
  template<typename Type> class vec4;

  template<typename Type> class matr;
  template<typename Type> class ray;
  template<typename Type> class intr;
  template<typename Type> class cam;
  class noise;
} // end of 'mth' namespace


/* defines */
#define PI 3.14159265358979323846

#define D2R(A) ((A) * (PI / 180))
#define R2D(A) ((A) / (PI / 180))


#endif // __mthdef_h_


