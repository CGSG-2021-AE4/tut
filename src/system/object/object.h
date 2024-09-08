#ifndef __object_h_
#define __object_h_

#include "system/window/window_defenitions.h"
#include "system/render/render_defenitions.h"

namespace tut::system::object {

  // Object that can be places on screen
  class object : public resource {
  private:
    int32_t Z {0};

  public:

    // Visual components
    virtual void Draw( render::render_context &RndCtx ) const = 0;
    virtual void HandleWindowResize( const ivec2 &NewWindowSize ) = 0;

    // Input components
    virtual void Update() = 0;
    virtual bool CheckIntersection( const ivec2 &MousePos ) const = 0;
    virtual bool HandleMouse( const window::mouse &Mouse ) = 0;

    // Closer interface
    virtual void Close( void ) = 0;

    // For sorting
    void SetZ( int32_t NewZ ) {
      Z = NewZ;
    }
    
    int32_t GetZ( void ) const {
      return Z;
    }
  };

  class object_z_comporator {
  public:
    bool operator()( const object *A, const object *B ) const noexcept {
      if (A->GetZ() == B->GetZ()) {
        return A < B;
      }
      return A->GetZ() < B->GetZ();
    }
  };
}

#endif // __object_h_