#include "sfx_player.h"

using namespace godot;




void SFXPlayer::_init(){
    is_sfx_on = true;
}


void SFXPlayer::_on_play_sfx(){
    if(is_sfx_on){
        _set_playing(true);
    }
}

void SFXPlayer::_on_sfx_toggled(bool turn_sfx_on){
    //will turn it on or off depending on how the button is settings was toggled
    is_sfx_on = turn_sfx_on;
}

//Registers the classes so Godot use them
void SFXPlayer::_register_methods(){
    register_method("_on_play_sfx", &SFXPlayer::_on_play_sfx);
    register_method("_on_sfx_toggled", &SFXPlayer::_on_sfx_toggled);

}