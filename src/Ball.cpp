#include "Ball.hpp"

pong::Ball::Ball(int x, int  y, int speed, int direction, bn::color color)
{
    _x = x; _y = y; _speed = speed; _direction = direction; _color = color;
}


void pong::Ball::update()
{
    /*_ball_sprite.set_x(_ball_sprite.x() + _speed * bn::cos(_direction));
    _ball_sprite.set_y(_ball_sprite.y() + _speed * bn::sin(_direction));*/
}

float pong::Ball::x()
{
    return _ball_sprite->x().to_float();
}

float pong::Ball::y()
{
    return _ball_sprite->y().to_float();
}

int pong::Ball::direction()
{
    return _direction;
}

void pong::Ball::set_direction(int direction)
{
    _direction = direction;
}

int pong::Ball::speed()
{
    return _speed;
}

void pong::Ball::set_speed(int speed)
{
    _speed = speed;
}

void pong::Ball::draw()
{
    //create a sprite for the ball
    bn::sprite_ptr ball_sprite = bn::sprite_items::ball.create_sprite(_x, _y);
    _ball_sprite = &ball_sprite;

    // colors contains the colors we want to use for the ball
    bn::color colors[] = {
        bn::colors::black, _color, _color, _color,
        _color, _color, _color, _color,
        _color, _color, _color, _color,
        _color, _color, _color, _color
    };

    bn::sprite_palette_item palette_item(colors, bn::bpp_mode::BPP_4);
    bn::sprite_palette_ptr ball_palette = ball_sprite.palette();
    ball_palette.set_colors(palette_item);
}

