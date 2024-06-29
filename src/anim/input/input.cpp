#include "input.h"
#include "../units/units.h"
#include "../window/window.h"

namespace tut::anim::input
{
  // Run event pop loop
  VOID system::RunLoop( VOID )
  {
    BOOL ExitFlag {FALSE};
    while (!ExitFlag)
    {
      message InMsg;
      Ctx->MsgQueue.Pop(InMsg);
      std::visit(overloaded {
        [&ExitFlag, &InMsg, this]( auto &Msg )
        {
          using message_type = std::decay_t<decltype(Msg)>;

          Ctx->UnitSystem->OnMessage(InMsg);
          Ctx->InputSystem->OnMessage(InMsg);
          Ctx->WindowSystem->OnMessage(InMsg);

          if (std::is_same_v<message_type, messages::close_message>)
            ExitFlag = TRUE;
          // std::cout << std::format("Mouse motion event - Delta: [{},{}]\n", E.Delta.X, E.Delta.Y);
        },
      }, InMsg);
    }
  } // End of 'RunLoop' function
} // end of 'tut::anim' namespace
