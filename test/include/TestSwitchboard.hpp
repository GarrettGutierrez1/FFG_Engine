#ifndef TEST_SWITCHBOARD_H_INCLUDED
#define TEST_SWITCHBOARD_H_INCLUDED

#include <string>
#include "FFG.hpp"

class TestSwitchboard {
public:
    // Textures
    FFG_Texture screen_resolutions;
    FFG_Texture soldier_1_helmet;
    FFG_Texture soldier_2_pack;
    FFG_Texture soldier_3_pants;
    FFG_Texture soldier_4_shirt;
    FFG_Texture soldier_5_skin;
    FFG_Texture soldier_6_rifle;
    // State IDs
	unsigned int draw_1_id;
    unsigned int draw_2_id;
    unsigned int draw_3_id;
    unsigned int event_id;
    unsigned int primitive_id;
    unsigned int target_id;
    unsigned int timer_id;
    unsigned int window_id;
};

#endif // TEST_SWITCHBOARD_H_INCLUDED
