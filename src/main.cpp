#include "bn_core.h"
#include "bn_math.h"
#include "bn_format.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_actions.h"
#include "bn_regular_bg_builder.h"
#include "bn_regular_bg_attributes.h"
#include "bn_sprite_text_generator.h"
#include "bn_regular_bg_position_hbe_ptr.h"
#include "bn_regular_bg_attributes_hbe_ptr.h"

#include "bn_sprite_items_variable_8x16_font_red.h"
#include "bn_sprite_items_variable_8x16_font_blue.h"
#include "bn_sprite_items_variable_8x16_font_yellow.h"

#include "common_variable_8x16_sprite_font.h"
#include "variable_8x16_sprite_font_custom.h"

#include "bn_regular_bg_items_pong_start_new_colors.h"

#include "bn_sprite_items_blue_sprite.h"

#define BG_COLOR bn::color(7, 4, 9)
#define FRAME_LIMIT 60

namespace
{
    void credits()
    {
        int frame_counter = 0;
        int frame_counter_limit = 60;
        bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));

        auto customfont = variable_8x16_sprite_font_custom;

        bn::sprite_text_generator text_generator(customfont);
        bn::vector<bn::sprite_ptr, 32> character_sprites;

        text_generator.set_center_alignment();
        text_generator.set_one_sprite_per_character(false);
        //text_generator.set_palette_item(bn::sprite_items::variable_8x16_font_yellow.palette_item());
        text_generator.generate(0, -8, "'2023  Tolik518", character_sprites);
        text_generator.generate(0, 8, "Powered by Butano Engine", character_sprites);

        bn::fixed wiggle_speed = 4;

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        while(!bn::keypad::start_pressed())
        {
            bn::core::update();
        }
        bn::core::update();
    }

    void sprite_move_scene() {
        bn::bg_palettes::set_transparent_color(BG_COLOR);
        int x0 = (bn::display::width()/2)-12;
        int x1 = (-(bn::display::width()/2))+12;
        bn::sprite_ptr blue_sprite0 = bn::sprite_items::blue_sprite.create_sprite(x0, 0);
        bn::sprite_ptr blue_sprite1 = bn::sprite_items::blue_sprite.create_sprite(x1, 0);


        while(!bn::keypad::start_pressed())
        {
            if(bn::keypad::up_held())
            {
                blue_sprite0.set_y(blue_sprite0.y() - 2);
                blue_sprite1.set_y(blue_sprite1.y() - 2);

            }
            else if(bn::keypad::down_held())
            {
                blue_sprite0.set_y(blue_sprite0.y() + 2);
                blue_sprite1.set_y(blue_sprite1.y() + 2);
            }

            bn::core::update();
        }
         bn::core::update();
    }

    void titlescreen_scene()
    {
        int frame_counter = 0;

        bn::regular_bg_ptr red_bg = bn::regular_bg_items::pong_start_new_colors.create_bg(0, 0);
        red_bg.set_visible(true);

        bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, 48, "PRESS START", text_sprites);

        while(!bn::keypad::start_pressed())
        {
            frame_counter++;
            if (frame_counter%FRAME_LIMIT > 30 ){
                text_sprites.clear();
            } else {
                text_sprites.clear();
                text_generator.generate(0, 48, "PRESS START", text_sprites);
            }
            bn::core::update();
        }
        bn::core::update();
    }

}


int main()
{
    bn::core::init();

    while(true)
    {
        credits();

        titlescreen_scene();

        sprite_move_scene();
    }
}
