#ifndef __anim_h_
#define __anim_h_

#include "tut.h"

#include "context.h"
#include "windows/windows.h"
#include "input/input.h"
#include "units/units.h"

namespace tut::anim
{
  // Main anim class
  class anim
  {
  private:
    context Context;

  public:

    // Default constructor
    anim( VOID )
    {
    } // End of 'anim' function

    // Destructor
    ~anim( VOID )
    {
    } // End of '~anim' function

    // Forbidding copy/move
    anim( const anim &Other ) = delete;
    anim & operator=( const anim &Other ) = delete;
    anim( anim &&Other ) noexcept = delete;
    anim & operator=( anim &&Other ) noexcept = delete;

    // Anim init
    VOID Init( VOID )
    {
      // Now I allocate systems here
      // Later will remove it
      // I store them as poiters because it retaines possibility of several implementation in future
      Context.WindowSystem = new window_system();
      Context.InputSystem = new input_system();
      Context.UnitSystem = new unit_system();

      // Self init
      Context.WindowSystem->WaitInit();
      Context.InputSystem->WaitInit();
      Context.UnitSystem->WaitInit();

      // Create main window
      Context.MainWindow = Context.WindowSystem->CreateWindow("TUT main window", ivec2 {100, 100}, isize2 {300, 200}, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
      if (Context.MainWindow == nullptr)
        throw std::exception("Main window creation error");

      // Post init
      Context.WindowSystem->PostInit(Context);
      Context.InputSystem->PostInit(Context);
      Context.UnitSystem->PostInit(Context);

    } // End if 'Init' function

    // Get context function
    context & GetContext( VOID ) noexcept
    {
      return Context;
    } // End of 'GetContext' function

    // Wait until the signal of close
    VOID WaitClose( VOID )
    {
      // MEGA SHIT
      message m;
      Context.MsgQueue.Pop(m);
    } // End of 'WaitClose' function

    // Anim close
    VOID Close( VOID )
    {
      // Destroy main window
      Context.WindowSystem->DestroyWindow(Context.MainWindow);

      // Closing systems
      Context.UnitSystem->Close();
      Context.InputSystem->Close();
      Context.WindowSystem->Close();

      // Deallocate context
      delete Context.UnitSystem;
      delete Context.InputSystem;
      delete Context.WindowSystem;

    } // End of 'Close' function
  }; // End of 'anim' class
} // end of 'tut::anim' namespace

#endif // __anim_h_
