#include "goal.h"

using namespace godot;

void Goal::_init(){
	score = 0;
} 



void Goal::_on_goal_area_entered(Ball* ptr_ball) {
	/*since my collision boxes of the goals overlap a tiny bit with my wall's collision boxes this checks that 
	the proper object has been sent, the game will crash if I don't do this because it will try to call
	->reset() on something that doesn't have that function.*/
	if ((ptr_ball->get_name() == "Ball1") || (ptr_ball->get_name() == "Ball2")) {
		//The ball went our of bounds so we must reset it
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
	
	/*when we call set_score in game_state_controller.cpp
	we obviously want our scores to update too*/
	emit_signal("update_score",score, this->get_name());
	
	/*
	technically we're never going to enter a score of 5 or greater but it doesn't hurt to add this, since we'd want 
	a similar response to updating the score through update_score() as we would set_score()
	*/
	if(score >= 5){
		//The class GameStateController handels this signal
		emit_signal("end_game", this->get_name());
	}
}


//Registers the classes so Godot use them
void Goal::_register_methods() {

	register_method("_on_goal_area_entered", &Goal::_on_goal_area_entered);
	register_method("update_score", &Goal::update_score);
	register_method("get_score", &Goal::get_score);
	register_method("set_score", &Goal::set_score);
	register_signal<Goal>((char*)"update_score", "Score", GODOT_VARIANT_TYPE_INT, "Goal Name", GODOT_VARIANT_TYPE_STRING);
	register_signal<Goal>((char*)"end_game", "Goal Name", GODOT_VARIANT_TYPE_STRING);
}
