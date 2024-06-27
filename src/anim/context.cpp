

#include "context.h"

namespace tut::anim::messages
{
  std::string Format( const message &Msg )
  {
    return std::visit(overloaded {
      []( const window_switch_state_event &Msg ) -> std::string { return "Window switch state"; },
      []( const window_resize_event       &Msg ) -> std::string { return "Window resize"; },
      []( const mouse_motion_event        &Msg ) -> std::string { return "Mouse motion"; },
      []( const mouse_wheel_event         &Msg ) -> std::string { return "Mouse wheel"; },
      []( const mouse_button_event        &Msg ) -> std::string { return "Mouse button"; },
      []( const keyboard_event            &Msg ) -> std::string { return "Keyboard"; },
      []( const close_message             &Msg ) -> std::string { return "Close"; }
    }, Msg);
  } // End of 'Format' function
} // end of 'tut::messages' namespace
