#ifndef PONG_BALL_H
#define PONG_BALL_H

#include "bn_core.h"
#include "bn_math.h"
#include "bn_color.h"
#include "bn_colors.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_palette_ptr.h"
#include "bn_sprite_palette_item.h"

#include "bn_sprite_items_ball.h"

namespace pong
{
    //class for a pong ball, which can have different speeds, directions and different color
    class Ball
    {
        private:
            bn::sprite_ptr* _ball_sprite;
            int _x;
            int _y;
            int _speed;
            int _direction;
            bn::color _color;

        public:
            Ball(int x, int  y, int speed, int direction, bn::color color);
            void update();

            float x();
            float y();

            int direction();
            void set_direction(int direction);

            int speed();
            void set_speed(int speed);

            void draw();
    };
}

#endif
