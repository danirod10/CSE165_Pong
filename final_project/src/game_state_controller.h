#ifndef GAME_STATE_CONTROLLER_H
#define GAME_STATE_CONTROLLER_H

#include <SceneTree.hpp>
#include <CanvasLayer.hpp>
#include <AudioStreamPlayer.hpp>
#include <Button.hpp>
#include <CheckButton.hpp>
#include <InputEvent.hpp>
#include <Godot.hpp>


#include "goal.h"
#include "wall.h"
#include "score.h"
#include "paddle.h"
#include "ball.h"
#include "music_player.h"


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
	MusicPlayer* game_play_music;

	//standard godot nodes
	godot::SceneTree* root;
    godot::CanvasLayer* game_over_screen;
	godot::CanvasLayer* settings_screen;
	
	godot::Label* game_over_text;
	godot::Button* restart_button;
	godot::CheckButton* toggle_music_button;


	//need this a singlton for _input()
	godot::Input* input;

	//base type vars
	bool settings_menu_visible;
	/*used to make sure the root->set_pause(false) isn't called in _input()
	when the game is over*/
	bool is_game_over;

public:

	/*C++ constructor and destructor
	Generally not super used in this project
	Godot functions can't be called in a C++ 
	constructor I believe and memory is generally automatically
	managed by Godot*/
	GameStateController(){};

	/*
	Note I don't need to call delete on any of these pointers because I'm not really creating
	any new nodes here, I'm getting pre-existing nodes so Godot should be handling everything
	based on what I know, I believe godot::Ref<T> could also be used to automatically manage memory too

	Okay after some testing here I can safely say that deleting those pointers to my nodes causes some nice errors that
	the Godot debugger doesn't like one bit. You're just gonna have to trust me and maybe read the documentation
	too when I say I don't need to clean up any pointers here
	*/
	~GameStateController(){};

	//Godot constructor
	void _init(){};

	//methods
    void _ready();
	void _input(godot::Ref<godot::InputEvent> event);
	void _on_end_game(godot::String goal_name);
	void _on_restart_game();

	static void _register_methods();
};

#endif 