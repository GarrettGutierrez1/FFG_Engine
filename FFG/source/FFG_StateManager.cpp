#include "FFG_StateManager.hpp"
#include "FFG_State.hpp"

/***************************************************************************//**
 * Protected. Constructor.
 ******************************************************************************/
FFG_StateManager::FFG_StateManager() {
	current_state = nullptr;
	next_state = nullptr;
}

/***************************************************************************//**
 * Protected. Initializes the state manager. Does not initialize the current
 * state. That is done by the initial call to FFG_StateManager::swap_states() in
 * FFG_Engine.
 ******************************************************************************/
void FFG_StateManager::init() {
	current_state = nullptr;
}

/***************************************************************************//**
 * Protected. Uninitializes the state manager, uninitializing the current state
 * if necessary (I.E. if it exists).
 ******************************************************************************/
void FFG_StateManager::exit() {
	next_state = nullptr;
	if (current_state) {
		current_state->exit();
		current_state = nullptr;
	}
	states.clear();
}

/***************************************************************************//**
 * Protected. Handles the current state.
 * NOTE: This method is core loop critical.
 ******************************************************************************/
void FFG_StateManager::handle() {
	if (current_state) current_state->handle();
}

/***************************************************************************//**
 * Protected. Updates the current state.
 * NOTE: This method is core loop critical.
 ******************************************************************************/
void FFG_StateManager::update() {
	if (current_state) current_state->update();
}

/***************************************************************************//**
 * Protected. Renders the current state.
 * NOTE: This method is core loop critical.
 ******************************************************************************/
void FFG_StateManager::render() {
	if (current_state) current_state->render();
}

/***************************************************************************//**
 * Protected. Swaps the states if a next state has been specified. Does nothing
 * otherwise.
 ******************************************************************************/
void FFG_StateManager::swap_states() {
	if (next_state) {
		if (current_state) current_state->exit();
		current_state = next_state;
		next_state = nullptr;
		if (current_state) current_state->init();
	}
}

/***************************************************************************//**
 * Registers a state and returns its ID. If this is the first state to be
 * registered it will be set to the next state.
 * NOTE: This method is undefined when called during FFG_Engine::run().
 * @param state A pointer to the state.
 * @return The ID of the state.
 ******************************************************************************/
unsigned int FFG_StateManager::register_state(FFG_State* state) {
	states.push_back(state);
	if (!next_state_set() && states.size() == 1) set_next_state(states.size() - 1);
	return states.size() - 1;
}

/***************************************************************************//**
 * Sets the next state. If the ID is invalid this will throw an
 * FFG_STATEMANAGER_BAD_ID exception.
 * @param id The ID of the state.
 ******************************************************************************/
void FFG_StateManager::set_next_state(unsigned int id) {
	next_state = nullptr;
	if (id >= states.size()) throw FFG_STATEMANAGER_OOB_ERROR;
	next_state = states[id];
}

/***************************************************************************//**
 * Cancels the next state.
 ******************************************************************************/
void FFG_StateManager::cancel_next_state() {
	next_state = nullptr;
}

/***************************************************************************//**
 * Indicates if the next state was set.
 * @return TRUE if the next state was set. Otherwise FALSE.
 ******************************************************************************/
bool FFG_StateManager::next_state_set() const {
	if (next_state) return true;
	return false;
}
