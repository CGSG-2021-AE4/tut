#ifndef __anim_h_
#define __anim_h_

#include "tut.h"

#include "context.h"
#include "windows/windows.h"


namespace tut::anim
{
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

      Context.WindowSystem = new window_system();

      // Self init
      Context.WindowSystem->WaitInit();

      // Create main window
      Context.MainWindow = Context.WindowSystem->CreateWindow("TUT main window", vec2 {100, 100}, size {300, 200}, SDL_WINDOW_SHOWN);
      if (Context.MainWindow == nullptr)
        throw std::exception("Main window creation error");

      // Post init
      Context.WindowSystem->PostInit(Context);

    } // End if 'Init' function

    // Anim close
    VOID Close( VOID )
    {
      // Destroy main window
      Context.WindowSystem->DestroyWindow(Context.MainWindow);

      // Closing systems
      Context.WindowSystem->Close();

      // Deallocate context
      delete Context.WindowSystem;

    } // End of 'Close' function
  }; // End of 'anim' class
} // end of 'tut::anim' namespace

#endif // __anim_h_
