#ifndef __units_h_
#define __units_h_

#include "tut.h"
#include "../context.h"

namespace tut::anim
{
  // Unit interface
  class unit abstract
  {
  public:

    // Virtual destructor
    virtual ~unit( VOID )
    {
    } // End of '~unit' function

    virtual VOID Init( context *Ctx ) = 0;
    virtual VOID OnMessage( message &Msg ) = 0;
    virtual VOID Close( VOID ) = 0;
  }; // End of 'unit' class

  class unit_system
  {
  private:
    context *Ctx;
    std::set<unit *> Units;
    async::spinlock UnitsMutex;

  public:

    // Default constructor
    unit_system( VOID )
    {
    } // End of 'unit_system' function

    // Self init
    VOID WaitInit( VOID )
    {
    } // End of 'WaitInit' function

    // Post init
    VOID PostInit( context &InCtx )
    {
      Ctx = &InCtx;
    } // End of 'PostInit' function
    
    // Unit management functions
    template<std::derived_from<unit> unit_type> requires(requires { unit_type(); })
      unit_type * CreateUnit( VOID )
      {
        auto *NewUnit = new unit_type();
        
        {
          std::lock_guard Lock(UnitsMutex);
          Units.emplace(NewUnit);
        }

        NewUnit->Init(Ctx);
        return NewUnit;
      } // End of 'CreateUnit' function

    VOID DestroyUnit( unit *Unit )
    {
      assert(Unit != nullptr); // Assume that Unit is not nullptr

      Unit->Close();
      delete Unit;

      std::lock_guard Lock(UnitsMutex);
      Units.erase(Unit);
    } // End of 'DestroyUnit' function

    VOID Close( VOID )
    {
      // Destroy all the rest units
      std::lock_guard Lock(UnitsMutex);
      for (unit *u : Units)
      {
        u->Close();
        delete u;
      }
      Units.clear();
    } // End of 'Close' function

    // Send messages to all units
    VOID OnMessage( message &Msg )
    {
      std::lock_guard Lock(UnitsMutex); // Not the best way but for the first time ok

      for (unit *u : Units)
        u->OnMessage(Msg);

    } // End of 'OnMessage' function

  }; // End of 'unit_system' class

} // end of 'tut::anim' namespace

#endif // __units_h_