#ifndef __context_h_
#define __context_h_

#include "tut.h"
#include "window/window_defenitions.h"
#include "input/input_defenitions.h"
#include "units/units_defenitions.h"

namespace tut::anim
{
  // Message classes
  namespace messages
  {
    // Window events

    struct window_switch_state_event
    {
      window::window *Wnd;
      window::state NewState;
    };

    struct window_resize_event
    {
      window::window *Wnd;
      isize2 NewSize;
    };

    // Input events
    
    struct mouse_motion_event
    {
      ivec2 Delta;
    };
    
    struct mouse_wheel_event
    {
      ivec2 Delta;
    };

    struct mouse_button_event
    {
      UINT Key;
    };

    struct keyboard_event
    {
      input::key Key;
      BOOL IsPressed;
    };

    // Common messages

    struct close_message
    {
      INT a;
      BOOL b;
    };

  } // end of 'messages' namespace

  using message = std::variant<
    messages::window_switch_state_event,
    messages::window_resize_event,
    messages::mouse_motion_event,
    messages::mouse_wheel_event,
    messages::mouse_button_event,
    messages::keyboard_event,
    messages::close_message
  >;

  namespace messages
  {
    std::string Format( const message &Msg );
  } // end of 'messages' namespace

  class context
  {
  public:
    // Systems
    // Use pointers because class are only declared and pointers retain possibility of interfaces in future
    window::system *WindowSystem {nullptr};
    input::system *InputSystem {nullptr};
    units::system *UnitSystem {nullptr};

    // Global variables and states
    window::window *MainWindow {nullptr};
    async::channel<message> MsgQueue {};

    // Default constructor
    context( VOID )
    {
    } // End of 'context' function

    // Forbidding copy/move
    context( const context &Other ) = delete;
    context & operator=( const context &Other ) = delete;
    context( context &&Other ) noexcept = delete;
    context & operator=( context &&Other ) noexcept = delete;

  }; // End of 'context' class
} // end of 'tut::anim' namespace

#endif // __context_h_