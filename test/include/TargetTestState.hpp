#ifndef TARGET_TEST_STATE_H_INCLUDED
#define TARGET_TEST_STATE_H_INCLUDED

#include <iostream>
#include "FFG.hpp"
#include "TestSwitchboard.hpp"

#define SOLDIER_WIDTH 200
#define SOLDIER_HEIGHT 300

class TargetTestState : public FFG_State {
private:
	TestSwitchboard& switchboard;
	FFG_Texture target_texture;
	int rs[6] = { 82, 138, 102, 143, 238,  89};
	int gs[6] = { 75, 111,  57, 151, 195,  86};
	int bs[6] = { 36,  48,  49,  74, 154,  82};
	int draw_to_x;
	int draw_to_y;
private:
	void redraw_soldier();
public:
	TargetTestState(FFG_Engine& engine, TestSwitchboard& switchboard);
	void init();
	void exit();
	void handle();
	void update();
	void render();
};

#endif // TARGET_TEST_STATE_H_INCLUDED
