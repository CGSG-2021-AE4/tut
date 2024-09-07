
#ifndef __async_h_
#define __async_h_

#include "def.h"

namespace tut::async
{
  constexpr static UINT DeadLockLimit = 1000000;

  // Spinlock - shared and common in one class
  class spinlock
  {
  private:
    std::atomic_int32_t UsersCounter; // If it is in a shared lock state: number of readers
                                      // If it is in a common lock state: -1
  public:

    // Default constructor function.
    spinlock( BOOL DoLock = FALSE ) :
      UsersCounter(DoLock ? -1 : 0)
    {
    } // End of 'spinlock' function

    // Forbidding copy and move
    spinlock( const spinlock & ) = delete;
    spinlock &operator=( const spinlock & ) = delete;
    spinlock( spinlock && ) noexcept = delete;
    spinlock &operator=( spinlock && ) noexcept = delete;

    // Pause 
    static VOID Pause( VOID ) noexcept
    {
#if defined(_M_IX86) || defined(_M_X64)
      // Use pause instruction
      _mm_pause();
#else
      // Emulate waiting be performing simple maths 256 times
      for (volatile UINT i {0}; i < 0x100;)
        i++;
#endif
    } // End of 'Pause' function

    // Long pause
    static VOID LongPause( VOID ) noexcept
    {
      Pause();
      Pause();
      Pause();
      Pause();

      Pause();
      Pause();
      Pause();
      Pause();

      Pause();
      Pause();
      Pause();
      Pause();

      Pause();
      Pause();
      Pause();
      Pause();
    } // End of 'LongPause' function

    // Try to lock as writer
    BOOL try_lock( VOID )
    {
      INT CompareValue = 0; // Need for compare_exchange (wtf stl)

      return UsersCounter.compare_exchange_weak(CompareValue, -1, std::memory_order_acquire);
    } /* End of 'spinlock::try_lock' function */
  
    // Lock as writer
    VOID lock( VOID )
    {
      INT CompareValue = 0; // Need for compare_exchange (wtf stl)

      if (!UsersCounter.compare_exchange_weak(CompareValue, -1, std::memory_order_acquire))
      {
        UINT32 RndVal {(uint32_t)((ptrdiff_t)this >> 4)};
        UINT Counter = 0; // DEBUG

        // Wait
        do
        {
          do
          {
            CompareValue = 0;
            std::this_thread::yield();
            LongPause();

            /* Dynamic pauses amount - [0; 16) */
            for (UINT i {RndVal & 0xF}; i > 0; i--)
              Pause();

            /* Check flag is false now */
            if (UsersCounter.load(std::memory_order_relaxed) == 0)
              break;

            /* Update random value (constants from MSVC++ STL) */
            RndVal *= 0x343FD;
            RndVal += 0x269EC3;
            Counter++;                                  // DEBUG
            if (Counter > DeadLockLimit)                // DEBUG
              throw std::runtime_error {"Deadlock :/"}; // DEBUG
          } while (TRUE);
        } while (!UsersCounter.compare_exchange_weak(CompareValue, -1, std::memory_order_acquire));
      }
    } // End of 'spinlock::lock' function

    // Unlock as writer
    VOID unlock( VOID )
    {
      // DEBUG
      if (UsersCounter.load(std::memory_order_relaxed) > 0)
        throw std::runtime_error {"Spinlock is currently used by reader but tries to unlock as writer."};
      UsersCounter.store(0, std::memory_order_release); // Very unsafe but ok
    } // End of 'unlock' function

    // Lock as reader
    VOID lock_shared( VOID )
    {
      INT CurValue = UsersCounter.load(std::memory_order_relaxed);

      if (CurValue == -1 || (CurValue != -1 && !UsersCounter.compare_exchange_weak(CurValue, CurValue + 1, std::memory_order_acquire)))
      {
        UINT32 RndVal {(uint32_t)((ptrdiff_t)this >> 4)};
        UINT Counter = 0; // DEBUG

        // Wait
        do
        {
          do
          {
            std::this_thread::yield();
            LongPause();

            /* Dynamic pauses amount - [0; 16) */
            for (UINT i {RndVal & 0xF}; i > 0; i--)
              Pause();

            /* Check flag is false now */
            if ((CurValue = UsersCounter.load(std::memory_order_relaxed)) != -1)
              break;

            /* Update random value (constants from MSVC++ STL) */
            RndVal *= 0x343FD;
            RndVal += 0x269EC3;

            // DEBUG
            Counter++;                                  // DEBUG
            if (Counter > DeadLockLimit)                // DEBUG
              throw std::runtime_error {"Deadlock :/"}; // DEBUG
          } while (TRUE);
        } while (!UsersCounter.compare_exchange_weak(CurValue, CurValue + 1, std::memory_order_acquire));
      }
    } // End of 'lock_shared' function

    // Try to lock as reader
    BOOL try_lock_shared( VOID )
    {
       if (INT CurValue = UsersCounter.load(std::memory_order_relaxed); CurValue != -1)
         return UsersCounter.compare_exchange_weak(CurValue, CurValue + 1, std::memory_order_acquire);
       return FALSE;
    } // End of 'try_lock_shared' function

    // Reader unlock
    VOID unlock_shared( VOID )
    {
      // DEBUG check
      if (UsersCounter.load(std::memory_order_relaxed) == -1)
        throw std::runtime_error {"Spinlock is currently used by writer but tries to unlock as reader."};
      UsersCounter.fetch_sub(1, std::memory_order_release);
    } // End of 'unlock_shared' function

  }; // End of 'spinlock' class

  // Analog of channel in GO
  template<typename obj_type>
    class channel
    {
    private:

      std::mutex SyncMutex; // STL DO NOT SUPPORT CONDVAR WITH CUSTOM MUTEX TYPE WTF??????
      std::condition_variable CondVar;
      std::atomic_bool StopFlag {false};
      std::deque<obj_type> Container;

    public:

      // Default constructor
      channel( VOID )
      {
      } // End of 'channel' function

      VOID Push( obj_type &&Obj )
      {
        if (StopFlag.load(std::memory_order_acquire)) { // ... Not very well
          return;
        }
        std::lock_guard Lock(SyncMutex);
        Container.push_front(Obj);
        CondVar.notify_all();
      } // End of 'Push' function

      VOID PushBack( obj_type &&Obj )
      {
        if (StopFlag.load(std::memory_order_acquire)) { // ... Not very well
          return;
        }
        std::lock_guard Lock(SyncMutex);
        Container.push_back(Obj);
        CondVar.notify_all();
      } // End of 'PushBack' function

      VOID Pop( obj_type &Obj )
      {
        std::unique_lock Lock(SyncMutex);
        
        CondVar.wait(Lock, [this]{
          std::printf("%i\n", StopFlag.load());
          return !Container.empty() || StopFlag.load(std::memory_order_acquire);
        });
        if (StopFlag.load(std::memory_order_acquire)) { // ... Not very well
          return;
        }
        Obj = Container.front();
        Container.pop_front();
      } // End of 'Pop' function

      VOID Stop( VOID ) {
        StopFlag.store(true, std::memory_order_release);
        CondVar.notify_all();
      }
      
      BOOL IsStop( VOID ) {
        return StopFlag.load(std::memory_order_acquire);
      }

    }; // End of 'channel' class

} // end of 'tut::async' namespace

#endif // __async_h_
