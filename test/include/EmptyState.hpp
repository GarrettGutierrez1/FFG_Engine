#ifndef EMPTY_STATE_H_INCLUDED
#define EMPTY_STATE_H_INCLUDED

#include "FFG.hpp"

class EmptyState : public FFG_State {
public:
	EmptyState(FFG_Engine& engine);
	void init();
	void exit();
	void handle();
	void update();
	void render();
};

#endif // EMPTY_STATE_H_INCLUDED
