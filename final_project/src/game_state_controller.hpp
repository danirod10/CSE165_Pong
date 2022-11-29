#ifndef GAME_STATE_CONTROLLER_H
#define GAME_STATE_CONTROLLER_H

#include <SceneTree.hpp>
#include <CanvasLayer.hpp>
#include <AudioStreamPlayer.hpp>
#include <Godot.hpp>


#include "wall.hpp"

class GameStateController : public godot::Node {
private:
	GODOT_CLASS(GameStateController, godot::Node);

	Wall* ptr_right_wall;
	Wall* ptr_left_wall;
	godot::SceneTree* root;
    godot::CanvasLayer* game_over_screen;
    godot::AudioStreamPlayer* game_over_music;

public:

	void _init(){};
    void _ready();
	void _on_end_game();

	static void _register_methods();
};

#endif 