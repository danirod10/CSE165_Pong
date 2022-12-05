#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <AudioStreamPlayer.hpp>
#include <Node.hpp>
#include <Godot.hpp>


/*This class is created to decrease the clutter of Game_State_Controller. 
At first this was all implimented there instead
*/
class MusicPlayer : public godot::Node {
private:
	GODOT_CLASS(MusicPlayer, godot::Node)

    godot::AudioStreamPlayer* game_over_music;
    godot::AudioStreamPlayer* game_play_music;
    bool is_game_over;
    bool is_music_on;

public:

	/*C++ constructor and destructor
	Generally not super used in this project
	Godot functions can't be called in a C++ 
	constructor I believe and memory is generally automatically
	managed by Godot*/
	MusicPlayer(){};
	~MusicPlayer(){};


	//Godot constructor
	void _init(){};

	//methods
    void _ready();
	void _change_track(bool game_state);
    void _on_music_toggled(bool turn_music_on);


	static void _register_methods();
};

#endif 