#include "paddle.hpp"

using namespace godot;



void Paddle::_ready() {
	_input = Input::get_singleton();
	_random = (Ref<RandomNumberGenerator>)RandomNumberGenerator::_new();
	_random->randomize();
	_screen_size_y = get_viewport_rect().size.y;
	initial_pos = get_position();
	
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
	//math tells me that the bounds needed for this clamp function to keep my player fully on screen is 34.4
	//to be exact I divided the height of the player.svg by 2 since the sprite + collision box is centered
	//on the Player1 and Player2 nodes and then multipled that value by .1 since that was the scale factor to get 34.4
	position.y = (real_t)Math::clamp(position.y + keyboard_input * MOVE_SPEED * delta, 34.4, _screen_size_y - 34.4);
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

Vector2 Paddle::get_initial_position(){
	return initial_pos;
}

void Paddle::set_initial_position(Vector2 new_initial_pos){
	initial_pos = new_initial_pos;
}

void Paddle::_register_methods() {
	register_method("_ready", &Paddle::_ready);
	register_method("_process", &Paddle::_process);
	register_method("_on_area_entered", &Paddle::_on_area_entered);
	register_method("get_initial_position", &Paddle::get_initial_position);
	register_method("set_initial_position", &Paddle::set_initial_position);
}
