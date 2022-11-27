#include <Godot.hpp>

#include "ball.hpp"
#include "ceiling_floor.hpp"
#include "paddle.hpp"
#include "wall.hpp"
#include "score.hpp"

using namespace godot;

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	Godot::nativescript_init(handle);

	register_class<Ball>();
	register_class<CeilingFloor>();
	register_class<Paddle>();
	register_class<Wall>();
	register_class<Score>();
}
