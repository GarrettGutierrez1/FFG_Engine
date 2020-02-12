#ifndef DRAW_1_TEST_STATE_H_INCLUDED
#define DRAW_1_TEST_STATE_H_INCLUDED

#include <iostream>
#include "FFG.hpp"
#include "TestSwitchboard.hpp"

class Draw1TestState : public FFG_State {
private:
	TestSwitchboard& switchboard;
public:
	Draw1TestState(FFG_Engine& engine, TestSwitchboard& switchboard);
	void init();
	void exit();
	void handle();
	void update();
	void render();
};

#endif // DRAW_1_TEST_STATE_H_INCLUDED
