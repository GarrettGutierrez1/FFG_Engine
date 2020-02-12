#ifndef EVENT_TEST_STATE_H_INCLUDED
#define EVENT_TEST_STATE_H_INCLUDED

#include <iostream>
#include <sstream>
#include "FFG.hpp"
#include "TestSwitchboard.hpp"

class EventTestState : public FFG_State {
private:
	TestSwitchboard& switchboard;
private:
	void print_event();
	void append_type(std::stringstream &ss);
	void append_window_type(std::stringstream &ss);
	void append_mouse_button(std::stringstream &ss);
	void append_key_type(std::stringstream &ss);
	void append_extras(std::stringstream &ss);
public:
	EventTestState(FFG_Engine& engine, TestSwitchboard& switchboard);
	void init();
	void exit();
	void handle();
	void update();
	void render();
};

#endif // EVENT_TEST_STATE_H_INCLUDED
