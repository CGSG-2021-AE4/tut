#ifndef __unit_test_h_
#define __unit_test_h_

#include <iostream>

#include "tut.h"
#include "anim/anim.h"
#include "anim/units/units.h"

namespace tut::units
{
  class unit_test : public tut::anim::unit
  {
  public:

    // Default constructor
    unit_test( VOID )
    {
    } // End of 'unit_test' function

    VOID Init( anim::context *Ctx ) override
    {
    } // End of 'Init' function

    VOID OnMessage( anim::message &Msg ) override
    {
      std::cout << "Got msg\n";
    } // End of 'OnMessage' function

    VOID Close( VOID ) override
    {
    } // End of 'Close' function

  }; // End of 'unit_test' function

} // end of 'tut::units' namespace

#endif // __unit_test_h_