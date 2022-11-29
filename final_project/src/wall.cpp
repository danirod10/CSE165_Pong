#include "wall.hpp"

using namespace godot;

void Wall::_init(){
	score = 0;
} 



void Wall::_on_wall_area_entered(Ball* ptr_ball) {
	//Totally breaks if I don't have the if statment checking for the balls's name
	//No clue why and I can't find documentation on it, so I can't remove it
	if ((ptr_ball->get_name() == "Ball1") || (ptr_ball->get_name() == "Ball2")) {
		// Ball went out of game area, reset.
		ptr_ball->reset();

		//calls for score update
		update_score();
	}
}

void Wall::update_score(){

	score++;
	//The Class Score handels this signal
	emit_signal("update_score",score, this->get_name());
	
	//game ends at a score of 5
	if(score == 5){
		//The class GameStateController handels this signal
		emit_signal("end_game");
	}

}

int Wall::get_score(){
	return score;
}

void Wall::set_score(int new_score){
	score = new_score;
}

void Wall::_register_methods() {

	register_method("_on_wall_area_entered", &Wall::_on_wall_area_entered);
	register_method("update_score", &Wall::update_score);
	register_method("get_direction", &Wall::get_score);
	register_method("set_score", &Wall::set_score);
	register_signal<Wall>((char*)"update_score", "Score", GODOT_VARIANT_TYPE_INT, "Wall Name", GODOT_VARIANT_TYPE_STRING);
	register_signal<Wall>((char*)"end_game");
}
