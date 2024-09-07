#ifndef __object_manager_h_
#define __object_manager_h_

#include "object.h"

namespace tut::system::object {
  class manager {
  private:
    bool ObjectsChanged {false}; // For situations when objects are being changed during loop

    std::thread AddObjThread, RemoveObjThread;
    async::channel<object *> AddChan, RemoveChan;

  public:
    std::set<object *, object_z_comporator> Objects {};
    async::spinlock Mutex;

    // Default constructor
    manager() :
      AddObjThread(&manager::AddLoop, this),
      RemoveObjThread(&manager::RemoveLoop, this)
    {
    }
    ~manager() {
      AddChan.Stop();
      RemoveChan.Stop();

      AddObjThread.join();
      RemoveObjThread.join();
    }

    void Add( object *NewObj ) {
      AddChan.Push(std::forward<object *>(NewObj));
    }

    bool Remove( object *DelObj ) {
      RemoveChan.Push(std::forward<object *>(DelObj));
    }

  private:

    void AddLoop( void ) {
      while (1) {
        object *NewObj;
        AddChan.Pop(NewObj);
        if (AddChan.IsStop()) {
          return;
        }
        AddSync(NewObj);
      }
    }
    void RemoveLoop( void ) {
      while (1) {
        object *DelObj;
        RemoveChan.Pop(DelObj);
        if (RemoveChan.IsStop()) {
          return;
        }
        RemoveSync(DelObj);
      }
    }


    void AddSync( object *NewObj ) {
      std::lock_guard _Lock(Mutex);

      ObjectsChanged = true;
      Objects.insert(NewObj);
    }

    bool RemoveSync( object *DelObj ) {
      std::lock_guard _Lock(Mutex);

      ObjectsChanged = true;
      if (auto Iter = Objects.find(DelObj); Iter != Objects.end()) {
        Objects.erase(Iter);
        return true;
      }
      return false;
    }

  };
}

#endif // __object_manager_h_