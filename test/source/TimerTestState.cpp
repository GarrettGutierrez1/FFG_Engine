#include "TimerTestState.hpp"

TimerTestState::TimerTestState(FFG_Engine& engine, TestSwitchboard& switchboard) : FFG_State(engine), switchboard(switchboard) {
    frame = 0;
}

void TimerTestState::init() {
    frame = 0;
    std::cout << "--> TimerTestState." << std::endl;
    std::cout << "\tThis state tests the timer." << std::endl;
    std::cout << "\tTiming information is logged every 300 frames." << std::endl;
    std::cout << "\t]    - Go to EventTestState." << std::endl;
}

void TimerTestState::exit() {
    std::cout << "<-- TimerTestState." << std::endl;
}

void TimerTestState::handle() {
    switch(engine.type) {
        case FFG_EVENT_KEYBOARD_UP:
            switch(engine.key_type) {
                case FFG_EVENT_KEY_CHAR:
                    switch(engine.key) {
                        case '}':
                        case ']':
                            engine.set_next_state(switchboard.event_id);
                            return;
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

void TimerTestState::update() {
    frame++;
    if (frame % PRINT_FRAME == 0) {
        std::cout << "Frame " << frame;
        std::cout << " Engine frame: " << engine.frame();
        std::cout << " dtime";
        std::cout << " s: " << std::setprecision(2) << std::fixed << engine.delta_time_s();
        std::cout << " ms: " << engine.delta_time_ms();
        std::cout << " us: " << engine.delta_time_us();
        std::cout << " framerate: " << std::setprecision(2) << std::fixed << 1.0 / engine.delta_time_s();
        std::cout << std::endl;
        std::cout << "Frame " << frame;
        std::cout << " Engine frame: " << engine.frame();
        std::cout << " ftime";
        std::cout << " s: " << std::setprecision(2) << std::fixed << engine.frame_time_s();
        std::cout << " ms: " << engine.frame_time_ms();
        std::cout << " us: " << engine.frame_time_us();
        std::cout << " framerate: " << std::setprecision(2) << std::fixed << 1.0 / engine.frame_time_s();
        std::cout << std::endl;
        std::cout << "Window:";
        std::cout << " minimized: " << engine.check_window_flag(FFG_WINFLAG_MINIMIZED);
        std::cout << " maximized: " << engine.check_window_flag(FFG_WINFLAG_MAXIMIZED);
        std::cout << " input focus: " << engine.check_window_flag(FFG_WINFLAG_INPUT_FOCUS);
        std::cout << " mouse focus: " << engine.check_window_flag(FFG_WINFLAG_MOUSE_FOCUS);
        std::cout << std::endl;
    }
}
void TimerTestState::render() {
    engine.render_clear();
}
