#ifndef __context_h_
#define __context_h_

#include "tut.h"

namespace tut::anim
{
  // Types declaration
  class window;
  class window_system;
  class input_system;
  class unit_system;

  // Window state descriptor
  struct window_state
  {
    BOOL
      IsFocused   = FALSE,
      IsHovered   = FALSE,
      IsMinimised = FALSE;
  }; // End of 'window_state' struct

  // Message classes
  namespace messages
  {
    // Window events

    struct window_switch_state_event
    {
      window *Wnd;
      window_state NewState;
    };

    struct window_resize_event
    {
      window *Wnd;
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
      // ???
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
    window_system *WindowSystem {nullptr};
    input_system *InputSystem {nullptr};
    unit_system *UnitSystem {nullptr};

    // Global variables and states
    window *MainWindow {nullptr};
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