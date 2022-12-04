#include "game_state_controller.h"

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
    game_over_screen = get_node<CanvasLayer>("GameOverControl/GameOverScreen");
    game_over_text = get_node<Label>("GameOverControl/GameOverScreen/WhoWon");

    //prepign for _on_restart_game()
    ptr_ball1 = get_node<Ball>("Pong/Ball1");
    ptr_ball2 = get_node<Ball>("Pong/Ball2");
    restart_button = get_node<Button>("GameOverControl/GameOverScreen/RestartButton");
    restart_button->connect("pressed", this,"_on_restart_game");

    //preps to open settings menu
    settings_screen = get_node<CanvasLayer>("SettingsControl/SettingsScreen");
    settings_menu_visible = false;
    input = Input::get_singleton();

    //sets up turning music on and off in settings
    MusicPlayer* game_play_music = get_node<MusicPlayer>("Music");
    toggle_music_button = get_node<CheckButton>("SettingsControl/SettingsScreen/SettingsContainer/GridContainer/MusicLevels");
    toggle_music_button->connect("toggled", game_play_music, "_on_music_toggled");
    this->connect("change_track", game_play_music, "_change_track");

    //used to make sure scene tree stays paused when needed
    is_game_over = false;
 }


void GameStateController::_input(Ref<InputEvent> event){
    if(input->is_action_just_pressed("toggle_settings_menu")){
        if(!settings_menu_visible){
            root->set_pause(true);
            settings_screen->set_visible(true);
            settings_menu_visible = true;
        }
        else{
            //don't want things unpaused if game is over
            if(!is_game_over){
                root->set_pause(false);
            }
            settings_screen->set_visible(false);
            settings_menu_visible = false;
        }
    }
}


void GameStateController::_on_end_game(String goal_name){
    is_game_over = true;

    //Need to emit a signal to change the music.
    //it absolutly dies and breaks if I call the _change_track() directly
    //Not sure what is different about what I'm doing that breaks it
    //however this method works
    emit_signal("change_track", is_game_over);

    //Pauses every single node except for the ones I have whitelisted to run no matter what
    //Will pause all of pong.tscn + the node GameplayMusic and will allow the remaining nodes/scenes 
    //in main.tscn to run, this specifically pauses _process() funcions and other similar ones
    //however the _process functions of Ball and Paddle are the ones we really want to stop
    //signals still work and custom functions still work
    root->set_pause(true);

    //will display the winner of the game
    if(goal_name == "RightGoal"){
        game_over_text->set_text("Player 1 Wins!");
    }
    else if(goal_name == "LeftGoal"){
        game_over_text->set_text("Player 2 Wins!");
    }

    //shows the canvas layer that functions as the game over screen
    game_over_screen->set_visible(true);

}

void GameStateController::_on_restart_game(){
    is_game_over = false;

    //resets score, updates the label too since set_score emits the signal update_score
    ptr_left_goal->set_score(0);
    ptr_right_goal->set_score(0);

    //resets all moving nodes to initial positions 
    ptr_ball1->reset();
    ptr_ball2->reset();
    ptr_player1->reset();
    ptr_player2->reset();
    
    //Need to emit a signal to change the music.
    //it absolutly dies and breaks if I call the _change_track() directly
    //Not sure what is different about what I'm doing that breaks it
    //however this method works
    emit_signal("change_track", is_game_over);

    game_over_screen->set_visible(false);

    root->set_pause(false);

}





void GameStateController::_register_methods(){
    register_method("_ready", &GameStateController::_ready);
    register_method("_input", &GameStateController::_input);
    register_method("_on_end_game", &GameStateController::_on_end_game);
    register_method("_on_restart_game", &GameStateController::_on_restart_game);
    register_signal<GameStateController>((char*)"change_track", "Is Game Over", GODOT_VARIANT_TYPE_BOOL);
}