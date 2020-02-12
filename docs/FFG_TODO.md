# FFG TODO Document

## TODO List

- [ ] Add support for changing the refresh rate when Vsync is on.
- [ ] Improve documentation with doxygen commands.
- [ ] `FFG_Engine`: Make `FFG_ENGINE_MINIMIZED_WAIT` a variable.
- [ ] Implement component: `FFG_Animation`
- [ ] Implement component: `FFG_AnimationFrame`
- [ ] Implement component: `FFG_Audio`
- [ ] Implement component: `FFG_FixedState`
- [ ] Implement component: `FFG_Flags`
- [ ] Implement component: `FFG_Lua`
- [ ] Implement component: `FFG_Object`
- [ ] Implement component: `FFG_ObjectHex`
- [ ] Implement component: `FFG_Map`
- [ ] Implement component: `FFG_MapHex`
- [ ] Implement component: `FFG_Math`
- [ ] Implement component: `FFG_UI`
- [ ] Implement component: `FFG_XML`

### TODOS

#### Add support for changing the refresh rate when Vsync is on

I need to figure out how it behaves when I try to change it with vsync on. Refresh rates include 60Hz, 120Hz, 144Hz, 240Hz. In order to set a display mode, I need to create an SDL_DisplayMode. I should use the format, w, h, from what I pull.

- <https://wiki.libsdl.org/SDL_DisplayMode> The SDL_DisplayMode struct.
- <https://wiki.libsdl.org/SDL_GetNumVideoDisplays> Gets the number of video displays.
- <https://wiki.libsdl.org/SDL_GetDesktopDisplayMode> Gets the desktop display mode regardless of SDL. Requires an index.
- <https://wiki.libsdl.org/SDL_GetCurrentDisplayMode> Gets the current display mode that SDL is using. Requires an index.
- <https://wiki.libsdl.org/SDL_GetWindowDisplayMode> Gets the display mode when the window is at fullscreen.
- <https://wiki.libsdl.org/SDL_SetWindowDisplayMode> Sets the window display mode when the window is at fullscreen.

#### Improve documentation with doxygen commands

I should look into improving documentation with the following doxygen commands.

- pre: A precondition.
- bug: A bug.
- warning: A warning.
- code: Starts a block of code. Use @code{.cpp} and then end with @endcode.
- todo: A todo.
- image: Displays an image.

#### Implement `FFG_FixedState`

I should implement a class that extends `FFG_State` but has a fixed timestep. `FFG_FixedState::update()` should be private, and instead it should have methods for advancing the state forward in accordance with a timestep.

This class should, fundamentally, do the following:

- Get the delta time.
- Add the remainder time to the delta time (explained in a later bullet point).
- Set the amount of game time to progress to the min of delta time and 0.25 seconds. In other words, if delta time is greater than 0.25 seconds use 0.25 seconds as the delta time instead. This is done to avoid the spiral of death. The slower a computer is, the longer a frame takes, which means the more fixed-time updates it has to do, which means the longer the frame takes, etc. By capping the delta time, the game will just slow down to some relatively constant speed rather than slowing down infinitely.
- Keep updating in increments of 0.01 seconds, subtracting from the delta time each update, until the time remaining is less than 0.01 seconds.
- Set that remainder as the remainder.
- Make a state that is part of the way between the current actual state and the next fixed step state, based on the remainder.
- Render that state.
