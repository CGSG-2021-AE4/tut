#ifndef __render_h_
#define __render_h_

#include "system/object/object.h"
#include "render_defenitions.h"

namespace tut::system::render {
  class system {
  private:

    context *SysCtx;
    render_context RndCtx;

    // Draw thread
    std::thread DrawThread;
    std::atomic_bool StopDrawFlag {false};
    
  public:

    // Default constructor
    system( void ) {
    } // End of 'system' function

    // Self init
    void WaitInit( void ) {
    } // End of 'WaitInit' function

    void PostInit( context &NewSysCtx ) {
      SysCtx = &NewSysCtx;
      RndCtx.Renderer = SDL_CreateRenderer(SysCtx->MainWindow->Wnd, -1, SDL_RENDERER_ACCELERATED);
      assert(RndCtx.Renderer != nullptr);
    }

    void Close( void ) {
      StopDraw();
      if (DrawThread.joinable())
        DrawThread.join(); // Cannot destoy renderer before end
      SDL_DestroyRenderer(RndCtx.Renderer);
    }

    // Get render context
    render_context & GetRndCtx( void ) {
      return RndCtx;
    }

    // Canvas management
    void ClearCanvas( void ) {
      SDL_SetRenderDrawColor(RndCtx.Renderer, 0, 0, 0, 255);
      SDL_RenderClear(RndCtx.Renderer);
    }

    void PresentCanvas( void ) {
      SDL_RenderPresent(RndCtx.Renderer);
    }

    void StartDraw( std::chrono::microseconds Timeout ) {
      StopDrawFlag.store(false, std::memory_order_release);
      DrawThread = std::thread([this]( std::chrono::microseconds Timeout ){
        while (1) {
          std::chrono::steady_clock::time_point Deadline = std::chrono::steady_clock::now() + Timeout;
          if (StopDrawFlag.load(std::memory_order_acquire)) {
            return;
          }
          ClearCanvas(); // ??
          DrawObjects();
          PresentCanvas();
          std::this_thread::sleep_until(Deadline);
        }
      }, Timeout);
    }

    void StopDraw( void ) {
      StopDrawFlag.store(true, std::memory_order_release);
    }
    
  private:

    // Draw objects in context object manager 
    void DrawObjects( void ) {
      std::lock_guard _Lock(SysCtx->ObjectManager.Mutex);

      for (auto Obj : SysCtx->ObjectManager.Objects) {
        Obj->Draw(RndCtx);
      }
    }
  };
}

#endif // __render_h_