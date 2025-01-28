//#include "utility/image.h"

#include "system/context.h"
#include "system/window/window.h"
#include "system/input/input.h"
#include "system/object/object_manager.h"
#include "system/render/render.h"

#include "app/components/sprite.h"

using namespace tut;

int main( int argv, char **args )
{
  // Now I allocate systems here
  // Later will remove it
  // I store them as poiters because it retaines possibility of several implementation in future
  system::context Ctx;

  Ctx.WindowSystem = new system::window::system();
  Ctx.InputSystem = new system::input::system();
  Ctx.RenderSystem = new system::render::system();
  // Self init
  Ctx.WindowSystem->WaitInit();
  Ctx.InputSystem->WaitInit();
  Ctx.RenderSystem->WaitInit();
  
  // Init variables
  // Create main window
  Ctx.MainWindow = Ctx.WindowSystem->CreateWindow("TUT main window",
                                                  ivec2 {100, 100},
                                                  isize2 {300, 200},
                                                  SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (Ctx.MainWindow == nullptr)
    throw std::exception("Main window creation error");
  // Create object manager
  
  // Post init
  Ctx.WindowSystem->PostInit(Ctx);
  Ctx.InputSystem->PostInit(Ctx);
  Ctx.RenderSystem->PostInit(Ctx);

  // Validate if everything is right
  Ctx.Validate();

  Ctx.RenderSystem->StartDraw(std::chrono::microseconds(10000));

  // TEST START
  app::components::sprite Sprite {};
  Sprite.Init(&Ctx, std::string(BinDirPathPrefix) + "/man1.png", {10, 10, 10}, {100, 100, 100});
  Ctx.ObjectManager.Add(&Sprite);
  // TEST END

  // Main loop
  Ctx.WindowSystem->RunEventPollLoop(); // Limitation of the platform: PollEvent loop has to be in the same thread... SDL WTF?

  Ctx.RenderSystem->StopDraw();

  Sprite.Close();


  // Destroy main window
  Ctx.WindowSystem->DestroyWindow(Ctx.MainWindow);

  // Closing systems
  Ctx.RenderSystem->Close();
  Ctx.InputSystem->Close();
  Ctx.WindowSystem->Close();

  // Deallocate context
  delete Ctx.RenderSystem;
  delete Ctx.InputSystem;
  delete Ctx.WindowSystem;

  // tut::anim::anim Anim  {};
  // 
  // Anim.Init();
  // 
  // // Units
  // auto *u = Anim.GetContext().UnitSystem->CreateUnit<units::unit_test>();
  // 
  // Anim.GetContext().WindowSystem->RunEventPollLoop(); // Limitation of the platform: PollEvent loop has to be in the same thread... SDL WTF?
  // 
  // Anim.Close();
  return 0;
} // End of 'main' function
