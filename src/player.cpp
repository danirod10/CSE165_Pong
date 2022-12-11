#include "player.h"

using namespace godot;



void Player::_ready() {
	//will be used to handle input later
	input = Input::get_singleton();

	//randomly generates the y-component for the ball's new direction for the method _on_area_entered
	//Called as a Ref<> to RandomNumberGenerator so that Godot handles the memory allocation automatically
	//Because of how GDNative is set up I can't simply call 'new' to make it 
	random_y_component = (Ref<RandomNumberGenerator>)RandomNumberGenerator::_new();
	random_y_component->randomize();

	//Used as a bound for the clamp function in _process() 
	screen_size_y = get_viewport_rect().size.y;

	//Used in reset();
	initial_pos = get_position();
	
	/*This code relies on the use of project.godot's setting to create an input map, where the 
	names of the inputs are registered as [name of node script is attached too]_move_up and 
	[name of node script is attached too]_move_down
	Currently the Nodes are named Player1 and Player2*/
	String name = String(get_name()).to_lower();
	up = name + "_move_up";
	down = name + "_move_down";
	

}

void Player::_process(const double delta) {
	/*Moves up and down based on input, if the down key is pressed then it will move down
	if the up key is pressed it will move up, if both are pressed it won't move at all.

	get_action_strength() works as the name implies and will return 1 if the key is pressed and 0 if it isn't (it also supports controller inputs so 
	that's why it returns a float and not a bool or int)

	Also note that (0,0) on our cordinate system is the top left of the screen so
	here we have down as our positive value and up as our negative value

	technically I think we could've used other godot functions to do the same thing but we had considered adding controller support but never got around to it
	and this was how Godot documentation recommended implimenting keyboard and controller support for movement
	*/
	real_t keyboard_input = input->get_action_strength(down) - input->get_action_strength(up);

	//gets current position
	Vector2 position = get_position();

	/*math tells me that the bounds needed for this clamp function to keep my player fully on screen is 34.4
	to be exact I divided the height of the player.svg by 2 since the sprite + collision box is centered
	on the Player1 and Player2 nodes and then multipled that value by .1 since that was the scale factor applied in the editor to get 34.4*/
	position.y = static_cast<real_t>(Math::clamp(position.y + keyboard_input * MOVE_SPEED * delta, 34.4, screen_size_y - 34.4));
	set_position(position);
}

void Player::_on_player_area_entered(Ball* ptr_ball) {
	/*makes sure that the pointer being passed is actually one of the two balls and that
	this function is responding to the proper on_area_entered signal set from our Player*/
	if ((ptr_ball->get_name() == "Ball1") || (ptr_ball->get_name() == "Ball2")) {
		Vector2 cur_direction = ptr_ball->get_direction();
		/*reverses the x component and randomly generates a y component between 1 and -1 since randf() returns a float between 0.0 and 1.0, it then 
		normalizes the vector so that the ball is set to the proper speed in Ball::_process()*/
		Vector2 new_direction = Vector2(-(cur_direction.x), random_y_component->randf() * 2 - 1).normalized();
		ptr_ball->set_direction(new_direction);

		ptr_ball->sound_effects->_on_play_sfx();
	}
}


void Player::reset() {
	set_position(initial_pos);
}


//Registers the classes so Godot use them
void Player::_register_methods() {
	register_method("_ready", &Player::_ready);
	register_method("_process", &Player::_process);
	register_method("_on_player_area_entered", &Player::_on_player_area_entered);
}
