#include "EmptyState.hpp"

EmptyState::EmptyState(FFG_Engine& engine) : FFG_State(engine) {
}

void EmptyState::init() {
}

void EmptyState::exit() {
}

void EmptyState::handle() {
}

void EmptyState::update() {
}

void EmptyState::render() {
    engine.render_clear();
}
