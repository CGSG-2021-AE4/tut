#ifndef __context_h_
#define __context_h_

#include "tut.h"

namespace tut::anim
{
  // Types declaration
  class window;
  class window_system;

  class context
  {
  public:
    // Systems
    // Use pointers because class are only declared and pointers retain possibility of interfaces in future
    window_system *WindowSystem {nullptr};

    // Global variables and states
    window *MainWindow {nullptr};

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
} // end of 'tut' namespace

#endif // __context_h_