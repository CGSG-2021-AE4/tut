#include "utility/image.h"

using namespace tut;
int main( int argv, char **args )
{
  /*
  std::cout << "CGSG forever!!!\n";

  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    std::runtime_error("SDL Init failed.");

  SDL_Window *window = SDL_CreateWindow("First SDL", 100, 100, 200, 100, SDL_WINDOW_SHOWN);

  if (window == nullptr)
    std::runtime_error("Window creation failed.");

  SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0x00));
  SDL_UpdateWindowSurface(window);

  SDL_Event e;
  bool quit = false;

  while (!quit)
    while (SDL_PollEvent(&e))
      if (e.type == SDL_QUIT)
        quit = true;

  SDL_DestroyWindow(window);
  SDL_Quit();
  */

  auto *ImgPtr {new image {"AAAA"}};

  {
    res_ptr<image> Img {ImgPtr};
    {
      res_ptr<image> AnotherPtr {std::move(Img)};

      AnotherPtr.Get()->GetFileName();
    }
  }

  return 0;
}
