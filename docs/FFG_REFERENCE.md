# FFG Quick Reference

## FFG_Engine API

```cpp
// *********************************************************************************************************************
// FFG_Engine:
//     Initialization:
int FFG_Engine::run();
//     Post-initialization:
void FFG_Engine::quit();
// *********************************************************************************************************************
// FFG_Event:
// - Should only be accessed within handle().
//     Meta:
FFG_EventType FFG_Event::type;
FFG_EventWindowEvent FFG_Event::window_type;
FFG_EventMouseButton FFG_Event::mouse_button;
FFG_EventKey FFG_Event::key_type;
//     engine.type == FFG_EVENT_MOUSE_BUTTON_DOWN || engine.type == FFG_EVENT_MOUSE_BUTTON_UP:
int FFG_Event::x;
int FFG_Event::y;
//     (engine.type == FFG_EVENT_KEYBOARD_DOWN || engine.type == FFG_EVENT_KEYBOARD_UP) && engine.key_type == FFG_EVENT_KEY_CHAR:
char FFG_Event::key;
//     engine.type == FFG_EVENT_KEYBOARD_DOWN:
bool FFG_Event::shift_mod;
bool FFG_Event::ctrl_mod;
bool FFG_Event::alt_mod;
bool FFG_Event::caps_mod;
bool FFG_Event::repeat;
//     engine.type == FFG_EVENT_MOUSE_BUTTON_DOWN:
bool FFG_Event::double_click;
bool FFG_Event::handled;
// *********************************************************************************************************************
// FFG_Renderer:
// - No function except those labeled as initialization should be accessed prior to initialization.
// - No drawing should be done anywhere except render().
//     Initialization:
void FFG_Renderer::set_window_title(const std::string& window_title);
bool FFG_Renderer::set_screen_mode(int width, int height, FFG_WindowMode mode);
void FFG_Renderer::set_vsync(bool vsync);
//     Window Information:
int FFG_Renderer::screen_width() const;
int FFG_Renderer::screen_height() const;
bool FFG_Renderer::get_window_flags(FFG_WindowFlag window_flag);
//     Texture Loading and Unloading:
bool FFG_Renderer::load_texture(FFG_Texture& texture);
void FFG_Renderer::unload_texture(FFG_Texture& texture);
//     Render Target:
bool FFG_Renderer::set_render_target(FFG_Texture& texture);
bool FFG_Renderer::reset_render_target();
//     Texture Drawing:
bool FFG_Renderer::draw(FFG_Texture& texture) const;
bool FFG_Renderer::draw(FFG_Texture& texture, FFG_Rect& source, int screen_x, int screen_y) const;
bool FFG_Renderer::draw(FFG_Texture& texture, FFG_Rect& source, FFG_Rect& destination) const;
//     Primitive Drawing:
bool FFG_Renderer::set_draw_color(int r, int g, int b, int a);
bool FFG_Renderer::draw_pixel(int x, int y);
bool FFG_Renderer::draw_h_line(int y, int x1, int x2);
bool FFG_Renderer::draw_v_line(int x, int y1, int y2);
bool FFG_Renderer::draw_line(int x1, int y1, int x2, int y2);
bool FFG_Renderer::draw_rectangle(int x, int y, int w, int h, bool filled);
bool FFG_Renderer::draw_circle(int x, int y, int r, bool filled);
bool FFG_Renderer::draw_ellipse(int x, int y, int rx, int ry, bool filled);
//     Buffer Control:
bool FFG_Renderer::render_clear();
// *********************************************************************************************************************
// FFG_StateManager:
// - Delcare all your states prior to initialization and then register them.
// - Return immediately after calling set_next_state() in any of handle(), update(), or render() to change states.
//     Initialization Only:
unsigned int FFG_StateManager::register_state(FFG_State* state);
//     Both:
void FFG_StateManager::set_next_state(unsigned int id);
//     Post-initialization Only:
void FFG_StateManager::cancel_next_state();
bool FFG_StateManager::next_state_set() const;
// *********************************************************************************************************************
// FFG_Timer:
// - s: seconds, ms: milliseconds, us: microseconds.
// - Delta time is time between the last two frames.
// - Frame time is the time since the current frame began.
//     Delta Time:
double FFG_Timer::delta_time_s() const;
int FFG_Timer::delta_time_ms() const;
int FFG_Timer::delta_time_us() const;
//     Frame:
unsigned long FFG_Timer::frame() const;
//     Frame Time:
double FFG_Timer::frame_time_s() const;
int FFG_Timer::frame_time_ms() const;
int FFG_Timer::frame_time_us() const;
// *********************************************************************************************************************
// FFG_Texture:
//     Construction:
FFG_Texture::FFG_Texture();
//     Setters:
void FFG_Texture::set(const std::string& path_p);
void FFG_Texture::set(void* const mem_p, const unsigned int size_b_p);
void FFG_Texture::set(const int width_p, const int height_p);
//     Info:
bool FFG_Texture::is_loaded() const;
int FFG_Texture::get_width() const;
int FFG_Texture::get_height() const;
//     Color Modification:
bool FFG_Texture::set_mod_color(int r, int g, int b);
// *********************************************************************************************************************
```

## Entry Point

### Main

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

## State Inheritance

### Declaration

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

### Definition

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
