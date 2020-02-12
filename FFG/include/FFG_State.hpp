#ifndef FFG_STATE_H_INCLUDED
#define FFG_STATE_H_INCLUDED

#include "FFG_Engine.hpp"

/***************************************************************************//**
 * State implementation. Any user-created states should inherit from this. To
 * execute them, instantiate them and register them through the FFG_StateManager
 * interface prior to the initialization of the engine. The following methods
 * should be overwritten in order to define the behavior of a state:
 *
 *   - FFG_State::FFG_State()
 *   - FFG_State::~FFG_State()
 *   - FFG_State::init()
 *   - FFG_State::exit()
 *   - FFG_State::handle()
 *   - FFG_State::update()
 *   - FFG_State::render()
 *
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_State {
protected:
	/***************************************************************************//**
	 * The engine.
	 ******************************************************************************/
	FFG_Engine& engine;
public:
	/***************************************************************************//**
	 * Constructor.
	 ******************************************************************************/
	FFG_State(FFG_Engine& engine) : engine(engine) {}
	/***************************************************************************//**
	 * Destructor.
	 ******************************************************************************/
	virtual ~FFG_State() {};
	/***************************************************************************//**
	 * Initializes the FFG_State. Called when a state is initialized by FFG_Engine
	 * upon state swapping.
	 ******************************************************************************/
	virtual void init() = 0;
	/***************************************************************************//**
	 * Uninitializes the FFG_State. Called when a state is uninitialized by
	 * FFG_Engine upon state swapping.
	 ******************************************************************************/
	virtual void exit() = 0;
	/***************************************************************************//**
	 * Handles a single event. Refer to FFG_Event.
	 ******************************************************************************/
	virtual void handle() = 0;
	/***************************************************************************//**
	 * Updates the state. Refer to FFG_Timer.
	 ******************************************************************************/
	virtual void update() = 0;
	/***************************************************************************//**
	 * Renders the state. Refer to FFG_Renderer.
	 ******************************************************************************/
	virtual void render() = 0;
};

#endif // FFG_STATE_H_INCLUDED
