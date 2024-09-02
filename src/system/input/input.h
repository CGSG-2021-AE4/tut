#ifndef __input_h_
#define __input_h_

#include <iostream>

#include "tut.h"
#include "../context.h"

namespace tut::system::input
{
  class system
  {
  private:

    context *Ctx {nullptr};
    std::thread EventLoopThread;

  public:

    // Default constructor
    system( VOID )
    {
    } // End of 'system' function

    // Self init
    VOID WaitInit( VOID )
    {
      
    } // End of 'WaitInit' function

    // Post init
    VOID PostInit( context &InCtx )
    {
      Ctx = &InCtx; // Ctx cannot be nullptr

      EventLoopThread = std::thread(&system::RunLoop, this);
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

  }; // End of 'system' class

} // end of 'tut::system::input' namespace

#endif // __input_h_
