#include "ceiling_floor.hpp"

using namespace godot;



void CeilingFloor::_on_area_entered(Ball* ptr_ball) {
	//Totally breaks if I don't have the if statment checking for the balls's name
	//No clude why and I can't find documentation on it, so I can't remove it
	if ((ptr_ball->get_name() == "Ball1") || (ptr_ball->get_name() == "Ball2")) {
		Vector2 new_direction = (ptr_ball->get_direction() + godot::Vector2(0, (real_t)bounce_direction)).normalized();
		ptr_ball->set_direction(new_direction);
		
	}
}

void CeilingFloor::_register_methods() {
	register_method("_on_area_entered", &CeilingFloor::_on_area_entered);
	register_property<CeilingFloor, int>("bounce_direction", &CeilingFloor::bounce_direction, 1);
}
