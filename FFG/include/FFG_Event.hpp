#ifndef FFG_EVENT_H_INCLUDED
#define FFG_EVENT_H_INCLUDED

#include <SDL2\SDL.h>
#include "FFG_Constants.hpp"

/***************************************************************************//**
 * Event representation. Is inherited by FFG_Engine. Access the most recent
 * event through the public data members.
 * 
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_Event {
private:
	SDL_Event event;
	char symbols[13] = { ')','!','@','#','$','%','^','&','*','(','{','|','}' };
protected:
	FFG_Event();
	bool poll_event();
public:
	/***************************************************************************//**
	 * The type of event. FFG_EVENT_EMPTY by default.
	 ******************************************************************************/
	FFG_EventType type;
	/***************************************************************************//**
	 * The type of window event. FFG_EVENT_WINDOW_NONE by default.
	 ******************************************************************************/
	FFG_EventWindowEvent window_type;
	/***************************************************************************//**
	 * The type of mouse button event. FFG_EVENT_BUTTON_NONE by default.
	 ******************************************************************************/
	FFG_EventMouseButton mouse_button;
	/***************************************************************************//**
	 * The type of key event. FFG_EVENT_KEY_NONE by default.
	 ******************************************************************************/
	FFG_EventKey key_type;
	/***************************************************************************//**
	 * If type is FFG_EVENT_MOUSE_BUTTON_DOWN or FFG_EVENT_MOUSE_BUTTON_UP, the
	 * x-coordinate of the event on the window.
	 ******************************************************************************/
	int x;
	/***************************************************************************//**
	 * If type is FFG_EVENT_MOUSE_BUTTON_DOWN or FFG_EVENT_MOUSE_BUTTON_UP, the
	 * y-coordinate of the event on the window.
	 ******************************************************************************/
	int y;
	/***************************************************************************//**
	 * If keyType is FFG_EVENT_KEY_CHAR, the char of the key that was pressed.
	 ******************************************************************************/
	char key;
	/***************************************************************************//**
	 * If type is FFG_EVENT_KEYBOARD_DOWN, TRUE if shift was held down.
	 ******************************************************************************/
	bool shift_mod;
	/***************************************************************************//**
	 * If type is FFG_EVENT_KEYBOARD_DOWN, TRUE if ctrl was held down.
	 ******************************************************************************/
	bool ctrl_mod;
	/***************************************************************************//**
	 * If type is FFG_EVENT_KEYBOARD_DOWN, TRUE if alt was held down.
	 ******************************************************************************/
	bool alt_mod;
	/***************************************************************************//**
	 * If type is FFG_EVENT_KEYBOARD_DOWN, TRUE if caps lock was on.
	 ******************************************************************************/
	bool caps_mod;
	/***************************************************************************//**
	 * If type is FFG_EVENT_KEYBOARD_DOWN, TRUE if this is a repeat event.
	 ******************************************************************************/
	bool repeat;
	/***************************************************************************//**
	 * If type is FFG_EVENT_MOUSE_BUTTON_DOWN, TRUE if this was a double click.
	 ******************************************************************************/
	bool double_click;
	/***************************************************************************//**
	 * An indicator if the event was handled. Always defaults to FALSE but can be
	 * changed by a state if necessary.
	 ******************************************************************************/
	bool handled;
};

#endif // FFG_EVENT_H_INCLUDED
