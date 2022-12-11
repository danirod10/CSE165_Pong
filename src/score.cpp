#include "score.h"

using namespace godot;


void Score::_ready(){
    score_name = get_name();   
}

//When emit_signal(update_score) is called in goal, this class will handle it with this member function
void Score::_on_update_score(int new_score, String goal_name){
    /*Since this class will be applied to two different label nodes we need to check the name of the 
    Goal emiting the signal and the Score receiving it to make sure nothing is broken*/
    if((score_name == "Player2Score") && (goal_name == "LeftGoal")){
        //Godot doesn't handle converting ints to strings well so 
        //we need to convert to a string and then to a c_string before
        //giving it to String::Godot
        std::string str_plus_int = "Player 2 Score : " + std::to_string(new_score);
        String updated_text = String(str_plus_int.c_str());
        this->set_text(updated_text);
    }
    else if((score_name == "Player1Score") && (goal_name == "RightGoal")){
        std::string str_plus_int = "Player 1 Score : " + std::to_string(new_score);
        String updated_text = String(str_plus_int.c_str());
        this->set_text(updated_text);
    }
}

//Registers the classes so Godot use them
void Score::_register_methods(){
    register_method("_ready", &Score::_ready);
    register_method("_on_update_score", &Score::_on_update_score);

}