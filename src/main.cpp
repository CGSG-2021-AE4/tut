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

  tut::anim::anim Anim  {};

  Anim.Init();
  Anim.GetContext().WindowSystem->RunEventPollLoop(); // Limitation of the platform: PollEvent loop has to be in the same thread... SDL WTF?

  Anim.Close();

  return 0;
} // End of 'main' function
