#ifndef GAME_STATE_CONTROLLER_H
#define GAME_STATE_CONTROLLER_H

#include <SceneTree.hpp>
#include <CanvasLayer.hpp>
#include <AudioStreamPlayer.hpp>
#include <Button.hpp>
#include <Godot.hpp>


#include "goal.hpp"
#include "wall.hpp"
#include "score.hpp"
#include "paddle.hpp"
#include "ball.hpp"


class GameStateController : public godot::Node {
private:
	GODOT_CLASS(GameStateController, godot::Node);

	//custom nodes
	Goal* ptr_right_goal;
	Goal* ptr_left_goal;
	Wall* ptr_ceiling;
	Wall* ptr_floor;
	Score* ptr_player1_score;
	Score* ptr_player2_score;
	Paddle* ptr_player1;
	Paddle* ptr_player2;
	Ball* ptr_ball1;
	Ball* ptr_ball2;

	//standard godot nodes
	godot::SceneTree* root;
    godot::CanvasLayer* game_over_screen;
    godot::AudioStreamPlayer* game_over_music;
	godot::Label* game_over_text;
	godot::Button* restart_button;

public:

	void _init(){};
    void _ready();
	void _on_end_game(godot::String goal_name);
	void _on_restart_game();

	static void _register_methods();
};

#endif 