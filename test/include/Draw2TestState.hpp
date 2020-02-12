#ifndef DRAW_2_TEST_STATE_H_INCLUDED
#define DRAW_2_TEST_STATE_H_INCLUDED

#include <iostream>
#include "FFG.hpp"
#include "TestSwitchboard.hpp"

class Draw2TestState : public FFG_State {
private:
	TestSwitchboard& switchboard;
public:
	Draw2TestState(FFG_Engine& engine, TestSwitchboard& switchboard);
	void init();
	void exit();
	void handle();
	void update();
	void render();
};

#endif // DRAW_2_TEST_STATE_H_INCLUDED
