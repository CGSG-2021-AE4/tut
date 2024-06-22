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

    window( std::string_view Title, const ivec2 &Pos, const isize2 &Size, DWORD Flags ) :
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
    context *Ctx {nullptr};
    std::thread EventPollLoop;

    // Default constructor
    window_system( VOID )
    {
    } // End of 'window_system' function

    // Self init
    VOID WaitInit( VOID )
    {
      // SDL init
      if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::exception("SDL Init failed.");
    } // End of 'WaitInit' function

    // Main event poll loop
    VOID RunEventPollLoop( VOID )
    {
      BOOL ExitFlag {FALSE};
      SDL_Event e;
      while (!ExitFlag)
      {
        while (SDL_PollEvent(&e) != 0)
        {
          switch (e.type)
          {
          case SDL_QUIT:
            ExitFlag = TRUE;
            Ctx->MsgQueue.PushBack(messages::close_message {});
            break;
          case SDL_MOUSEMOTION:
            Ctx->MsgQueue.PushBack(messages::mouse_motion_event { ivec2 {e.motion.xrel, e.motion.yrel} });
            break;
          case SDL_MOUSEWHEEL:
            Ctx->MsgQueue.PushBack(messages::mouse_wheel_event { ivec2 {e.wheel.x, e.wheel.y} });
            break;
          }
        }
      }
    } // End of 'RunEventPollLoop' function

    // Post init
    VOID PostInit( context &InCtx )
    {
      Ctx = &InCtx;

      // Start event poll cycle
      //EventPollLoop = std::thread(&window_system::RunEventPollLoop, this);
    } // End of 'PostInit' function

    VOID Close( VOID )
    {
      // Wait for event poll loop to finish
      // if (EventPollLoop.joinable())
      //   EventPollLoop.join();
      // Destroy all existing windows but... I do not store them yet)
      // SDL deinit
      SDL_Quit();
    } // End of 'Close' function

    window *CreateWindow( std::string_view Title, const ivec2 &Pos, const isize2 &Size, DWORD Flags )
    {
      // I am sure it is not right but for the first time OK
      auto Wnd = new window(Title, Pos, Size, Flags);

      if (!Wnd->Validate())
      {
        delete Wnd;
        return nullptr;
      }
      return Wnd;
    } // End of 'CreateWindow' function

    VOID DestroyWindow( window *Wnd )
    {
      delete Wnd;
    } // End of 'DestroyWindow' function

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
