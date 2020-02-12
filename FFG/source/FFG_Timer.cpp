#include "FFG_Timer.hpp"

/***************************************************************************//**
 * Protected. Constructor.
 ******************************************************************************/
FFG_Timer::FFG_Timer() {
	start_time = std::chrono::system_clock::from_time_t(0);
	frame_p = 0;
	delta_time_s_p = 0.0;
	delta_time_ms_p = 0;
	delta_time_us_p = 0;
}

/***************************************************************************//**
 * Protected. Stops the timer, recording the number of milliseconds since the
 * last starting of the timer, and then starts the timer. Will also delay if a
 * minimum ticks per frame has been specified.
 * NOTE: This method is core loop critical.
 ******************************************************************************/
void FFG_Timer::start_stop() {
	// Get the current time.
	std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
	// Get the durations.
	std::chrono::duration<double> duration_s = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start_time);
	std::chrono::milliseconds duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
	std::chrono::microseconds duration_us = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time);
	// Get the times from the durations.
	delta_time_s_p = duration_s.count();
	delta_time_ms_p = duration_ms.count();
	delta_time_us_p = duration_us.count();
	frame_p++;
	start_time = current_time;
}

/***************************************************************************//**
 * Protected. Delays the application the specified number of milliseconds.
 * @param ms The number of milliseconds to delay.
 ******************************************************************************/
void FFG_Timer::delay(int ms) const {
	SDL_Delay(ms);
}

/***************************************************************************//**
 * Returns the amount of time between the last two frames in milliseconds. "Last
 * two frames" in this context means between the last two calls to
 * FFG_Timer::start_stop().
 * NOTE: This method is core loop critical.
 * @return The amount of time in milliseconds.
 ******************************************************************************/
double FFG_Timer::delta_time_s() const {
	return delta_time_s_p;
}

/***************************************************************************//**
 * Returns the amount of time between the last two frames in milliseconds. "Last
 * two frames" in this context means between the last two calls to
 * FFG_Timer::start_stop().
 * NOTE: This method is core loop critical.
 * @return The amount of time in milliseconds.
 ******************************************************************************/
int FFG_Timer::delta_time_ms() const {
	return delta_time_ms_p;
}

/***************************************************************************//**
 * Returns the amount of time between the last two frames in milliseconds. "Last
 * two frames" in this context means between the last two calls to
 * FFG_Timer::start_stop().
 * NOTE: This method is core loop critical.
 * @return The amount of time in milliseconds.
 ******************************************************************************/
int FFG_Timer::delta_time_us() const {
	return delta_time_us_p;
}

/***************************************************************************//**
 * Returns the number of frames that have been presented since the program
 * began.
 * NOTE: This method is core loop critical.
 * @return Number of frames.
 ******************************************************************************/
unsigned long FFG_Timer::frame() const {
	return frame_p;
}

/***************************************************************************//**
 * Returns the time since the last frame was rendered, in seconds.
 * @return The frame time in seconds.
 ******************************************************************************/
double FFG_Timer::frame_time_s() const {
	std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration_s = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start_time);
	return duration_s.count();

}

/***************************************************************************//**
 * Returns the time since the last frame was rendered, in milliseconds.
 * @return The frame time in milliseconds.
 ******************************************************************************/
int FFG_Timer::frame_time_ms() const {
	std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
	return duration_ms.count();
}

/***************************************************************************//**
 * Returns the time since the last frame was rendered, in microseconds.
 * @return The frame time in microseconds.
 ******************************************************************************/
int FFG_Timer::frame_time_us() const {
	std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
	std::chrono::microseconds duration_us = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time);
	return duration_us.count();
}
