#include <Godot.hpp>

#include "ball.hpp"
#include "wall.hpp"
#include "paddle.hpp"
#include "goal.hpp"
#include "score.hpp"
#include "game_state_controller.hpp"


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
	register_class<Wall>();
	register_class<Paddle>();
	register_class<Goal>();
	register_class<Score>();
	register_class<GameStateController>();
}
