#include "paddle.hpp"

void Paddle::_init() {
	MOVE_SPEED = 100;
}


void Paddle::_ready() {
	_input = godot::Input::get_singleton();
	_random = (godot::Ref<godot::RandomNumberGenerator>)godot::RandomNumberGenerator::_new();
	_random->randomize();
	_screen_size_y = get_viewport_rect().size.y;
	
	//This code relies on the use of project godot's setting to create an input map, where the 
	//names of the inputs are registered as [name of node script is attached too]_move_up and 
	//[name of node script is attached too]_move_down
	//Currently the Nodes are named Player1 and Player2
	godot::String n = godot::String(get_name()).to_lower();
	_up = n + "_move_up";
	_down = n + "_move_down";
	
	//if (n == "Player1") {
		//_ball_dir = 1;
	//} else {
		//_ball_dir = -1;
	//}
}

void Paddle::_process(const double delta) {
	// Move up and down based on input.
	real_t keyboard_input = _input->get_action_strength(_down) - _input->get_action_strength(_up);
	godot::Vector2 position = get_position();
	position.y = (real_t)godot::Math::clamp(position.y + keyboard_input * MOVE_SPEED * delta, 16.0, _screen_size_y - 16.0);
	set_position(position);
}

void Paddle::_on_area_entered(Ball *p_ball) {
	// Assign new direction.
	//Doesn't break like the other objects if I don't have this if statment
	//Literally zero clue why though so I'll keep it for consistency
	if ((p_ball->get_name() == "Ball1") || (p_ball->get_name() == "Ball2")) {
		real_t opposite_x = -(p_ball->direction.x);
		p_ball->direction = godot::Vector2(opposite_x, _random->randf() * 2 - 1).normalized();
		//(real_t)_ball_dir
	}
}

void Paddle::_register_methods() {
	godot::register_method("_ready", &Paddle::_ready);
	godot::register_method("_process", &Paddle::_process);
	godot::register_method("_on_area_entered", &Paddle::_on_area_entered);
	godot::register_property<Paddle, int>("MOVE_SPEED",&Paddle::MOVE_SPEED, 100);
}
