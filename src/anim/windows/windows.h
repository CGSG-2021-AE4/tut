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
  private:
    SDL_Window *Wnd {nullptr}; // SDL window object

  public:

    window( std::string_view Title, const vec2 &Pos, const size &Size, DWORD Flags ) :
      Wnd {SDL_CreateWindow(Title.data(), Pos.X, Pos.Y, Size.W, Size.H, Flags)}
    {
    } // End of 'window' function

    // Check if window is valid
    BOOL Validate( VOID ) noexcept
    {
      return Wnd != nullptr;
    } // End of 'Validate' function

    ~window( VOID )
    {
      if (Wnd != nullptr)
        SDL_DestroyWindow(Wnd);
    } // End of '~window' function

  }; // End of 'window' class

  class window_system
  {
  public:

    window_system( VOID )
    {
    }

    VOID WaitInit( VOID )
    {
      if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::exception("SDL Init failed.");
    }

    VOID PostInit( context &Ctx )
    {
    }

    VOID Close( VOID )
    {
      // Destroy all existing windows but... I do not store them yet)
    }

    window *CreateWindow( std::string_view Title, const vec2 &Pos, const size &Size, DWORD Flags )
    {
      // I am sure it is not right but for the first time OK
      auto Wnd = new window(Title, Pos, Size, Flags);

      if (!Wnd->Validate())
      {
        delete Wnd;
        return nullptr;
      }
      return Wnd;
    }

    VOID DestroyWindow( window *Wnd )
    {
      delete Wnd;
    }

  }; // End of 'window_system' class
} // end of 'tut::anim' namespace

/* SDL window sample 
 
std::cout << "CGSG forever!!!\n";

if (SDL_Init(SDL_INIT_VIDEO) < 0)
  std::runtime_error("SDL Init failed.");

SDL_Window *window = SDL_CreateWindow("First SDL", 100, 100, 200, 100, SDL_WINDOW_SHOWN);

if (window == nullptr)
  std::runtime_error("Window creation failed.");

SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0x00));
SDL_UpdateWindowSurface(window);

SDL_Event e;
bool quit = false;

while (!quit)
  while (SDL_PollEvent(&e))
    if (e.type == SDL_QUIT)
      quit = true;

SDL_DestroyWindow(window);
SDL_Quit();
*/

#endif // __windows_h_
