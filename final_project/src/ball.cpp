#include "ball.hpp"

using namespace godot;

void Ball::_init(){
	//Initializes the defaults
	//my set up in Godot breaks if I don't do this
	DEFAULT_SPEED = 100;
	_speed = DEFAULT_SPEED;
	
	DEFAULT_DIRECTION = Vector2(-1, 0);
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
	Vector2 position = get_position();
	position += _speed * (real_t)p_delta * direction;
	set_position(position);
}

void Ball::reset() {
	direction = DEFAULT_DIRECTION;
	set_position(_initial_pos);
	_speed = DEFAULT_SPEED;
}


Vector2 Ball::get_direction(){
	return direction;
}

void Ball::set_direction(Vector2 new_direction){
	direction = new_direction;
}

void Ball::_register_methods() {
	register_method("_ready", &Ball::_ready);
	register_method("_process", &Ball::_process);
	register_method("reset", &Ball::reset);
	register_method("get_direction", &Ball::get_direction);
	register_method("set_direction", &Ball::set_direction);
	register_property<Ball, real_t>("DEFAULT_SPEED", &Ball::DEFAULT_SPEED, 100);
	register_property<Ball, Vector2>("DEFAULT_DIRECTION", &Ball::DEFAULT_DIRECTION, Vector2(-1, 0));
}
