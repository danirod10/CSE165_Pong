#include "music_player.h"

using namespace godot;




void MusicPlayer::_ready(){
    game_over_music = get_node<AudioStreamPlayer>("GameoverMusic");
    game_play_music = get_node<AudioStreamPlayer>("GameplayMusic");
    is_game_over = false;
    is_music_on = true;
}

//methods
void MusicPlayer::_change_track(){
    if(is_music_on){
        is_game_over = !is_game_over;
        game_over_music->_set_playing(is_game_over);
        game_play_music->_set_playing(is_game_over);
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
    else if(!turn_music_on && !is_game_over){
        game_play_music->_set_playing(false);
        is_music_on = false;
    }
    else if(!turn_music_on && is_game_over){
        game_over_music->_set_playing(false);
        is_music_on = false;
    }
}

void MusicPlayer::_register_methods(){
    register_method("_ready", &MusicPlayer::_ready);
    register_method("_change_track", &MusicPlayer::_change_track);
    register_method("_on_music_toggled", &MusicPlayer::_on_music_toggled);

}