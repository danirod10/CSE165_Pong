#include "game_state_controller.hpp"

using namespace godot;


void GameStateController::_ready(){
    ptr_right_wall = get_node<Wall>("Pong/RightWall");
    ptr_right_wall->connect("end_game", this, "_on_end_game");
    ptr_left_wall = get_node<Wall>("Pong/LeftWall");
    ptr_left_wall->connect("end_game", this, "_on_end_game");
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