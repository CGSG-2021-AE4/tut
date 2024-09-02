#ifndef __window_defenitions_h_
#define __window_defenitions_h_

namespace tut::system::window
{
  // Types declarations
  class window;
  class system;
  
  // Window state descriptor
  struct state
  {
    BOOL
      IsFocused   = FALSE,
      IsHovered   = FALSE,
      IsMinimised = FALSE;
  }; // End of 'window_state' struct

} // end of 'tut::system::window' namespace

#endif // __window_defenitions_h_