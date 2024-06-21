#ifndef __image_h_
#define __image_h_

#include "def.h"

#include "resource.h"

namespace tut
{
  class image : public resource
  {
  private:
    std::string FileName;

  public:

    image( std::string_view FileName ) :
      FileName(FileName)
    {
    } // End of 'image' function

    ~image( VOID )
    {
      std::cout << "Image destrutor\n";
      FileName = "";
    }

    std::string_view GetFileName( VOID ) const
    {
      return FileName;
    }

  }; // End of 'image' class
}

#endif // __image_h_
