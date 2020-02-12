#ifndef FFG_ENGINE_H_INCLUDED
#define FFG_ENGINE_H_INCLUDED

#include <climits>
#include <string>
#include "FFG_Constants.hpp"
#include "FFG_Event.hpp"
#include "FFG_Renderer.hpp"
#include "FFG_StateManager.hpp"
#include "FFG_Timer.hpp"

/***************************************************************************//**
 * The engine. Inherits from FFG_Config, FFG_Event, FFG_Renderer,
 * FFG_StateManager, and FFG_Timer. Initialize using:
 *
 *   - FFG_Renderer::set_window_title()
 *   - FFG_Renderer::set_screen_mode()
 *   - FFG_Renderer::set_vsync()
 *   - FFG_StateManager::register_state()
 *   - FFG_StateManager::set_next_state()
 *
 * By default:
 *
 *   - The window title is "FFG_Engine".
 *   - The screen mode is 800x600 windowed.
 *   - Vsync is enabled.
 *   - No states will be registered.
 *   - There will be no next state.
 *
 * Use this engine by creating subclasses of FFG_State and implementing the
 * necessary methods. Then create an instance of FFG_Engine and set its initial
 * attributes using the methods specified above, including registration of the
 * states and setting of the initial state. Then, run the FFG_Engine using
 * FFG_Engine::run(). At any point, if a state should decide that the
 * application should quit, have it call FFG_Engine::quit() and then return.
 * 
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_Engine : public FFG_Event, public FFG_Renderer, public FFG_StateManager, public FFG_Timer {
private:
	bool is_quit;
private:
	void init();
	void exit();
	void handle();
	void update();
	void render();
public:
	FFG_Engine();
	void quit();
	int run();
};

#endif // FFG_ENGINE_H_INCLUDED
