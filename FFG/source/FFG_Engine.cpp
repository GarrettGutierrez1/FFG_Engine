#include "FFG_Engine.hpp"

/***************************************************************************//**
 * Constructor.
 ******************************************************************************/
FFG_Engine::FFG_Engine() {
	is_quit = false;
}

/***************************************************************************//**
 * Private. Initializes the engine's modules.
 ******************************************************************************/
void FFG_Engine::init() {
	FFG_Renderer::init();
	FFG_StateManager::init();
}

/***************************************************************************//**
 * Private. Uninitializes the engine's modules.
 ******************************************************************************/
void FFG_Engine::exit() {
	FFG_StateManager::exit();
	FFG_Renderer::exit();
}

/***************************************************************************//**
 * Private. Handles all events in the queue, either within the engine or by
 * passing the event to the state manager. Window close events are handled by
 * the engine. The rest are passed to the current state. Events will be handled
 * until there either are no more events to handle, the next state is set, or
 * the engine is set to quit.
 * NOTE: This method is core loop critical.
 ******************************************************************************/
void FFG_Engine::handle() {
	while (FFG_Event::poll_event()) {
		if(FFG_StateManager::next_state_set() || is_quit) {
			break;
		}
		if (FFG_Event::type == FFG_EVENT_WINDOW_EVENT) {
			if (FFG_Event::window_type == FFG_EVENT_WINDOW_CLOSE) {
				is_quit = true;
				return;
			}
		}
		FFG_StateManager::handle();
	}
}

/***************************************************************************//**
 * Private. Updates the current state.
 * NOTE: This method is core loop critical.
 ******************************************************************************/
void FFG_Engine::update() {
	FFG_StateManager::update();
}

/***************************************************************************//**
 * Private. Renders the current state if the window is in focus. The buffer is
 * automatically presented. If the window is out of focus, will delay.
 * NOTE: This method is core loop critical.
 ******************************************************************************/
void FFG_Engine::render() {
	FFG_StateManager::render();
	if (!FFG_StateManager::next_state_set() && !is_quit) {
		FFG_Renderer::present();
	}
	if (FFG_Renderer::check_window_flag(FFG_WINFLAG_MINIMIZED)) {
		FFG_Timer::delay(FFG_ENGINE_MINIMIZED_WAIT);
	}
	FFG_Timer::start_stop();
}

/***************************************************************************//**
 * Signifies the engine to quit when possible. Will quit after the conclusion
 * its substate's handle(), update(), render(), init(), or exit() method.
 ******************************************************************************/
void FFG_Engine::quit() {
	is_quit = true;
	FFG_StateManager::cancel_next_state();
}

/***************************************************************************//**
 * Runs the engine.
 * NOTE: This method is core loop critical.
 * @return 0 in all cases.
 ******************************************************************************/
int FFG_Engine::run() {
	// Initialize all subcomponents:
	init();
	while (true) {
		// If told to quit in the previous iteration of this loop, quit:
		if (is_quit) break;
		// Keeps initializing the next state as long as one is waiting or until told to quit:
		while (FFG_StateManager::next_state_set()) {
			FFG_StateManager::swap_states();
			if (is_quit) {
				break;
			}
		}
		// Quit if indicated to do so by state init or exit:
		if (is_quit) break;
		while (true) {
			// Handle all events in the event queue:
			handle();
			// If the next state was set, or if the engine was told to quit, stop this loop:
			if (FFG_StateManager::next_state_set() || is_quit) break;
			// Update:
			update();
			// If the next state was set, or if the engine was told to quit, stop this loop:
			if (FFG_StateManager::next_state_set() || is_quit) break;
			// Render:
			render();
			// If the next state was set, or if the engine was told to quit, stop this loop:
			if (FFG_StateManager::next_state_set() || is_quit) break;
		}
	}
	// Uninitialize all the subcomponents:
	exit();
	return 0;
}
