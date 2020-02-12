#include "PrimitiveTestState.hpp"

PrimitiveTestState::PrimitiveTestState(FFG_Engine& engine, TestSwitchboard& switchboard) : FFG_State(engine), switchboard(switchboard) {
}

void PrimitiveTestState::init() {
    std::cout << "--> PrimitiveTestState." << std::endl;
}

void PrimitiveTestState::exit() {
    std::cout << "<-- PrimitiveTestState." << std::endl;
}

void PrimitiveTestState::handle() {
    switch(engine.type) {
        case FFG_EVENT_KEYBOARD_UP:
            switch(engine.key_type) {
                case FFG_EVENT_KEY_CHAR:
                    switch(engine.key) {
                        case '{':
                        case '[':
                            engine.set_next_state(switchboard.draw_3_id);
                            return;
                        case '}':
                        case ']':
                            engine.set_next_state(switchboard.target_id);
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

void PrimitiveTestState::update() {
}

void PrimitiveTestState::render() {
    engine.render_clear();
}
