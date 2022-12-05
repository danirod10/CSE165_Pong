#include "goal.h"

using namespace godot;

void Goal::_init(){
	score = 0;
} 



void Goal::_on_goal_area_entered(Ball* ptr_ball) {
	//Totally breaks if I don't have the if statment checking for the balls's name
	//No clue why and I can't find documentation on it, so I can't remove it
	if ((ptr_ball->get_name() == "Ball1") || (ptr_ball->get_name() == "Ball2")) {
		// Ball went out of game area, reset.
		ptr_ball->reset();

		//calls for score update
		update_score();
	}
}

void Goal::update_score(){

	score++;
	//The Class Score handels this signal
	emit_signal("update_score",score, this->get_name());
	
	//game ends at a score of 5
	if(score == 5){
		//The class GameStateController handels this signal
		emit_signal("end_game", this->get_name());
	}

}

int Goal::get_score(){
	return score;
}

void Goal::set_score(int new_score){
	score = new_score;
	//Testing something here
	emit_signal("update_score",score, this->get_name());
}

void Goal::_register_methods() {

	register_method("_on_goal_area_entered", &Goal::_on_goal_area_entered);
	register_method("update_score", &Goal::update_score);
	register_method("get_score", &Goal::get_score);
	register_method("set_score", &Goal::set_score);
	register_signal<Goal>((char*)"update_score", "Score", GODOT_VARIANT_TYPE_INT, "Goal Name", GODOT_VARIANT_TYPE_STRING);
	register_signal<Goal>((char*)"end_game", "Goal Name", GODOT_VARIANT_TYPE_STRING);
}
