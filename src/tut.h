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
  
  using ivec2 = mth::vec2<INT>;
  using ivec3 = mth::vec3<INT>;
  using ivec4 = mth::vec4<INT>;
  using isize2 = mth::size<INT>;

  // Some meta from FB1
  // Meta used for std::variant handling
  template<class... ts>
    struct overloaded : ts... { using ts::operator()...; };

} // end of 'tut' namespace

#endif // __tut_h_