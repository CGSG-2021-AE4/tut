# Tu tu tu tut...
T***** U******** T****
Some architecture patterns are driven by TAP, for example global context, message queue.

---
# Some docs:

## Architecture
In TAP there are interfaces that porvided functionality of certain system and their implementations.
This way has too mach code and different implementation almost always are not needed so now there is no interfaces. Maybe I will add them in future).
Purposes of systems are mostly the same as in TAP.

Main class - anim. It has context that contains programm systems. Anim class inits and closes systems.

Initialization:

- WaitInit method wait for init of system's internal state.
- Inits public states: input, timer, etc.
- Creates main window.
- PostInit methods are invoked after all system are self inited. Provide context reference for futher init.
- Binds msg queue to window.

---

## Systems

### Window system
Now it uses SDL2. Now system supports only one window. Runs SDL event poll loop, pushes all messages to message queue.

### Input system
Pops all messages from message queue, sends them to systems: Units, Render?, Window.

### Units system
Now there is no scenes in project, only units.

---

## Utilities

### Resource management
There is no resoure managers now so memory management use RAII idiom. For safe resource allocations there are several rules:
- Every resource class has to be derived from resource abstract class(resource)
- Every resource must be stored only by using pointer wrapper(res_ptr)

### Asynchronous utilities
Class spinlock provides lightweight shared spinlock. It implements STL mutex functions so can be used with STL lock classes.

---

