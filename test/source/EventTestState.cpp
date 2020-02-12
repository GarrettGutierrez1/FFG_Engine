#include "EventTestState.hpp"

void EventTestState::print_event() {
    std::stringstream ss;
    ss << "EVENT|T:";
    append_type(ss);
    ss << "|W:";
    append_window_type(ss);
    ss << "|M:";
    append_mouse_button(ss);
    ss << "|K:";
    append_key_type(ss);
    ss << "|";
    append_extras(ss);
    std::cout << ss.str() << std::endl;
}

void EventTestState::append_type(std::stringstream &ss) {
    switch (engine.type) {
        case FFG_EVENT_EMPTY:
            ss << "________";
            break;
        case FFG_EVENT_KEYBOARD_DOWN:
            ss << "KEY_DOWN";
            break;
        case FFG_EVENT_KEYBOARD_UP:
            ss << "KEY_UP__";
            break;
        case FFG_EVENT_MOUSE_MOTION:
            ss << "MOUSE_M_";
            break;
        case FFG_EVENT_MOUSE_BUTTON_DOWN:
            ss << "MOUSE_D_";
            break;
        case FFG_EVENT_MOUSE_BUTTON_UP:
            ss << "MOUSE_U_";
            break;
        case FFG_EVENT_MOUSE_WHEEL_MOTION:
            ss << "MOUSE_W_";
            break;
        case FFG_EVENT_WINDOW_EVENT:
            ss << "WINDOW__";
            break;
    }
}

void EventTestState::append_window_type(std::stringstream &ss) {
    switch(engine.window_type) {
        case FFG_EVENT_WINDOW_NONE:
            ss << "______";
            break;
	    case FFG_EVENT_WINDOW_MINIMIZE:
            ss << "MIN___";
            break;
	    case FFG_EVENT_WINDOW_MAXIMIZE:
            ss << "MAX___";
            break;
	    case FFG_EVENT_WINDOW_LOSTFOCUS:
            ss << "LFOCUS";
            break;
	    case FFG_EVENT_WINDOW_GAINEDFOCUS:
            ss << "GFOCUS";
            break;
	    case FFG_EVENT_WINDOW_CLOSE:
            ss << "WCLOSE";
            break;
    }
}

void EventTestState::append_mouse_button(std::stringstream &ss) {
    switch(engine.mouse_button) {
        case FFG_EVENT_BUTTON_NONE:
            ss << "______";
            break;
	    case FFG_EVENT_BUTTON_LEFT:
            ss << "LEFT__";
            break;
	    case FFG_EVENT_BUTTON_RIGHT:
            ss << "RIGHT_";
            break;
	    case FFG_EVENT_BUTTON_MIDDLE:
            ss << "MIDDLE";
            break;
    }
}

void EventTestState::append_key_type(std::stringstream &ss) {
    switch (engine.key_type) {
        case FFG_EVENT_KEY_NONE:
            ss << "NONE__";
            break;
	    case FFG_EVENT_KEY_CHAR:
            ss << "CHAR__";
            break;
	    case FFG_EVENT_KEY_LSHIFT:
            ss << "LSHIFT";
            break;
	    case FFG_EVENT_KEY_LCTRL:
            ss << "LCTRL_";
            break;
	    case FFG_EVENT_KEY_LALT:
            ss << "LALT__";
            break;
	    case FFG_EVENT_KEY_ENTER:
            ss << "ENTER_";
            break;
	    case FFG_EVENT_KEY_BACKSPACE:
            ss << "BSPACE";
            break;
	    case FFG_EVENT_KEY_TAB:
            ss << "TAB___";
            break;
	    case FFG_EVENT_KEY_UP:
            ss << "UP____";
            break;
	    case FFG_EVENT_KEY_LEFT:
            ss << "LEFT__";
            break;
	    case FFG_EVENT_KEY_DOWN:
            ss << "DOWN__";
            break;
	    case FFG_EVENT_KEY_RIGHT:
            ss << "RIGHT_";
            break;
	    case FFG_EVENT_KEY_ESCAPE:
            ss << "ESCAPE";
            break;
    }
}

void EventTestState::append_extras(std::stringstream &ss) {
    if (engine.x) ss << " x(" << engine.x << ")";
    if (engine.y) ss << " y(" << engine.y << ")";
    if (engine.key) ss << " key(" << engine.key << ")";
    if (engine.shift_mod) ss << " shift(1)";
    if (engine.ctrl_mod) ss << " ctrl(1)";
    if (engine.alt_mod) ss << " alt(1)";
    if (engine.repeat) ss << " repeat(1)";
    if (engine.double_click) ss << " double(1)";
}

EventTestState::EventTestState(FFG_Engine& engine, TestSwitchboard& switchboard) : FFG_State(engine), switchboard(switchboard) {
}

void EventTestState::init() {
    std::cout << "--> EventTestState." << std::endl;
    std::cout << "\tThis state tests events." << std::endl;
    std::cout << "\tData for every event should be logged." << std::endl;
    std::cout << "\t[    - Go to TimerTestState." << std::endl;
    std::cout << "\t]    - Go to WindowTestState." << std::endl;
}

void EventTestState::exit() {
    std::cout << "<-- EventTestState." << std::endl;
}

void EventTestState::handle() {
    switch(engine.type) {
        case FFG_EVENT_KEYBOARD_UP:
            switch(engine.key_type) {
                case FFG_EVENT_KEY_CHAR:
                    switch(engine.key) {
                        case '{':
                        case '[':
                            engine.set_next_state(switchboard.timer_id);
                            return;
                        case '}':
                        case ']':
                            engine.set_next_state(switchboard.window_id);
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
    print_event();
}

void EventTestState::update() {
}

void EventTestState::render() {
    engine.render_clear();
}
