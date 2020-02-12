#include <iostream>
#include "FFG.hpp"
#include "Draw1TestState.hpp"
#include "Draw2TestState.hpp"
#include "Draw3TestState.hpp"
#include "EventTestState.hpp"
#include "PrimitiveTestState.hpp"
#include "TargetTestState.hpp"
#include "test_constants.hpp"
#include "TimerTestState.hpp"
#include "WindowTestState.hpp"

#define WINDOW_TITLE "FFG_ENGINE TEST"
#define SCREEN_WIDTH 1366
#define SCREEN_HEIGHT 768
#define SCREEN_RESOLUTIONS_PATH "test/images/ScreenResolutions.png"
#define SOLDIER_1_HELMET_PATH "test/images/soldier1helmet.png"
#define SOLDIER_2_PACK_PATH "test/images/soldier2pack.png"
#define SOLDIER_3_PANTS_PATH "test/images/soldier3pants.png"
#define SOLDIER_4_SHIRT_PATH "test/images/soldier4shirt.png"
#define SOLDIER_5_SKIN_PATH "test/images/soldier5skin.png"
#define SOLDIER_6_RIFLE_PATH "test/images/soldier6rifle.png"

void print_error(TestError error) {
    switch(error) {
        case LOAD_TEXTURE_FAIL:
            std::cout << "A texture failed to load." << std::endl;
            break;
        case RENDER_CLEAR_FAIL:
            std::cout << "Failed to clear the renderer." << std::endl;
            break;
    }
}

int main(int argc, char **argv) {
    // Switchboard:
    TestSwitchboard switchboard;
    switchboard.screen_resolutions.set(SCREEN_RESOLUTIONS_PATH);
    switchboard.soldier_1_helmet.set(SOLDIER_1_HELMET_PATH);
    switchboard.soldier_2_pack.set(SOLDIER_2_PACK_PATH);
    switchboard.soldier_3_pants.set(SOLDIER_3_PANTS_PATH);
    switchboard.soldier_4_shirt.set(SOLDIER_4_SHIRT_PATH);
    switchboard.soldier_5_skin.set(SOLDIER_5_SKIN_PATH);
    switchboard.soldier_6_rifle.set(SOLDIER_6_RIFLE_PATH);

    // Engine:
    FFG_Engine engine;

    // States:
    Draw1TestState draw_1_state(engine, switchboard);
    Draw2TestState draw_2_state(engine, switchboard);
    Draw3TestState draw_3_state(engine, switchboard);
    EventTestState event_state(engine, switchboard);
    PrimitiveTestState primitive_state(engine, switchboard);
    TargetTestState target_state(engine, switchboard);
    TimerTestState timer_state(engine, switchboard);
    WindowTestState window_state(engine, switchboard);

    // State registration:
    unsigned int draw_1_id = engine.register_state(&draw_1_state);
    unsigned int draw_2_id = engine.register_state(&draw_2_state);
    unsigned int draw_3_id = engine.register_state(&draw_3_state);
    unsigned int event_id = engine.register_state(&event_state);
    unsigned int primitive_id = engine.register_state(&primitive_state);
    unsigned int target_id = engine.register_state(&target_state);
    unsigned int timer_id = engine.register_state(&timer_state);
    unsigned int window_id = engine.register_state(&window_state);

    // Setup switchboard:
    switchboard.draw_1_id = draw_1_id;
    switchboard.draw_2_id = draw_2_id;
    switchboard.draw_3_id = draw_3_id;
    switchboard.event_id = event_id;
    switchboard.primitive_id = primitive_id;
    switchboard.target_id = target_id;
    switchboard.timer_id = timer_id;
    switchboard.window_id = window_id;

    // Setup engine:
    engine.set_window_title(WINDOW_TITLE);
    engine.set_screen_mode(SCREEN_WIDTH, SCREEN_HEIGHT, FFG_WINDOW_WINDOWED);
    engine.set_vsync(true);
    engine.set_next_state(window_id);

    // Run:
    try {
        return engine.run();
    } catch (TestError error) {
        print_error(error);
    }
}
