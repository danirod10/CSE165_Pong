#ifndef GAME_STATE_CONTROLLER_H
#define GAME_STATE_CONTROLLER_H

#include <SceneTree.hpp>
#include <CanvasLayer.hpp>
#include <AudioStreamPlayer.hpp>
#include <Godot.hpp>


#include "goal.hpp"
#include "wall.hpp"
#include "score.hpp"
#include "paddle.hpp"

class GameStateController : public godot::Node {
private:
	GODOT_CLASS(GameStateController, godot::Node);

	Goal* ptr_right_goal;
	Goal* ptr_left_goal;
	Wall* ptr_ceiling;
	Wall* ptr_floor;
	Score* ptr_player1_score;
	Score* ptr_player2_score;
	Paddle* ptr_player1;
	Paddle* ptr_player2;
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