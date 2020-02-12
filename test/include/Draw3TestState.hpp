#ifndef DRAW_3_TEST_STATE_H_INCLUDED
#define DRAW_3_TEST_STATE_H_INCLUDED

#include <iostream>
#include "FFG.hpp"
#include "TestSwitchboard.hpp"

class Draw3TestState : public FFG_State {
private:
	TestSwitchboard& switchboard;
public:
	Draw3TestState(FFG_Engine& engine, TestSwitchboard& switchboard);
	void init();
	void exit();
	void handle();
	void update();
	void render();
};

#endif // DRAW_3_TEST_STATE_H_INCLUDED
