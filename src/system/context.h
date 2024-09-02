#ifndef __context_h_
#define __context_h_

#include "tut.h"
#include "window/window_defenitions.h"
#include "input/input_defenitions.h"
#include "messages.h"

namespace tut::system
{
  class context
  {
  public:
    // Systems
    // Use pointers because class are only declared and pointers retain possibility of interfaces in future
    window::system *WindowSystem {nullptr};
    input::system *InputSystem {nullptr};

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

    // Checks if all values are valid and set otherwise throw an exception
    void Validate( void ) const {
      // if (WindowSystem == nullptr)
      //   throw std::runtime_error("window system is null");
      // if (InputSystem == nullptr)
      //   throw std::runtime_error("input system is null");
      // if (MainWindow == nullptr)
      //   throw std::runtime_error("main window is null");
    }

  }; // End of 'context' class
} // end of 'tut::system' namespace

#endif // __context_h_