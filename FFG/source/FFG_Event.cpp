#include "FFG_Event.hpp"

/***************************************************************************//**
 * Protected. Constructor.
 ******************************************************************************/
FFG_Event::FFG_Event() {
	type = FFG_EVENT_EMPTY;
	window_type = FFG_EVENT_WINDOW_NONE;
	mouse_button = FFG_EVENT_BUTTON_NONE;
	key_type = FFG_EVENT_KEY_NONE;
	x = 0;
	y = 0;
	key = '\0';
	shift_mod = false;
	ctrl_mod = false;
	alt_mod = false;
	caps_mod = false;
	repeat = false;
	double_click = false;
	handled = false;
}

/***************************************************************************//**
 * Protected. Polls for a new event. Returns true if an event was polled and
 * false if no event was polled.
 * NOTE: This method is core loop critical.
 * @return TRUE if an event was polled, otherwise FALSE.
 ******************************************************************************/
bool FFG_Event::poll_event() {
	type = FFG_EVENT_EMPTY;
	key_type = FFG_EVENT_KEY_NONE;
	mouse_button = FFG_EVENT_BUTTON_NONE;
	window_type = FFG_EVENT_WINDOW_NONE;
	x = 0;
	y = 0;
	key = '\0';
	shift_mod = false;
	ctrl_mod = false;
	alt_mod = false;
	caps_mod = false;
	repeat = false;
	double_click = false;
	handled = false;
	if (!SDL_PollEvent(&event)) return false;
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		// KEYBOARD EVENT:
		if (event.type == SDL_KEYDOWN) {
			type = FFG_EVENT_KEYBOARD_DOWN;
		} else {
			type = FFG_EVENT_KEYBOARD_UP;
		}
		shift_mod = (event.key.keysym.mod & KMOD_LSHIFT || event.key.keysym.mod & KMOD_RSHIFT);
		alt_mod = (event.key.keysym.mod & KMOD_LALT || event.key.keysym.mod & KMOD_RALT);
		ctrl_mod = (event.key.keysym.mod & KMOD_LCTRL || event.key.keysym.mod & KMOD_RCTRL);
		caps_mod = (event.key.keysym.mod & KMOD_CAPS);
		if (event.key.keysym.sym >= 97 && event.key.keysym.sym <= 122) {
			if (shift_mod != caps_mod) {
				key = event.key.keysym.sym - 32;
			} else {
				key = event.key.keysym.sym;
			}
		} else if (event.key.keysym.sym >= 48 && event.key.keysym.sym <= 57) {
			if (shift_mod) {
				key = symbols[event.key.keysym.sym - 48];
			} else {
				key = event.key.keysym.sym;
			}
		} else if (event.key.keysym.sym >= 91 && event.key.keysym.sym <= 93) {
			if (shift_mod) {
				key = symbols[event.key.keysym.sym - 81];
			} else {
				key = event.key.keysym.sym;
			}
		} else if (event.key.keysym.sym == 32) {
			key = ' ';
		} else if (event.key.keysym.sym == 39) {
			key = (shift_mod) ? '\"' : '\'';
		} else if (event.key.keysym.sym == 44) {
			key = (shift_mod) ? '<' : ',';
		} else if (event.key.keysym.sym == 45) {
			key = (shift_mod) ? '_' : '-';
		} else if (event.key.keysym.sym == 46) {
			key = (shift_mod) ? '>' : '.';
		} else if (event.key.keysym.sym == 47) {
			key = (shift_mod) ? '?' : '/';
		} else if (event.key.keysym.sym == 59) {
			key = (shift_mod) ? ':' : ';';
		} else if (event.key.keysym.sym == 61) {
			key = (shift_mod) ? '+' : '=';
		} else if (event.key.keysym.sym == 96) {
			key = (shift_mod) ? '~' : '`';
		}
		if (key == '\0') {
			if (event.key.keysym.sym == SDLK_LSHIFT) {
				key_type = FFG_EVENT_KEY_LSHIFT;
			} else if (event.key.keysym.sym == SDLK_LCTRL) {
				key_type = FFG_EVENT_KEY_LCTRL;
			} else if (event.key.keysym.sym == SDLK_LALT) {
				key_type = FFG_EVENT_KEY_LALT;
			} else if (event.key.keysym.sym == SDLK_RETURN) {
				key_type = FFG_EVENT_KEY_ENTER;
			} else if (event.key.keysym.sym == SDLK_BACKSPACE) {
				key_type = FFG_EVENT_KEY_BACKSPACE;
			} else if (event.key.keysym.sym == SDLK_TAB) {
				key_type = FFG_EVENT_KEY_TAB;
			} else if (event.key.keysym.sym == SDLK_UP) {
				key_type = FFG_EVENT_KEY_UP;
			} else if (event.key.keysym.sym == SDLK_LEFT) {
				key_type = FFG_EVENT_KEY_LEFT;
			} else if (event.key.keysym.sym == SDLK_DOWN) {
				key_type = FFG_EVENT_KEY_DOWN;
			} else if (event.key.keysym.sym == SDLK_RIGHT) {
				key_type = FFG_EVENT_KEY_RIGHT;
			} else if (event.key.keysym.sym == SDLK_ESCAPE) {
				key_type = FFG_EVENT_KEY_ESCAPE;
			}
		} else {
			key_type = FFG_EVENT_KEY_CHAR;
		}
	} else if (event.type == SDL_MOUSEMOTION) {
		// MOUSE MOTION EVENT:
		type = FFG_EVENT_MOUSE_MOTION;
		x = event.motion.x;
		y = event.motion.y;
	} else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
		// MOUSE BUTTON EVENT:
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			type = FFG_EVENT_MOUSE_BUTTON_DOWN;
		} else {
			type = FFG_EVENT_MOUSE_BUTTON_UP;
		}
		x = event.button.x;
		y = event.button.y;
		if (event.button.button == SDL_BUTTON_LEFT) {
			mouse_button = FFG_EVENT_BUTTON_LEFT;
		} else if (event.button.button == SDL_BUTTON_RIGHT) {
			mouse_button = FFG_EVENT_BUTTON_RIGHT;
		} else if (event.button.button == SDL_BUTTON_MIDDLE) {
			mouse_button = FFG_EVENT_BUTTON_MIDDLE;
		}
		if (event.button.clicks > 1) {
			double_click = true;
		}
	} else if (event.type == SDL_MOUSEWHEEL) {
		// MOUSE WHEEL EVENT:
		type = FFG_EVENT_MOUSE_WHEEL_MOTION;
		x = event.wheel.x;
		y = event.wheel.y;
	} else if (event.type == SDL_WINDOWEVENT) {
		// WINDOW EVENT:
		type = FFG_EVENT_WINDOW_EVENT;
		if (event.window.event == SDL_WINDOWEVENT_MINIMIZED) {
			window_type = FFG_EVENT_WINDOW_MINIMIZE;
		} else if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
			window_type = FFG_EVENT_WINDOW_MAXIMIZE;
		} else if (event.window.event == SDL_WINDOWEVENT_FOCUS_LOST) {
			window_type = FFG_EVENT_WINDOW_LOSTFOCUS;
		} else if (event.window.event == SDL_WINDOWEVENT_FOCUS_GAINED) {
			window_type = FFG_EVENT_WINDOW_GAINEDFOCUS;
		}
	} else if (event.type == SDL_QUIT) {
		// QUIT EVENT:
		type = FFG_EVENT_WINDOW_EVENT;
		window_type = FFG_EVENT_WINDOW_CLOSE;
	}
	return true;
}
