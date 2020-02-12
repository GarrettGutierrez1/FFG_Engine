#ifndef FFG_STATEMANAGER_H_INCLUDED
#define FFG_STATEMANAGER_H_INCLUDED

#include <string>
#include <vector>
#include "FFG_Constants.hpp"

class FFG_State;

/***************************************************************************//**
 * State manager representation. Is inherited by FFG_Engine. Handles all forms
 * of state control, including registering, loading, and unloading states.
 * Methods relevant to FFG_Engine initial setup are:
 *
 *   - FFG_StateManager::register_state()
 *   - FFG_StateManager::set_next_state()
 * 
 * Engine runtime interface methods are:
 *
 *   - FFG_StateManager::set_next_state()
 *   - FFG_StateManager::cancel_next_state()
 *   - FFG_StateManager::next_state_set()
 *
 * States are referenced by unsigned int IDs returned when they are registered.
 * 
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_StateManager {
private:
	std::vector<FFG_State*> states;
	FFG_State* current_state;
	FFG_State* next_state;
protected:
	FFG_StateManager();
	void init();
	void exit();
	void handle();
	void update();
	void render();
	void swap_states();
public:
	unsigned int register_state(FFG_State* state);
	void set_next_state(unsigned int id);
	void cancel_next_state();
	bool next_state_set() const;
};

#endif // FFG_STATEMANAGER_H_INCLUDED
