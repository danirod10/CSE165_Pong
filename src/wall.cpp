#include "wall.h"

using namespace godot;



void Wall::_on_wall_area_entered(Ball* ptr_ball) {
	/*since my collision boxes of the goals overlap a tiny bit with my wall's collision boxes this checks that 
	the proper object has been sent, the game will crash if I don't do this because it will try to call
	->reset() on something that doesn't have that function.*/
	if ((ptr_ball->get_name() == "Ball1") || (ptr_ball->get_name() == "Ball2")) {
		/*super simple just reverses the direction of the y component of the vector
		and since Wall is always applied to nodes that are horizontal this will
		mean we reflect our direction across the x-axis exactly like we want to */
		Vector2 new_direction = ptr_ball->get_direction();
		new_direction.y = -(new_direction.y);

		/*originally I normalized it but I'm looking at the math and I shouldn't have to do that here
		so I will just set the ball's current direction as the new direction since nothing else 
		needs to be changed*/
		ptr_ball->set_direction(new_direction);
		
		ptr_ball->sound_effects->_on_play_sfx();
	}
}


//Registers the classes so Godot use them
void Wall::_register_methods() {
	register_method("_on_wall_area_entered", &Wall::_on_wall_area_entered);
}
