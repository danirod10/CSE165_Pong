#include "score.hpp"

using namespace godot;


void Score::_ready(){
    score_name = get_name();    
}

void Score::_on_update_score(int new_score, String wall_name){
    if((score_name == "Player1Score") && (wall_name == "LeftWall")){
        //Godot doesn't handle converting ints to strings well so 
        //we need to convert to a string and then to a c_string before
        //giving it to String::Godot
        std::string str_plus_int = "Player 1 Score : " + std::to_string(new_score);
        String updated_text = String(str_plus_int.c_str());
        this->set_text(updated_text);
    }
    if((score_name == "Player2Score") && (wall_name == "RightWall")){
        std::string str_plus_int = "Player 2 Score : " + std::to_string(new_score);
        String updated_text = String(str_plus_int.c_str());
        this->set_text(updated_text);
    }
}


void Score::_register_methods(){
    register_method("_ready", &Score::_ready);
    register_method("_on_update_score", &Score::_on_update_score);

}