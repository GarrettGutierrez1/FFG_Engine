#ifndef TIMER_TEST_STATE_H_INCLUDED
#define TIMER_TEST_STATE_H_INCLUDED

#include <iomanip>
#include <iostream>
#include "FFG.hpp"
#include "TestSwitchboard.hpp"

#define PRINT_FRAME 300

class TimerTestState : public FFG_State {
private:
	TestSwitchboard& switchboard;
	unsigned int frame;
public:
	TimerTestState(FFG_Engine& engine, TestSwitchboard& switchboard);
	void init();
	void exit();
	void handle();
	void update();
	void render();
};

#endif // TIMER_TEST_STATE_H_INCLUDED
