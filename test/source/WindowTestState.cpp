#include "WindowTestState.hpp"

void WindowTestState::update_window(int resolution_adj, int mode) {
    // Calculate the appropriate indices.
    on_resolution = (NUM_RESOLUTIONS + ((on_resolution + resolution_adj) % NUM_RESOLUTIONS)) % NUM_RESOLUTIONS;
    if (mode < 0) mode = on_mode;
    on_mode = mode % NUM_MODES;
    // Generate the console message and the new title.
    std::stringstream ss_message;
    std::stringstream ss_title;
    ss_message << "Setting screen to resolution: " << on_resolution << ": " << widths[on_resolution] << "x" << heights[on_resolution] << ", mode: ";
    ss_title << "WINDOW TEST: " << widths[on_resolution] << "x" << heights[on_resolution] << " ";
    switch(modes[on_mode]) {
        case FFG_WINDOW_WINDOWED:
            ss_message << "windowed";
            ss_title << "WINDOWED";
            break;
        case FFG_WINDOW_MATCHDESKTOP:
            ss_message << "desktop";
            ss_title << "DESKTOP";
            break;
    }
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    if(engine.set_screen_mode(widths[on_resolution], heights[on_resolution], modes[on_mode])) throw SET_WINDOW_MODE_FAIL;
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    ss_message << " took " << duration_ms.count() << " milliseconds. Actual resolution: " << engine.screen_width() << "x" << engine.screen_height() << ".";
    // Update the console and title.
    std::cout << ss_message.str() << std::endl;
    engine.set_window_title(ss_title.str());
}

WindowTestState::WindowTestState(FFG_Engine& engine, TestSwitchboard& switchboard) : FFG_State(engine), switchboard(switchboard) {
}

void WindowTestState::init() {
    std::cout << "--> WindowTestState." << std::endl;
    std::cout << "\tThis state tests changing the window resolution and mode during runtime." << std::endl;
    std::cout << "\tThe current resolution and mode is logged via the window title." << std::endl;
    std::cout << "\t[    - Go to EventTestState." << std::endl;
    std::cout << "\t]    - Go to Draw1TestState." << std::endl;
    std::cout << "\tWASD - Change window resolution." << std::endl;
    std::cout << "\t1    - Change window mode to windowed." << std::endl;
    std::cout << "\t2    - Change window mode to match desktop." << std::endl;
    if(engine.load_texture(switchboard.screen_resolutions)) throw LOAD_TEXTURE_FAIL;
    update_window(0, 0);
}

void WindowTestState::exit() {
    std::cout << "<-- WindowTestState." << std::endl;
    engine.unload_texture(switchboard.screen_resolutions);
}

void WindowTestState::handle() {
    switch(engine.type) {
        case FFG_EVENT_KEYBOARD_UP:
            switch(engine.key_type) {
                case FFG_EVENT_KEY_CHAR:
                    switch(engine.key) {
                        case '{':
                        case '[':
                            engine.set_next_state(switchboard.event_id);
                            break;
                        case '}':
                        case ']':
                            engine.set_next_state(switchboard.draw_1_id);
                            break;
                        case 'W':
                        case 'w':
                            update_window(-1, -1);
                            break;
                        case 'A':
                        case 'a':
                            update_window(-1, -1);
                            break;
                        case 'S':
                        case 's':
                            update_window(1, -1);
                            break;
                        case 'D':
                        case 'd':
                            update_window(1, -1);
                            break;
                        case '1':
                        case '!':
                            update_window(0, 0);
                            break;
                        case '2':
                        case '@':
                            update_window(0, 1);
                            break;
                        default:
                            break;
                    } // switch(engine.key)
                    break;
                case FFG_EVENT_KEY_ESCAPE:
                    engine.quit();
                    return;
                default:
                    break;
            } // switch(engine.key_type)
            break;
        default:
            break;
    } // switch(engine.type)
}

void WindowTestState::update() {
}

void WindowTestState::render() {
    if(engine.render_clear()) throw RENDER_CLEAR_FAIL;
    FFG_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = switchboard.screen_resolutions.get_width();
    source.h = switchboard.screen_resolutions.get_height();
    engine.draw(switchboard.screen_resolutions, source, 0, 0);
}
