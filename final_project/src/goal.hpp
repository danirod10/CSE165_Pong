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


	void _init();
	void _on_goal_area_entered(Ball* ptr_area);
	void update_score();
	int get_score();
	void set_score(int new_score);

	static void _register_methods();
};

#endif 
