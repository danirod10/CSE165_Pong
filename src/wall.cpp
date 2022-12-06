#include "wall.h"

using namespace godot;



void Wall::_on_wall_area_entered(Ball* ptr_ball) {
	/*since my collision boxes of the goals overlap a tiny bit with my wall's collision boxes this checks that 
	the proper object has been sent, the game will crash if I don't do this because it will try to call
	->reset() on something that doesn't have that function.*/
	if ((ptr_ball->get_name() == "Ball1") || (ptr_ball->get_name() == "Ball2")) {
		//super simple just reverses the direction of the y component of the vector
		//might use something more complex but hey it works
		//will change if I find out this is some big no-no in game design
		Vector2 new_direction = ptr_ball->get_direction();
		new_direction.y = -(new_direction.y);
		//normalizes it just in case
		new_direction.normalize();
		ptr_ball->set_direction(new_direction);
		
		ptr_ball->sound_effects->_on_play_sfx();
	}
}

void Wall::_register_methods() {
	register_method("_on_wall_area_entered", &Wall::_on_wall_area_entered);
}
