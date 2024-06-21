#ifndef __context_h_
#define __context_h_

#include "tut.h"

#include "windows/windows.h"

namespace tut::anim
{
  class context
  {
  public:
    // Systems
    window_system WindowsSystem;

    // Global variables and states
    window *MainWindow {nullptr};

    // Default constructor
    context( VOID )
    {
    } // End of 'context' function

    // Forbidding copy/move
    context( cosnt context &Other ) = delete;
    context & operator=( cosnt context &Other ) = delete;
    context( context &&Other ) noexcept = delete;
    context & operator=( context &&Other ) noexcept = delete;

  }; // End of 'context' class
} // end of 'tut' namespace

#endif // __context_h_