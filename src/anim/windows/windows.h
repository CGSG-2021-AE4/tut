#ifndef __windows_h_
#define __windows_h_

#include "tut.h"

#include "../context.h"

// Disable converting main to SDL_main
#define SDL_MAIN_HANDLED
#include <SDL.h>

namespace tut::anim
{
  class window
  {
    window( std::string_view Title, const vec2 &Pos, const size &Size, DWORD Flags )
    {
    }

  }; // End of 'window' class

  class window_system
  {
    window_system( VOID )
    {
    }

    VOID WaitInit( VOID )
    {
    }

    VOID PostInit( context &Ctx )
    {
    }

    window *CreateWindow( std::string_view Title, const vec2 &Pos, const size &Size, DWORD Flags )
    {
    }

  }; // End of 'window_system' class
}

#endif // __windows_h_
