#ifndef __window_defenitions_h_
#define __window_defenitions_h_

namespace tut::system::window {
  // Types declarations
  class window;
  class system;
  
  // Window state descriptor
  struct state {
    BOOL
      IsFocused   = FALSE,
      IsHovered   = FALSE,
      IsMinimised = FALSE;
  }; // End of 'window_state' struct

  struct mouse {
    bool
      LButton {false},
      MButton {false},
      RButton {false};
    ivec2 Pos {0, 0};
    ivec3 Delta {0, 0, 0};
  };

} // end of 'tut::system::window' namespace

#endif // __window_defenitions_h_