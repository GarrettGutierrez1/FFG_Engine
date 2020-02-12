#include "FFG.hpp"
#include "EmptyState.hpp"

#define WINDOW_TITLE "FFG_ENGINE SIMPLE TEST"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(int argc, char **argv) {
    FFG_Engine engine;
    EmptyState empty_state(engine);
    engine.set_window_title(WINDOW_TITLE);
    engine.set_screen_mode(SCREEN_WIDTH, SCREEN_HEIGHT, FFG_WINDOW_WINDOWED);
    unsigned int empty_state_id = engine.register_state(&empty_state);
    return engine.run();
}
