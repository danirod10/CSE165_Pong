#include "ball.h"

using namespace godot;

void Ball::_init(){
	speed = DEFAULT_SPEED;
}

void Ball::_ready() {
	initial_pos = get_position();	
	random_direction_component = (Ref<RandomNumberGenerator>)RandomNumberGenerator::_new();
	random_direction_component->randomize();
	/*creates a random integer between 1 and -1 by randomly generating an integer between 1 and 0, multiplying it by 2 and then subtracting by 1
	chose an integer because I don't want it to ever be zero as an X component to start since I want it to go towards one of the 
	two goals no matter what. Also since the y-component can be a 0.0 I don't want to accidently crash things
	by trying to normalize a zero vector*/ 
	rand_x_direction = random_direction_component->randi_range(0, 1) * 2 - 1;

	/*randfn() generates a normally distributed float with the defaults of 0.0 mean and 1 standard deviation
	I chose a normal distribution because I want it to be a random start but stay closer to a 0 y-component
	and I made the standard deviation .125 since I didn't want it to have two extream an angle*/
	rand_y_direction = random_direction_component->randfn(0.0, 0.125);

	direction = Vector2(rand_x_direction, rand_y_direction);

	//normalized since it is our direction vector
	direction.normalize();
}

void Ball::_process(const double p_delta) {
	speed += (real_t)p_delta * 2;
	Vector2 position = get_position();
	position += speed * (real_t)p_delta * direction;
	set_position(position);
}

void Ball::reset() {
	//generates new random vector components and then assigns them to the direction vector and then normalizes vector
	rand_x_direction = random_direction_component->randi_range(0, 1) * 2 - 1;
	rand_y_direction = random_direction_component->randfn(0.0, 0.125);
	direction = Vector2(rand_x_direction, rand_y_direction);
	direction.normalize();

	set_position(initial_pos);
	speed = DEFAULT_SPEED;
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
}
