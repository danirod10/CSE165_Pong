#include "ball.hpp"

void Ball::_init(){
	//Initializes the defaults
	//my set up in Godot breaks if I don't do this
	DEFAULT_SPEED = 100;
	_speed = DEFAULT_SPEED;
	
	DEFAULT_DIRECTION = godot::Vector2(-1, 0);
	direction = DEFAULT_DIRECTION;
}

void Ball::_ready() {
	_initial_pos = get_position();
	
	//Allows for Defaults to be updated if changed by Godot's Editor
	//Means I don't have do derive a bunch of different class
	//to make different speeds or default values if I 
	//want to make multiple unique ping-pong balls
	_speed = DEFAULT_SPEED;
	direction = DEFAULT_DIRECTION;
}

void Ball::_process(const double p_delta) {
	_speed += (real_t)p_delta * 2;
	godot::Vector2 position = get_position();
	position += _speed * (real_t)p_delta * direction;
	set_position(position);
}

void Ball::reset() {
	direction = DEFAULT_DIRECTION;
	set_position(_initial_pos);
	_speed = DEFAULT_SPEED;
}

void Ball::_register_methods() {
	godot::register_method("_ready", &Ball::_ready);
	godot::register_method("_process", &Ball::_process);
	godot::register_method("reset", &Ball::reset);
	godot::register_property<Ball, real_t>("DEFAULT_SPEED", &Ball::DEFAULT_SPEED, 100);
	godot::register_property<Ball, godot::Vector2>("DEFAULT_DIRECTION", &Ball::DEFAULT_DIRECTION, godot::Vector2(-1, 0));
}
