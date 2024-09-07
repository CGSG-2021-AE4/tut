#ifndef __render_h_
#define __render_h_

#include "system/object/object.h"
#include "render_defenitions.h"

namespace tut::system::render {
  class system {
  private:

    context *SysCtx;
    render_context Ctx;

  public:

    // Default constructor
    system( void ) {
    } // End of 'system' function

    // Self init
    void WaitInit( void ) {
    } // End of 'WaitInit' function

    void PostInit( context &NewSysCtx ) {
      SysCtx = &NewSysCtx;
      Ctx.Renderer = SDL_CreateRenderer(SysCtx->MainWindow->Wnd, -1, SDL_RENDERER_ACCELERATED);
      assert(Ctx.Renderer != nullptr);
    }

    void Close( void ) {
      SDL_DestroyRenderer(Ctx.Renderer);
    }

    // Canvas management
    void ClearCanvas( void ) {
      SDL_SetRenderDrawColor(Ctx.Renderer, 0, 0, 0, 255);
      SDL_RenderClear(Ctx.Renderer);
    }

    // Draw objects in context object manager 
    void DrawObjects( void ) {
      std::lock_guard _Lock(SysCtx->ObjectManager.Mutex);

    }

    void PresentCanvas( void ) {
      SDL_RenderPresent(Ctx.Renderer);
    }
  };
}

#endif // __render_h_