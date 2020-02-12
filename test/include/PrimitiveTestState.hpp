#ifndef PRIMITIVE_TEST_STATE_H_INCLUDED
#define PRIMITIVE_TEST_STATE_H_INCLUDED

#include <iostream>
#include "FFG.hpp"
#include "TestSwitchboard.hpp"

class PrimitiveTestState : public FFG_State {
private:
	TestSwitchboard& switchboard;
public:
	PrimitiveTestState(FFG_Engine& engine, TestSwitchboard& switchboard);
	void init();
	void exit();
	void handle();
	void update();
	void render();
};

#endif // PRIMITIVE_TEST_STATE_H_INCLUDED
