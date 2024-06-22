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

  private:

    // Run event pop loop
    VOID RunLoop( VOID )
    {
      BOOL ExitFlag {FALSE};
      while (!ExitFlag)
      {
        message Msg;
        Ctx->MsgQueue.Pop(Msg);
        std::visit(overloaded { []( auto &Msg ) { /* Default message */ },
          [&ExitFlag, this]( messages::close_message &CloseMsg )
          {
            ExitFlag = TRUE;
          },
          [&ExitFlag, this]( messages::mouse_motion_event &E )
          {
            std::cout << std::format("Mouse motion event - Delta: [{},{}]\n", E.Delta.X, E.Delta.Y);
          }
        },Msg);
      }
    } // End of 'RunLoop' function

  public:

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
  }; // End of 'input_system' class

} // end of 'tut::anim' namespace

#endif // __input_h_
