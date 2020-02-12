# FFG API Guide

## Initialization and Main

### Example Main

This is an example of a simple main application entry point. The enginge needs to be declared, configured, and have its states registered before it is ran.

```cpp
// main.cpp
#include "FFG.hpp"
#include "MyState.hpp"

int main(int argc, char **argv) {
    // Initialize the engine.
    FFG_Engine engine;

    // Set window title.
    engine.set_window_title("Hello World!");

    // Set screen mode.
    engine.set_screen_mode(800, 600, FFG_WINDOW_MATCHDESKTOP);

    // Set Vsync.
    engine.set_vsync(true);

    // Register a state.
    MyState my_state(engine); // This inherits from FFG_State.
    unsigned int id = engine.register_state(&my_state);

    // Set the next state.
    engine.set_next_state(id);

    // Run the engine and return the exit code.
    return engine.run();
}
```

### API

#### `void FFG_Renderer::set_window_title(const std::string& window_title)`

Sets the title of the window. By default the title will be "FFG_Engine".

#### `bool FFG_Renderer::set_screen_mode(int width, int height, FFG_WindowMode mode)`

Sets the screen mode to the dimensions specified by the width and height and the screen mode. Right now, only FFG_WINDOW_WINDOWED and FFG_WINDOW_MATCHDESKTOP are supported for mode. Using FFG_WINDOW_MATCHDESKTOP will cause the width and height parameters to be ignored. By default, the screen will be windowed.

#### `void FFG_Renderer::set_vsync(bool vsync)`

Sets Vsync to be either on or off. By default, vsync will be on.

#### `unsigned int FFG_StateManager::register_state(FFG_State* state)`

Registers the state and returns its ID. The first registered state will, by default, be the initial state.

#### `void FFG_StateManager::set_next_state(unsigned int id)`

Registers the state with the ID to be the next state. By default the first registered state will be the initial state. If no states have been registered, the behavior is not defined.

#### `int FFG_Engine::run()`

Runs the engine. Initializes the engine, its components, and the initial state, and then enters the main loop. Once the engine is quit the current state at that time is uninitialized, followed by the engine components and then the engine, and the exit code of 0 is returned.

## Creating a state

### Example state

This is an example of a state. Every state needs to inherit from FFG_State and implement some pure virtual methods.

```cpp
// MyState.hpp
#ifndef MYSTATE_H_INCLUDED
#define MYSTATE_H_INCLUDED

#include "FFG.hpp"

class MyState : public FFG_State {
public:
    MyState(FFG_Engine& engine);
    void init();
    void exit();
    void handle();
    void update();
    void render();
};

#endif // MYSTATE_H_INCLUDED
```

```cpp
// MyState.cpp
#include "MyState.hpp"

MyState::MyState(FFG_Engine& engine) : FFG_State(engine) {
}

void MyState::init() {
}

void MyState::exit() {
}

void MyState::handle() {
}

void MyState::update() {
}

void MyState::render() {
    // As you can see, this is a state that does nothing except clear the screen every frame.
    engine.render_clear();
}
```

### Method overview

#### `void FFG_State::init()`

Initializes the state. It should be noted that unlike the constructor and destructor which will only be called once for the state, a state may be initialized and uninitialized multiple times, once for every time the state is entered and exited, respectively. This should allocate any resources necessary, including texture loading and unloading, if you have any textures that you do not want to persist across states.

#### `void FFG_State::exit()`

Uninitializes the state.

#### `void FFG_State::handle()`

This method is called once for every single event. This means that it may be called once per frame, multiple times per frame, or 0 times per frame. Therefore only event processing should happen here.

#### `void FFG_State::update()`

This method is called once per frame and should contain all updating necessary for the frame.

#### `void FFG_State::render()`

This method is called once per frame and should contain all rendering necessary for the frame. You should call ```engine.render_clear();``` before any rendering is done. What you render will automatically be presented.

### A note on quitting the engine or changing states

In any of `init()`, `exit()`, `handle()`, `update()`, or `render()`, you may quit the application using `engine.quit()` or change the state using `engine.set_next_state()`. As soon as the state method returns, either the engine will be shutdown or the state will be changed, respectively.
