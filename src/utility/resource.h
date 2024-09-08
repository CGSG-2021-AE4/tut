#include <iostream>

#ifndef __resource_h_
#define __resource_h_

#include "def.h"

namespace tut
{
  // Resource reference count handler
  class resource abstract
  {
  private:
    std::atomic_uint32_t ReferenceCounter {0};

  public:

    // Default counstructor
    resource( VOID ) noexcept
    {
    } // End of 'resource' function

    // Destructor
    virtual ~resource( VOID ) noexcept
    {
      // For the first time
      assert(ReferenceCounter.load() == 0);
    } // End of '~resource' function

    // Forbidding copy and move
    resource( const resource &Other ) = delete;
    resource & operator=( const resource &Other ) = delete;
    resource( resource &&Other ) noexcept = delete;
    resource & operator=( resource &&Other ) = delete;
  
    // Increase reference counter
    VOID AddReference() noexcept
    {
      ReferenceCounter.fetch_add(1);
    } // End of 'AddRefernce' function
    
    // Decrease reference counter
    VOID RemoveReference() noexcept
    {
      if (ReferenceCounter.fetch_sub(1) == 1)
      {
        // I am using RAII => now there is now resource managers!!!
        // Maybe later I will have to change it
        // No valid refernces => time to destroy
        delete this;
      }
    } // End of 'AddRefernce' function
    
  }; // End of 'resource' class

  // Resource pointer
  template<std::derived_from<resource> res_type>
    class res_ptr
    {
    private:

      res_type *Ptr; // Pointer to resource itself

      // Clear function for moving
      VOID Clear( VOID ) noexcept
      {
        Ptr = nullptr;
      } // End of 'Clear' function

    public:

      // Default constructor
      res_ptr( VOID ) noexcept :
        Ptr {nullptr}
      {
      } // End of 'res_ptr' function

      // Constructor from resource
      res_ptr( res_type *Other ) noexcept :
        Ptr {Other}
      {
        Ptr->AddReference();
      } // End of 'res_ptr' function

      // Release
      VOID Release() noexcept
      {
        if (Ptr != nullptr)
        {
          Ptr->RemoveReference();
          Ptr = nullptr;
        }
      } // End of 'Release' function

      // Reset
      VOID Reset( res_type *Other = nullptr ) noexcept
      {
        Release();
        if (Other != nullptr)
        {
          Ptr = Other;
          Ptr->AddReference();
        }
      } // End of 'Reset' function

      // Copy constructor
      res_ptr( const res_ptr &Other ) noexcept :
        Ptr {Other.Ptr}
      {
        std::cout << "Copy\n";
        Ptr->AddReference();
      } // End of 'res_ptr' function

      // Copy operator
      res_ptr & operator=( const res_ptr &Other ) noexcept
      {
        std::cout << "Copy=\n";
        Reset(Other.Ptr);

        return *this;
      } // End of 'operator=' function

      // Move constructor
      res_ptr( res_ptr &&Other ) noexcept :
        Ptr {Other.Ptr}
      {
        std::cout << "Move\n";
        Other.Clear();
      } // End of 'res_ptr' function

      // Move operator
      res_ptr & operator=( res_ptr &&Other ) noexcept
      {
        std::cout << "Move=\n";
        Release();
        Ptr = Other.Ptr;
        Other.Clear();
        return *this;
      } // End of 'operator=' function

      // Get
      res_type * Get( VOID ) noexcept
      {
        return Ptr;
      } // End of 'Get' function

      const res_type * Get( VOID ) const noexcept
      {
        return Ptr;
      } // End of 'Get' function

      // Overload operators
      // Get
      res_type * operator->( void ) noexcept
      {
        return Get();
      } // End of 'Get' function

      const res_type * operator->( void ) const noexcept
      {
        return Get();
      } // End of 'Get' function


      // Casts TODO

      // Descructor
      ~res_ptr( VOID ) noexcept
      {
        Reset();
      } // End of '~res_ptr' function
    }; // End of 'res_ptr' class

} // end of 'tut' namespace

#endif // __resource_h_
