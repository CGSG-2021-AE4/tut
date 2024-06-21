#ifndef __anim_h_
#define __anim_h_

#include "tut.h"

#include "context.h"
#include "windows/windows.h"

namespace tut::anim
{
  class anim
  {
  private:
    context Context;

  public:

    // Default constructor
    anim( VOID )
    {
    } // End of 'anim' function

    // Anim init
    VOID Init( VOID )
    {
      
    } // End if 'Init' function

    // Anim close
    VOID Close( VOID )
    {
    } // End of 'Close' function
  }; // End of 'anim' class
} // end of 'tut::anim' namespace

#endif // __anim_h_
