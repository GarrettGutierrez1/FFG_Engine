#include "Draw3TestState.hpp"

Draw3TestState::Draw3TestState(FFG_Engine& engine, TestSwitchboard& switchboard) : FFG_State(engine), switchboard(switchboard) {
}

void Draw3TestState::init() {
    std::cout << "--> Draw3TestState." << std::endl;
}

void Draw3TestState::exit() {
    std::cout << "<-- Draw3TestState." << std::endl;
}

void Draw3TestState::handle() {
    switch(engine.type) {
        case FFG_EVENT_KEYBOARD_UP:
            switch(engine.key_type) {
                case FFG_EVENT_KEY_CHAR:
                    switch(engine.key) {
                        case '{':
                        case '[':
                            engine.set_next_state(switchboard.draw_2_id);
                            return;
                        case '}':
                        case ']':
                            engine.set_next_state(switchboard.primitive_id);
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

void Draw3TestState::update() {
}

void Draw3TestState::render() {
    engine.render_clear();
}
