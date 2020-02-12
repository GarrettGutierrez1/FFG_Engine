#include "TargetTestState.hpp"

void TargetTestState::redraw_soldier() {
    engine.set_render_target(target_texture);
    engine.set_draw_color(0, 0, 0, 255);
    engine.render_clear();

    // Modulation colors.
    switchboard.soldier_1_helmet.set_mod_color(rs[0], gs[0], bs[0]);
    switchboard.soldier_2_pack.set_mod_color(rs[1], gs[1], bs[1]);
    switchboard.soldier_3_pants.set_mod_color(rs[2], gs[2], bs[2]);
    switchboard.soldier_4_shirt.set_mod_color(rs[3], gs[3], bs[3]);
    switchboard.soldier_5_skin.set_mod_color(rs[4], gs[4], bs[4]);
    switchboard.soldier_6_rifle.set_mod_color(rs[5], gs[5], bs[5]);

    // Draws.
    engine.draw(switchboard.soldier_6_rifle);
    engine.draw(switchboard.soldier_5_skin);
    engine.draw(switchboard.soldier_4_shirt);
    engine.draw(switchboard.soldier_3_pants);
    engine.draw(switchboard.soldier_2_pack);
    engine.draw(switchboard.soldier_1_helmet);

    engine.reset_render_target();
}

TargetTestState::TargetTestState(FFG_Engine& engine, TestSwitchboard& switchboard) : FFG_State(engine), switchboard(switchboard) {
    target_texture.set(SOLDIER_WIDTH, SOLDIER_HEIGHT);
    draw_to_x = 0;
    draw_to_y = 0;
}

void TargetTestState::init() {
    std::cout << "--> TargetTestState." << std::endl;
    engine.load_texture(switchboard.soldier_1_helmet);
    engine.load_texture(switchboard.soldier_2_pack);
    engine.load_texture(switchboard.soldier_3_pants);
    engine.load_texture(switchboard.soldier_4_shirt);
    engine.load_texture(switchboard.soldier_5_skin);
    engine.load_texture(switchboard.soldier_6_rifle);
    engine.load_texture(target_texture);
    draw_to_x = (engine.screen_width() - SOLDIER_WIDTH) / 2;
    draw_to_y = (engine.screen_height() - SOLDIER_HEIGHT) / 2;
    redraw_soldier();
}

void TargetTestState::exit() {
    std::cout << "<-- TargetTestState." << std::endl;
    engine.unload_texture(switchboard.soldier_1_helmet);
    engine.unload_texture(switchboard.soldier_2_pack);
    engine.unload_texture(switchboard.soldier_3_pants);
    engine.unload_texture(switchboard.soldier_4_shirt);
    engine.unload_texture(switchboard.soldier_5_skin);
    engine.unload_texture(switchboard.soldier_6_rifle);
    engine.unload_texture(target_texture);
}

void TargetTestState::handle() {
    switch(engine.type) {
        case FFG_EVENT_KEYBOARD_UP:
            switch(engine.key_type) {
                case FFG_EVENT_KEY_CHAR:
                    switch(engine.key) {
                        case '{':
                        case '[':
                            engine.set_next_state(switchboard.primitive_id);
                            return;
                        default:
                            break;
                    } // switch(engine.key)
                    break;
                case FFG_EVENT_KEY_ESCAPE:
                    engine.quit();
                    return;
                default:
                    break;
            } // switch(engine.key_type)
            break;
        default:
            break;
    } // switch(engine.type)
}

void TargetTestState::update() {
}

void TargetTestState::render() {
    engine.reset_render_target();
    engine.render_clear();
    FFG_Rect source;
    source.x = 0;
    source.y = 0;
    source.w = SOLDIER_WIDTH;
    source.h = SOLDIER_HEIGHT;
    engine.draw(target_texture, source, draw_to_x, draw_to_y);
}
