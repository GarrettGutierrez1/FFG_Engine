#ifndef FFG_TIMER_H_INCLUDED
#define FFG_TIMER_H_INCLUDED

#include <chrono>
#include <SDL2/Sdl.h>
#include <thread>
#include "FFG_Constants.hpp"

/***************************************************************************//**
 * Timer representation. Is inherited by FFG_Engine. Delta time and the current
 * frame. Methods relevant to FFG_Engine initial setup are:
 *
 * Engine runtime interface methods are:
 *
 *   - FFG_Timer::delta_time_s()
 *   - FFG_Timer::delta_time_ms()
 *   - FFG_Timer::delta_time_us()
 *   - FFG_Timer::frame()
 *   - FFG_Timer::frame_time_s()
 *   - FFG_Timer::frame_time_ms()
 *   - FFG_Timer::frame_time_us()
 * 
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_Timer {
private:
	std::chrono::high_resolution_clock::time_point start_time;
	unsigned long frame_p;
	double delta_time_s_p;
	int delta_time_ms_p;
	int delta_time_us_p;
protected:
	FFG_Timer();
	void start_stop();
	void delay(int ms) const;
public:
	double delta_time_s() const;
	int delta_time_ms() const;
	int delta_time_us() const;
	unsigned long frame() const;
	double frame_time_s() const;
	int frame_time_ms() const;
	int frame_time_us() const;
};

#endif // FFG_TIMER_H_INCLUDED
