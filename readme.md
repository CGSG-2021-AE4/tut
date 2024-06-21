# Tu tu tu tut...
T**** U******** T****

Now it's just anim project. I have some further plans but I am not sure will I be able to finish it. Try to guess the title)).

# Docs:

### Architecture
Major architecture patterns are driven by TAP. TAP has interfaces that provide functionality of certain systems. Their implementations are defined by the user during the initialization.
This approach has too much code for a project like this and different implementations almost always are not needed so this project do not implement interfaces. Yet.
Maybe I will add them in future). Purposes of the systems are mostly the same as in TAP.

Main class - `anim`. It has `context` that contains all global objects like systems, main window, message queue, input state, etc. `anim` initializes and closes systems.

##### Anim initialization:

- `WaitInit` method wait for initialization of system's internal state.
- Initializes public states: input, timer, etc.
- Creates main window.
- `PostInit` methods are invoked after all system are self initialized. Provide context reference for further initialization.
- Binds message queue to window.

### Systems

##### Window system
Now project uses `SDL2` and supports only one window(I am not sure). Window system runs SDL event poll loop, pushes all messages to message queue.

##### Input system
Pops all messages from message queue, sends them to systems: Units, Render?, Windows. Not implemented yet.

##### Units system
Now there is no scenes in project, only units. Not implemented yet.

### Utilities

##### Resource management
There is no resource managers now so now memory management use RAII idiom. For safe resource allocations there are several rules:
- Every resource class has to be derived from abstract class `resource`
- Every resource must be stored only by using `res_ptr` wrapper

Also in future maybe I will add storages. But for the first time it's ok.

##### Asynchronous utilities
Class `spinlock` provides lightweight shared spinlock. It implements STL mutex functions so can be used with STL lock classes.

##### Math
Basic math library. TODO: add noexcept if needed, add rect class.
