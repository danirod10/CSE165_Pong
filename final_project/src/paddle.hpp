#ifndef PADDLE_H
#define PADDLE_H

#include <Area2D.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <RandomNumberGenerator.hpp>

#include "ball.hpp"

class Paddle : public godot::Area2D {
private:
	GODOT_CLASS(Paddle, godot::Area2D)


	const int MOVE_SPEED = 500;
	
	
	godot::String _up;
	godot::String _down;
	godot::Input *_input;
	godot::Ref<godot::RandomNumberGenerator> _random;
	godot::Vector2 initial_pos;
	real_t _screen_size_y;

public:
	void _init(){};
	void _ready();
	void _process(const double delta);
	void _on_area_entered(Ball *ptr_area);
	void reset();
	godot::Vector2 get_initial_position();
	void set_initial_position(godot::Vector2 new_inital_pos);

	static void _register_methods();
};

#endif 
