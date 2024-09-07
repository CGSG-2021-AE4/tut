#ifndef __window_h_
#define __window_h_

#include "tut.h"

#include "../context.h"
#include "system/render/render_defenitions.h"

// Disable converting main to SDL_main
#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif // SDL_MAIN_HANDLED
#include <SDL.h>

namespace tut::system::window
{
  // Window
  class window
  {
  protected:
    friend class system;
    friend class render::system;
    
    SDL_Window *Wnd {nullptr}; // SDL window object
    state State {};     // Visual state
    isize2 Size;               // Current window size

  public:

    window( std::string_view Title, const ivec2 &Pos, const isize2 &Size, DWORD Flags ) :
      Wnd {SDL_CreateWindow(Title.data(), Pos.X, Pos.Y, Size.W, Size.H, Flags)},
      Size {Size}
    {
    } // End of 'window' function

    ~window( VOID )
    {
      if (Wnd != nullptr)
        SDL_DestroyWindow(Wnd);
    } // End of '~window' function

    // Check if window is valid
    BOOL Validate( VOID ) noexcept
    {
      return Wnd != nullptr;
    } // End of 'Validate' function

    isize2 GetSize( VOID ) const noexcept
    {
      return State.IsMinimised ? isize2 {0, 0} : Size;
    } // End of 'GetSize' function

    // Event functions - public because are executed from lambda

    VOID OnResize( const isize2 &NewSize )
    {
      Size = NewSize;
      std::cout << "WINDOW new size\n";
      // Maybe something...
    } // End of 'OnResize' function
    
    VOID OnSwitchState( const state &NewState )
    {
      std::cout << "WINDOW new state\n";
      State = NewState;
    } // End of 'OnSwitchState' function
  }; // End of 'window' class

  class system
  {
  public:
    context *Ctx {nullptr};
    std::thread EventPollLoop;
    std::map<UINT32, window *> Windows;

    // Default constructor
    system( VOID )
    {
    } // End of 'system' function

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
          case SDL_WINDOWEVENT:
          {
            auto we = e.window;
            std::cout << we.windowID;
            auto *Wnd = Windows[we.windowID]; // Should not fail...
            auto WndState = Wnd->State;

            switch (we.event)
            {
              case SDL_WINDOWEVENT_SIZE_CHANGED:
                Ctx->MsgQueue.PushBack(messages::window_resize_event { Wnd, isize2 { we.data1, we.data2 } });
                break;
              case SDL_WINDOWEVENT_MINIMIZED:
                WndState.IsMinimised = TRUE;
                Ctx->MsgQueue.PushBack(messages::window_switch_state_event { Wnd, WndState });
                break;
              case SDL_WINDOWEVENT_RESTORED:
                WndState.IsMinimised = FALSE;
                Ctx->MsgQueue.PushBack(messages::window_switch_state_event { Wnd, WndState });
                break;
              case SDL_WINDOWEVENT_ENTER:
                WndState.IsHovered = TRUE;
                Ctx->MsgQueue.PushBack(messages::window_switch_state_event { Wnd, WndState });
                break;
              case SDL_WINDOWEVENT_LEAVE:
                WndState.IsHovered = FALSE;
                Ctx->MsgQueue.PushBack(messages::window_switch_state_event { Wnd, WndState });
                break;
              case SDL_WINDOWEVENT_FOCUS_GAINED:
                WndState.IsFocused = TRUE;
                Ctx->MsgQueue.PushBack(messages::window_switch_state_event { Wnd, WndState });
                break;
              case SDL_WINDOWEVENT_FOCUS_LOST:
                WndState.IsFocused = FALSE;
                Ctx->MsgQueue.PushBack(messages::window_switch_state_event { Wnd, WndState });
                break;
              case SDL_WINDOWEVENT_SHOWN: // --
              case SDL_WINDOWEVENT_HIDDEN: // --
              case SDL_WINDOWEVENT_EXPOSED: // --
              case SDL_WINDOWEVENT_MOVED: // --
              case SDL_WINDOWEVENT_RESIZED: // --
              case SDL_WINDOWEVENT_MAXIMIZED: // --
              case SDL_WINDOWEVENT_CLOSE: // --
              case SDL_WINDOWEVENT_TAKE_FOCUS: // --
              case SDL_WINDOWEVENT_HIT_TEST: // --
              case SDL_WINDOWEVENT_ICCPROF_CHANGED: // --
              case SDL_WINDOWEVENT_DISPLAY_CHANGED : // --
                break;
            }
            //Ctx->MsgQueue.PushBack(messages::window_resize_event {  });
            break;
          }
          case SDL_MOUSEMOTION:
            Ctx->MsgQueue.PushBack(messages::mouse_motion_event { ivec2 {e.motion.xrel, e.motion.yrel} });
            break;
          case SDL_MOUSEWHEEL:
            Ctx->MsgQueue.PushBack(messages::mouse_wheel_event { ivec2 {e.wheel.x, e.wheel.y} });
            break;
          case SDL_KEYDOWN:
            if (!e.key.repeat) // I cannot deside what is better but this way there are less messages TODO deside!!!
              Ctx->MsgQueue.PushBack(messages::keyboard_event { input::key::FromSDL(e.key.keysym.scancode, e.key.keysym.mod), TRUE });
            break;
          case SDL_KEYUP:
            Ctx->MsgQueue.PushBack(messages::keyboard_event { input::key::FromSDL(e.key.keysym.scancode, e.key.keysym.mod), TRUE });
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

    VOID OnMessage( message &Msg )
    {
      std::visit(overloaded { []( auto &Msg ) { /* Default case */ },
        [this]( messages::window_resize_event &Msg )
        {
          Msg.Wnd->OnResize(Msg.NewSize);
        },
        [this]( messages::window_switch_state_event &Msg )
        {
          Msg.Wnd->OnSwitchState(Msg.NewState);
        }
      }, Msg);
    } // End of 'OnMessage' function

    window *CreateWindow( std::string_view Title, const ivec2 &Pos, const isize2 &Size, DWORD Flags )
    {
      // I am sure it is not right but for the first time OK
      auto Wnd = new window(Title, Pos, Size, Flags);

      if (!Wnd->Validate())
      {
        delete Wnd;
        return nullptr;
      }
      Windows.emplace(SDL_GetWindowID(Wnd->Wnd), Wnd);
      return Wnd;
    } // End of 'CreateWindow' function

    VOID DestroyWindow( window *Wnd )
    {
      Windows.erase(SDL_GetWindowID(Wnd->Wnd));
      delete Wnd;
    } // End of 'DestroyWindow' function

  }; // End of 'system' class
} // end of 'tut::system::window' namespace

#endif // __window_h_
