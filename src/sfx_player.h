#ifndef SFX_PLAYER_H
#define SFX_PLAYER_H

#include <AudioStreamPlayer.hpp>
#include <Node.hpp>
#include <Godot.hpp>


/*This class is created to decrease the clutter of Game_State_Controller. 
At first this was all implimented there instead
*/
class SFXPlayer : public godot::AudioStreamPlayer {
private:
	GODOT_CLASS(SFXPlayer, godot::Node)


    bool is_sfx_on;

public:

	/*C++ constructor and destructor
	Generally not super used in this project
	Godot functions can't be called in a C++ 
	constructor I believe and memory is generally automatically
	managed by Godot*/
	SFXPlayer(){};
	~SFXPlayer(){};


	//Godot constructor
	void _init();

	//methods
    void _on_play_sfx();
    void _on_sfx_toggled(bool turn_sfx_on);


	static void _register_methods();
};

#endif 