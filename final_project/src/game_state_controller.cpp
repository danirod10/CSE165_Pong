#include "game_state_controller.hpp"

using namespace godot;

/*Handles all the connections and set up needed
Since this game is fairly simple it should always be 
safe to do it this way 

This all works because I attatch this script to the node "main" where all
nodes fetched with get_node() are it's children and my understanding is that _ready() is only called
by Godot when all of the children have been created so it should always get the nodes I want

So far this method hasn't failed me

Technically I can do most of this in the Godot Editor but at the end of the day
the assignment was to use C++ to build a game so I'll do it here
*/
void GameStateController::_ready(){
    //prep for singal connections for the goals
    Score* ptr_player1_score = get_node<Score>("Pong/Player1Score");
	Score* ptr_player2_score = get_node<Score>("Pong/Player2Score");

    //handling signal connections for the goals
    ptr_right_goal = get_node<Goal>("Pong/RightGoal");
    ptr_right_goal->connect("end_game", this, "_on_end_game");
    ptr_right_goal->connect("area_entered",ptr_right_goal,"_on_goal_area_entered");
    ptr_right_goal->connect("update_score",ptr_player2_score,"_on_update_score");

    ptr_left_goal = get_node<Goal>("Pong/LeftGoal");
    ptr_left_goal->connect("end_game", this, "_on_end_game");
    ptr_left_goal->connect("area_entered",ptr_left_goal,"_on_goal_area_entered");
    ptr_left_goal->connect("update_score",ptr_player1_score,"_on_update_score");

    //handles the signal connections for the player
    ptr_player1 = get_node<Paddle>("Pong/Player1");
    ptr_player1->connect("area_entered",ptr_player1,"_on_area_entered");

	ptr_player2 = get_node<Paddle>("Pong/Player2");
    ptr_player2->connect("area_entered",ptr_player2,"_on_area_entered");

    //handling signal connections for the walls
    Wall* ptr_ceiling = get_node<Wall>("Pong/Ceiling");
    ptr_ceiling->connect("area_entered",ptr_ceiling,"_on_wall_area_entered");
	Wall* ptr_floor = get_node<Wall>("Pong/Floor");
    ptr_floor->connect("area_entered",ptr_floor,"_on_wall_area_entered");

    //preping for _on_end_game()
    root = get_tree();
    game_over_screen = get_node<CanvasLayer>("GameOverScreen");
    game_over_music = get_node<AudioStreamPlayer>("GameOverMusic");
}



void GameStateController::_on_end_game(){

    root->set_pause(true);
    game_over_screen->set_visible(true);
    game_over_music->_set_playing(true);

}

void GameStateController::_register_methods(){
    register_method("_ready", &GameStateController::_ready);
    register_method("_on_end_game", &GameStateController::_on_end_game);
}