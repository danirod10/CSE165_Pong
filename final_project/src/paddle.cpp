#include "paddle.hpp"

using namespace godot;


void Paddle::_init() {
	MOVE_SPEED = 100;
}


void Paddle::_ready() {
	_input = Input::get_singleton();
	_random = (Ref<RandomNumberGenerator>)RandomNumberGenerator::_new();
	_random->randomize();
	_screen_size_y = get_viewport_rect().size.y;
	
	//This code relies on the use of project.godot's setting to create an input map, where the 
	//names of the inputs are registered as [name of node script is attached too]_move_up and 
	//[name of node script is attached too]_move_down
	//Currently the Nodes are named Player1 and Player2
	String n = String(get_name()).to_lower();
	_up = n + "_move_up";
	_down = n + "_move_down";
	

}

void Paddle::_process(const double delta) {
	// Move up and down based on input.
	real_t keyboard_input = _input->get_action_strength(_down) - _input->get_action_strength(_up);
	Vector2 position = get_position();
	position.y = (real_t)Math::clamp(position.y + keyboard_input * MOVE_SPEED * delta, 16.0, _screen_size_y - 16.0);
	set_position(position);
}

void Paddle::_on_area_entered(Ball* ptr_ball) {
	// Give ball randomized dirrection
	//Doesn't break like the other objects if I don't have this if statment
	//Literally zero clue why though so I'll keep it for consistency
	if ((ptr_ball->get_name() == "Ball1") || (ptr_ball->get_name() == "Ball2")) {
		Vector2 cur_direction = ptr_ball->get_direction();
		Vector2 new_direction = Vector2(-(cur_direction.x), _random->randf() * 2 - 1).normalized();
		ptr_ball->set_direction(new_direction);
	}
}

void Paddle::_register_methods() {
	register_method("_ready", &Paddle::_ready);
	register_method("_process", &Paddle::_process);
	register_method("_on_area_entered", &Paddle::_on_area_entered);
	register_property<Paddle, int>("MOVE_SPEED",&Paddle::MOVE_SPEED, 100);
}
