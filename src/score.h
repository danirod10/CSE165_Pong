#ifndef SCORE_H
#define SCORE_H

#include <Label.hpp>
#include <Godot.hpp>
#include <string>

#include "goal.h"

class Score : public godot::Label {
private:
	GODOT_CLASS(Score, godot::Label)

    godot::String score_name;

public:

	/*C++ constructor and destructor
	Generally not super used in this project
	Godot functions can't be called in a C++ 
	constructor I believe and memory is generally automatically
	managed by Godot*/
	Score(){};
	~Score(){};


	//Godot constructor
	void _init(){};

	//methods
    void _ready();
	void _on_update_score(int new_score, godot::String wall_name);


	static void _register_methods();
};

#endif 