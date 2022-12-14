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
	rand_x_direction = static_cast<real_t>(random_direction_component->randi_range(0, 1)) * 2 - 1;

	/*randfn() generates a normally distributed float with the defaults of 0.0 mean and 1 standard deviation
	I chose a normal distribution because I want it to be a random start but stay closer to a 0 y-component
	and I made the standard deviation .125 since I didn't want it to have two extream an angle*/
	rand_y_direction = random_direction_component->randfn(0.0, 0.125);

	direction = Vector2(rand_x_direction, rand_y_direction);

	//normalized since it is our direction vector
	direction.normalize();


	//initalizes our SFX
	sound_effects = get_node<SFXPlayer>("SFX");
}

void Ball::_process(const double delta) {
	/*Originally tried to have this line function as a "ball gets 10% faster per second" thing here 
	but since _process() is obviously being called multiple times a second
	I notice this should be more than 10% per second but I'm not sure by how much. 
	Either way it does visibly speed up so I'm not to worried about the exact numbers here*/
	speed += delta * 0.1 * speed;

	//gets current position
	Vector2 position = get_position();

	/*multiplies the delta by the direction and the speed and adds it to the current position
	then sets the position of our Ball to the new position. Note that since speed and delta are 
	doubles and Vector2 uses real_t(which is a typecast of a float) we have to cast our floats to doubles.*/
	position += static_cast<real_t>(speed) * static_cast<real_t>(delta) * direction;
	set_position(position);
}

void Ball::reset() {
	/*generates new random vector components and then assigns them to the direction vector and then normalizes vector
	this is just like what we did in _ready()*/
	rand_x_direction = static_cast<real_t>(random_direction_component->randi_range(0, 1)) * 2 - 1;
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




//Registers the classes so Godot use them
void Ball::_register_methods() {
	register_method("_ready", &Ball::_ready);
	register_method("_process", &Ball::_process);
	register_method("reset", &Ball::reset);
	register_method("get_direction", &Ball::get_direction);
	register_method("set_direction", &Ball::set_direction);
}
