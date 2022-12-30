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

#include "fixed_32x64_sprite_font.h"

#include "bn_sprite_items_variable_8x16_font_red.h"
#include "bn_sprite_items_variable_8x16_font_blue.h"
#include "bn_sprite_items_variable_8x16_font_yellow.h"

#include "common_fixed_8x8_sprite_font.h"
#include "common_fixed_8x16_sprite_font.h"
#include "common_variable_8x8_sprite_font.h"
#include "common_variable_8x16_sprite_font.h"

#include "bn_regular_bg_items_pong_start_new_colors.h"

#include "bn_sprite_items_blue_sprite.h"

namespace
{
    constexpr bn::fixed text_y_inc = 14;
    constexpr bn::fixed text_y_limit = (bn::display::height() / 2) - text_y_inc;

    bn::fixed angle;

    void wiggle_text(bn::fixed wiggle_speed, bn::vector<bn::sprite_ptr, 32> character_sprites)
    {
        bn::fixed angle_inc = wiggle_speed;
        angle += angle_inc;

        if(angle >= 360)
        {
            angle -= 360;
        }

        bn::fixed local_angle = angle;

        for(bn::sprite_ptr& character_sprite : character_sprites)
        {
            local_angle += angle_inc;

            if(local_angle >= 360)
            {
                local_angle -= 360;
            }

            character_sprite.set_y(bn::degrees_lut_sin(local_angle) * 3);
        }
    }

    void sprite_per_character_text_scene()
    {
        int points = 0;

        bn::sprite_text_generator fixed_text_generator(common::fixed_8x16_sprite_font);
        fixed_text_generator.set_center_alignment();

        bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> character_sprites;
        text_generator.set_center_alignment();
        //text_generator.set_palette_item(bn::sprite_items::variable_8x16_font_yellow.palette_item());
        text_generator.set_one_sprite_per_character(true);
        text_generator.generate(0, 0, "by Tolik518 (2023)", character_sprites);

        bn::fixed wiggle_speed = 4;

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        while(!bn::keypad::start_pressed())
        {
            text_sprites.clear();
            points += 3;
            fixed_text_generator.set_left_alignment();
            fixed_text_generator.generate(0, -text_y_limit, bn::format<16>(" {}", points), text_sprites);
            fixed_text_generator.set_right_alignment();
            fixed_text_generator.generate(0, -text_y_limit, bn::format<16>("{}", points), text_sprites);

            wiggle_text(wiggle_speed, character_sprites);

            bn::core::update();
        }
         bn::core::update();
    }

    void sprite_move_scene(){
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
        int frame_counter_limit = 60;

        bn::regular_bg_ptr red_bg = bn::regular_bg_items::pong_start_new_colors.create_bg(0, 0);
        red_bg.set_visible(true);

        bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
        text_generator.set_center_alignment();

        bn::vector<bn::sprite_ptr, 32> text_sprites;
        text_generator.generate(0, 48, "PRESS START", text_sprites);

        while(!bn::keypad::start_pressed())
        {
            frame_counter++;
            if (frame_counter%frame_counter_limit > 30 ){
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

    bn::bg_palettes::set_transparent_color(bn::color(7, 4, 9));

    while(true)
    {
        sprite_per_character_text_scene();

        titlescreen_scene();

        sprite_move_scene();
    }
}
