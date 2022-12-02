#ifndef GOAL_H
#define GOAL_H

#include <Area2D.hpp>
#include <Label.hpp>
#include <Godot.hpp>

#include "ball.hpp"

class Goal : public godot::Area2D {
private:
	GODOT_CLASS(Goal, godot::Area2D)


	int score;


public:

	/*C++ constructor and destructor
	Generally not super used in this project
	Godot functions can't be called in a C++ 
	constructor I believe and memory is generally automatically
	managed by Godot*/
	Goal(){};
	~Goal(){};

	//Godot constructor
	void _init();

	//methods
	void _on_goal_area_entered(Ball* ptr_area);
	void update_score();
	int get_score();
	void set_score(int new_score);

	static void _register_methods();
};

#endif 
