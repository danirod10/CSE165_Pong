#ifndef SCORE_H
#define SCORE_H

#include <Label.hpp>
#include <Godot.hpp>
#include <string>

#include "wall.hpp"

class Score : public godot::Label {
private:
	GODOT_CLASS(Score, godot::Label)

    godot::String score_name;

public:

	void _init(){};
    void _ready();
	void _on_update_score(int new_score, godot::String wall_name);

	static void _register_methods();
};

#endif 