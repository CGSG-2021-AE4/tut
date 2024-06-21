//#include "utility/image.h"

#include "anim/anim.h"

using namespace tut;
int main( int argv, char **args )
{
  /* Resource management test * /
  auto *ImgPtr {new image {"AAAA"}};

  {
    res_ptr<image> Img {ImgPtr};
    {
      res_ptr<image> AnotherPtr {std::move(Img)};

      AnotherPtr.Get()->GetFileName();
    }
  }
  /**/

  tut::anim::anim Anim {};

  Anim.Init();

  Anim.Close();

  return 0;
} // End of 'main' function
