#ifndef __image_h_
#define __image_h_

#include "utility/resource.h"
#include "system/context.h"

namespace tut::render::prims {
  class image;

  class image_data : public resource {
  protected:
    friend class image;

    system::context *Ctx {nullptr};
    SDL_Texture *Img {nullptr};
    
  public:

    void Load( system::context *NewCtx, const std::string &Filename ) {
      Ctx = NewCtx;

      Img = IMG_LoadTexture(Ctx->RenderSystem->GetRndCtx().Renderer, Filename.c_str());
    }

    bool IsLoaded( void ) const noexcept {
      return Img != nullptr;
    }

    void Close() {
      if (Img != nullptr) {
        SDL_DestroyTexture(Img);
        Img = nullptr;
      }
      Ctx = nullptr;
    }

    ~image_data() {
      Close();
    }
  };

  class image : public resource {
  private:

    res_ptr<image_data> Data;
    SDL_Rect Rect;
    ivec2 SrcSize {};
    
  public:

    void Load( system::context *NewCtx, const std::string &Filename, const ivec3 &NewPos, const ivec3 &NewSize ) { // I use const string & because otherwise I will have to copy string!!
      // Load data
      res_ptr<image_data> NewData = new image_data();
      NewData->Load(NewCtx, Filename);
      if (NewData->Img == nullptr) {
        std::println("ERROR: failed to load image{}", Filename);
        return;
      }
      SetImgData(NewData);

      // Save rectangle
      Rect.x = NewPos.X;
      Rect.y = NewPos.Y;
      if (NewSize.X == 0 && NewSize.Y == 0) {
        Rect.w = SrcSize.X;
        Rect.h = SrcSize.Y;
      } else {
        Rect.w = NewSize.X;
        Rect.h = NewSize.Y;
      }
    }

    void Load( system::context *NewCtx, res_ptr<image_data> NewData, const ivec3 &NewPos, const ivec3 &NewSize ) {
      // Load data
      SetImgData(NewData);
      
      // Save rectangle
      Rect.x = NewPos.X;
      Rect.y = NewPos.Y;
      Rect.w = NewSize.X;
      Rect.h = NewSize.Y;
    }

    bool IsLoaded( void ) const noexcept {
      return Data->IsLoaded();
    }

    // Resets image data 
    void SetImgData( res_ptr<image_data> NewData ) {
      Data = NewData;
      SDL_QueryTexture(Data->Img, NULL, NULL, &SrcSize.X, &SrcSize.Y);
    }
    
    ivec2 GetPos( void ) const {
      return {Rect.x, Rect.y};
    }
    
    ivec2 GetSize( void ) const {
      return {Rect.w, Rect.h};
    }

    ivec2 GetSrcSize( void ) const {
      return SrcSize;
    }

    void SetPos( const ivec2 &NewPos ) {
      Rect.x = NewPos.X;
      Rect.y = NewPos.Y;
    }
    
    void SetSize( const ivec2 &NewSize ) {
      Rect.w = NewSize.X;
      Rect.h = NewSize.Y;
    }

    void Close() {
      // Data->Close(); // No because texture can be reused
    }

    void Draw( system::render::render_context &Ctx ) const {
      SDL_RenderCopy(Ctx.Renderer, Data->Img, nullptr, &Rect);
    }

    bool IsIn( const ivec2 &Point ) const {
      return
        Point.X >= Rect.x && Point.X <= Rect.x + Rect.w &&
        Point.Y >= Rect.y && Point.Y <= Rect.y + Rect.h;
    }

  };
}

#endif // __image_h_