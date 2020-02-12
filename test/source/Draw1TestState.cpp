#include "Draw1TestState.hpp"

Draw1TestState::Draw1TestState(FFG_Engine& engine, TestSwitchboard& switchboard) : FFG_State(engine), switchboard(switchboard) {
}

void Draw1TestState::init() {
    std::cout << "--> Draw1TestState." << std::endl;
}

void Draw1TestState::exit() {
    std::cout << "<-- Draw1TestState." << std::endl;
}

void Draw1TestState::handle() {
    switch(engine.type) {
        case FFG_EVENT_KEYBOARD_UP:
            switch(engine.key_type) {
                case FFG_EVENT_KEY_CHAR:
                    switch(engine.key) {
                        case '{':
                        case '[':
                            engine.set_next_state(switchboard.window_id);
                            return;
                        case '}':
                        case ']':
                            engine.set_next_state(switchboard.draw_2_id);
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

void Draw1TestState::update() {
}

void Draw1TestState::render() {
    engine.render_clear();
}
