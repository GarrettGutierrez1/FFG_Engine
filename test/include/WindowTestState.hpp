#ifndef WINDOW_TEST_STATE_H_INCLUDED
#define WINDOW_TEST_STATE_H_INCLUDED

#include <chrono>
#include <iostream>
#include <iterator>
#include <sstream>
#include "FFG.hpp"
#include "test_constants.hpp"
#include "TestSwitchboard.hpp"

#define NUM_RESOLUTIONS 13
#define NUM_MODES 2

class WindowTestState : public FFG_State {
private:
	TestSwitchboard& switchboard;
	int on_resolution = 6;
	int on_mode = 0;
	int widths[NUM_RESOLUTIONS] =  {640, 800, 1024, 1280, 1280, 1280, 1366, 1440, 1536, 1600, 1680, 1920, 2560};
	int heights[NUM_RESOLUTIONS] = {480, 600,  768,  720,  800, 1024,  768,  900,  864,  900, 1050, 1080, 1440};
	FFG_WindowMode modes[NUM_MODES] = {FFG_WINDOW_WINDOWED, FFG_WINDOW_MATCHDESKTOP};
private:
	void update_window(int resolution_adj, int mode);
public:
	WindowTestState(FFG_Engine& engine, TestSwitchboard& switchboard);
	void init();
	void exit();
	void handle();
	void update();
	void render();
};

#endif // WINDOW_TEST_STATE_H_INCLUDED
