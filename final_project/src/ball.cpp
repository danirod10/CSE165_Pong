#include "ball.h"

using namespace godot;

void Ball::_init(){
	//Initializes the defaults
	//my set up in Godot breaks if I don't do this
	speed = DEFAULT_SPEED;
	motion_paused = false;
	DEFAULT_DIRECTION = Vector2(-1, 0);
	direction = DEFAULT_DIRECTION;
}

void Ball::_ready() {
	initial_pos = get_position();
	
	//Allows for Defaults to be updated if changed by Godot's Editor
	//Means I don't have do derive a bunch of different class
	//to make different speeds or default values if I 
	//want to make multiple unique ping-pong balls
	direction = DEFAULT_DIRECTION;
}

void Ball::_process(const double p_delta) {
	/*wrapped in !motion_paused if statement so that when reseting things and 
	unpausing the Ball with the Scene Tree the ball still won't move
	until I tell it to*/
	if(!motion_paused){ 
		speed += (real_t)p_delta * 2;
		Vector2 position = get_position();
		position += speed * (real_t)p_delta * direction;
		set_position(position);
	}
}

void Ball::reset() {
	direction = DEFAULT_DIRECTION;
	set_position(initial_pos);
	speed = DEFAULT_SPEED;
}


Vector2 Ball::get_direction(){
	return direction;
}

void Ball::set_direction(Vector2 new_direction){
	direction = new_direction;
}

Vector2 Ball::get_initial_position(){
	return initial_pos;
}

void Ball::set_initial_position(Vector2 new_initial_pos){
	initial_pos = new_initial_pos;
}


bool Ball::get_motion_paused(){
	return motion_paused;
}
void Ball::set_motion_paused(bool b){
	motion_paused = b;
}

void Ball::_register_methods() {
	register_method("_ready", &Ball::_ready);
	register_method("_process", &Ball::_process);
	register_method("reset", &Ball::reset);
	register_method("get_direction", &Ball::get_direction);
	register_method("set_direction", &Ball::set_direction);
	register_method("get_initial_position", &Ball::get_initial_position);
	register_method("set_initial_position", &Ball::set_initial_position);
	register_method("get_motion_paused", &Ball::get_motion_paused);
	register_method("set_motion_paused", &Ball::set_motion_paused);
	register_property<Ball, Vector2>("DEFAULT_DIRECTION", &Ball::DEFAULT_DIRECTION, Vector2(-1, 0));
}
