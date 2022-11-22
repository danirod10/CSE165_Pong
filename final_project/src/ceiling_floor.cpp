#include "ceiling_floor.hpp"

void CeilingFloor::_on_area_entered(Ball *p_ball) {
	//Totally breaks if I don't have the if statment checking for the balls's name
	//No clude why and I can't find documentation on it, so I can't remove it
	if ((p_ball->get_name() == "Ball1") || (p_ball->get_name() == "Ball2")) {
		p_ball->direction = (p_ball->direction + godot::Vector2(0, (real_t)bounce_direction)).normalized();
	}
}

void CeilingFloor::_register_methods() {
	godot::register_method("_on_area_entered", &CeilingFloor::_on_area_entered);
	godot::register_property("bounce_direction", &CeilingFloor::bounce_direction, 1);
}
