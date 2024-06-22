#ifndef __input_h_
#define __input_h_

#include <iostream>

#include "tut.h"
#include "../context.h"

namespace tut::anim
{
  class input_system
  {
  private:

    context *Ctx {nullptr};
    std::thread EventLoopThread;

  public:

    // Default constructor
    input_system( VOID )
    {
    } // End of 'input_system' function

    // Self init
    VOID WaitInit( VOID )
    {
      
    } // End of 'WaitInit' function

    // Post init
    VOID PostInit( context &InCtx )
    {
      Ctx = &InCtx; // Ctx cannot be nullptr

      EventLoopThread = std::thread(&input_system::RunLoop, this);
    } // End of 'PostInit' function

    VOID Close( VOID )
    {
      if (EventLoopThread.joinable())
        EventLoopThread.join();

    } // End of 'Close' function

  private:

    VOID OnMessage( message &Msg )
    {

    } // End of 'OnMessage' function

    VOID RunLoop( VOID );

  }; // End of 'input_system' class

} // end of 'tut::anim' namespace

#endif // __input_h_
