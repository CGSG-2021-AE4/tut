#ifndef __components_sprite_h_
#define __components_sprite_h_

#include "render/primitives/image.h"

namespace tut::app::components {
  class sprite : public system::object::object {
    private:
    
    system::context *Ctx;
    render::prims::image Img {};

  public:

    void Init( system::context *NewCtx, const std::string &Filename, const ivec3 &NewPos, const ivec3 &NewSize ) { // I use const string & because otherwise I will have to copy string!!
      Ctx = NewCtx;
      Img.Load(Ctx, Filename, NewPos, NewSize);
      object::SetZ(NewPos.Z);
    }
    
    void Init( system::context *NewCtx, res_ptr<render::prims::image_data> ImgData, const ivec3 &NewPos, const ivec3 &NewSize ) { // I use const string & because otherwise I will have to copy string!!
      Ctx = NewCtx;
      Img.Load(Ctx, ImgData, NewPos, NewSize);
      object::SetZ(NewPos.Z);
    }

    void SetImgData( res_ptr<render::prims::image_data> ImgData ) {
      Img.SetImgData(ImgData);
    }
    
    void Close( void ) override {
      Img.Close();
    }

    void Update( void ) override {
      // auto t = std::chrono::steady_clock::now().time_since_epoch().count() / 1000000;
      // Img.SetSize({int((sin((t) / 1000.0) * 0.5 + 0.5) * Img.GetSrcSize().X), int((sin((t) / 1000.0) * 100) * 0.5 + 0.5) * Img.GetSrcSize().Y});
    }

    void HandleWindowResize( const ivec2 &NewWindowSize ) override {
    }
    bool CheckIntersection( const ivec2 &MousePos ) const override {
      return false;
    }
    bool HandleMouse( const system::window::mouse &Mouse ) override {
      return false;
    }

    void Draw( system::render::render_context &RndCtx ) const override {
      Img.Draw(RndCtx);
    }

  };
}

#endif // __components_sprite_h_