#ifndef __tut_h_
#define __tut_h_

#include "def.h"

#include "utility/math/mth.h"
#include "utility/async.h"
#include "utility/resource.h"

namespace tut
{
  using vec2 = mth::vec2<FLT>;
  using vec3 = mth::vec3<FLT>;
  using vec4 = mth::vec4<FLT>;
  using size2 = mth::size<FLT>;
  
  using ivec2 = mth::vec2<UINT>;
  using ivec3 = mth::vec3<UINT>;
  using ivec4 = mth::vec4<UINT>;
  using isize2 = mth::size<UINT>;
} // end of 'tut' namespace

#endif // __tut_h_