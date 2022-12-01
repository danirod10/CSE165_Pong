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
    /*area_entered is a signal released by Area2D nodes when another Area2D node enters it
    since goals are derived from Area2D nodes we can hook up our goal member function 
    _on_goal_area_entered to the signal released by a goal when it is entered*/
    ptr_right_goal->connect("area_entered",ptr_right_goal,"_on_goal_area_entered");
    ptr_right_goal->connect("update_score",ptr_player1_score,"_on_update_score");

    ptr_left_goal = get_node<Goal>("Pong/LeftGoal");
    ptr_left_goal->connect("end_game", this, "_on_end_game");
    //Same idea here as with the other goal
    ptr_left_goal->connect("area_entered",ptr_left_goal,"_on_goal_area_entered");
    ptr_left_goal->connect("update_score",ptr_player2_score,"_on_update_score");

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
    game_over_text = get_node<Label>("GameOverScreen/WhoWon");

    //prepign for _on_restart_game()
    ptr_ball1 = get_node<Ball>("Pong/Ball1");
    ptr_ball1 = get_node<Ball>("Pong/Ball2");
    restart_button = get_node<Button>("GameOverScreen/RestartButton");
    restart_button->connect("pressed", this,"_on_restart_game");
 }



void GameStateController::_on_end_game(String goal_name){

    //crashes game not sure why
    ptr_ball1->set_motion_paused(true);
    ptr_ball2->set_motion_paused(true);

    //Pauses every single node except for the ones I have whitelisted to run no matter what
    //Will pause all of pong.tscn + the node GameplayMusic and will allow the remaining nodes 
    //in main.tscn to run

    root->set_pause(true);


    //will display the winner of the game
    if(goal_name == "RightGoal"){
        game_over_text->set_text("Player 1 Wins!");
    }
    else if(goal_name == "LeftGoal"){
        game_over_text->set_text("Player 2 Wins!");
    }
    //Thought it might be fun to have differrent game over music
    game_over_music->_set_playing(true);
    //shows the canvas layer that functions as the game over screen
    game_over_screen->set_visible(true);


    

}

void GameStateController::_on_restart_game(){
    /*This may go through multiple itterations depending on how Godot handles things here*/
    
    //resets music
    game_over_music->_set_playing(false);

    root->set_pause(false);

    //resets players and balls to default position
    Vector2 temp = ptr_player1->get_initial_position();
    ptr_player1->set_position(temp);

    temp = ptr_player2->get_initial_position();
    ptr_player2->set_position(temp);

    temp = ptr_ball1->get_initial_position();
    ptr_ball1->reset();

    temp = ptr_ball1->get_initial_position();
    ptr_ball2->reset();

    //resets score
    ptr_player1_score->set_text("Player 1 Score : ");
    ptr_player2_score->set_text("Player 2 Score : ");
    ptr_left_goal->set_score(0);
    ptr_right_goal->set_score(0);

    // //called second to last just so players don't see the reset
    game_over_screen->set_visible(false);

    // //Balls now have movement unpaused
    ptr_ball1->set_motion_paused(false);
    ptr_ball2->set_motion_paused(false);
}



void GameStateController::_register_methods(){
    register_method("_ready", &GameStateController::_ready);
    register_method("_on_end_game", &GameStateController::_on_end_game);
    register_method("_on_restart_game", &GameStateController::_on_restart_game);
}