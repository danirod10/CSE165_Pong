#include "wall.h"

using namespace godot;



void Wall::_on_wall_area_entered(Ball* ptr_ball) {
	//Totally breaks if I don't have the if statment checking for the balls's name
	//No clude why and I can't find documentation on it, so I can't remove it
	if ((ptr_ball->get_name() == "Ball1") || (ptr_ball->get_name() == "Ball2")) {
		//super simple just reverses the direction of the y component of the vector
		//might use something more complex but hey it works
		//will change if I find out this is some big no-no in game design
		Vector2 new_direction = ptr_ball->get_direction();
		new_direction.y = -(new_direction.y);
		ptr_ball->set_direction(new_direction);
		
	}
}

void Wall::_register_methods() {
	register_method("_on_wall_area_entered", &Wall::_on_wall_area_entered);
}
