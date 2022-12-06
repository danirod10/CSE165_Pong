#include <Godot.hpp>

/*
everything runs is included in game_state_controller
since I use game_state_controller as the script to handle linking
every signal together
*/
#include "game_state_controller.h"


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
	register_class<Player>();
	register_class<Goal>();
	register_class<Score>();
	register_class<MusicPlayer>();
	register_class<GameStateController>();
}
