#include "music_player.h"

using namespace godot;




void MusicPlayer::_ready(){
    game_over_music = get_node<AudioStreamPlayer>("GameoverMusic");
    game_play_music = get_node<AudioStreamPlayer>("GameplayMusic");
    is_game_over = false;
    is_music_on = true;
}

//methods
void MusicPlayer::_change_track(bool game_state){
    //change track is called whenever game ends or restarts, since those are the only two times 
    //just make is_game_over the reverse of what it was before
    is_game_over = game_state;

    //now if music is on it will switch the tracks playing
    //if music is off then _on_music_toggled will handle everything
    // properly and change tracks when music is turned back on
    if(is_music_on){
        game_over_music->_set_playing(is_game_over);
        game_play_music->_set_playing(!is_game_over);
    }
    //makes sure both are off
    else{
        game_over_music->_set_playing(false);
        game_play_music->_set_playing(false);
    }
}


void MusicPlayer::_on_music_toggled(bool turn_music_on){
    if(turn_music_on && !is_game_over){
        game_play_music->_set_playing(true);
        is_music_on = true;
    }
    else if(turn_music_on && is_game_over){
        game_over_music->_set_playing(true);
        is_music_on = true;
    }
    //turns music off
    else{
        game_play_music->_set_playing(false);
        game_over_music->_set_playing(false);
        is_music_on = false;
    }
}

void MusicPlayer::_register_methods(){
    register_method("_ready", &MusicPlayer::_ready);
    register_method("_change_track", &MusicPlayer::_change_track);
    register_method("_on_music_toggled", &MusicPlayer::_on_music_toggled);

}