#ifndef WALL_H
#define WALL_H

#include <Area2D.hpp>
#include <Label.hpp>
#include <Godot.hpp>

#include "ball.hpp"

class Wall : public godot::Area2D {
private:
	GODOT_CLASS(Wall, godot::Area2D)

	//used to handel the scores of the players/paddles
	//will likely also help handle ending the game
	int score;


public:


	void _init();
	void _on_wall_area_entered(Ball* ptr_area);
	void update_score();
	int get_score();
	void set_score(int new_score);

	static void _register_methods();
};

#endif 
