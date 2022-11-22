#include "wall.hpp"

void Wall::_on_wall_area_entered(Ball *p_ball) {
	//Totally breaks if I don't have the if statment checking for the balls's name
	//No clude why and I can't find documentation on it, so I can't remove it
	if ((p_ball->get_name() == "Ball1") || (p_ball->get_name() == "Ball2")) {
		// Ball went out of game area, reset.
		p_ball->reset();
	}
}

void Wall::_register_methods() {
	godot::register_method("_on_wall_area_entered", &Wall::_on_wall_area_entered);
}
