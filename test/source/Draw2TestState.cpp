#include "Draw2TestState.hpp"

Draw2TestState::Draw2TestState(FFG_Engine& engine, TestSwitchboard& switchboard) : FFG_State(engine), switchboard(switchboard) {
}

void Draw2TestState::init() {
    std::cout << "--> Draw2TestState." << std::endl;
}

void Draw2TestState::exit() {
    std::cout << "<-- Draw2TestState." << std::endl;
}

void Draw2TestState::handle() {
    switch(engine.type) {
        case FFG_EVENT_KEYBOARD_UP:
            switch(engine.key_type) {
                case FFG_EVENT_KEY_CHAR:
                    switch(engine.key) {
                        case '{':
                        case '[':
                            engine.set_next_state(switchboard.draw_1_id);
                            return;
                        case '}':
                        case ']':
                            engine.set_next_state(switchboard.draw_3_id);
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

void Draw2TestState::update() {
}

void Draw2TestState::render() {
    engine.render_clear();
}
