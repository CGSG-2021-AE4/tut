#ifndef __messages_h_
#define __messages_h_

namespace tut::system
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
}

#endif // __messages_h_