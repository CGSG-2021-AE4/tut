#include <string>
#include <string_view>
#include <iostream>

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

    VOID Destroy( VOID ) noexcept override
    {
      std::cout << "Image destroy\n";
      //FileName.clear();
    }
  }; // End of 'image' class
}
