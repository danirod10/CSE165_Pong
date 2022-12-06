#ifndef PLAYER_H
#define PLAYER_H

#include <Area2D.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <RandomNumberGenerator.hpp>

#include "ball.h"

class Player : public godot::Area2D {
private:
	GODOT_CLASS(Player, godot::Area2D)


	const int MOVE_SPEED = 750;
	
	
	godot::String up;
	godot::String down;
	godot::Input* input;
	godot::Ref<godot::RandomNumberGenerator> random_y_component;
	godot::Vector2 initial_pos;
	real_t screen_size_y;

public:

	/*C++ constructor and destructor
	Generally not super used in this project
	Godot functions can't be called in a C++ 
	constructor I believe and memory is generally automatically
	managed by Godot*/
	Player(){};
	~Player(){};


	//Godot constructor
	void _init(){};

	//methods
	void _ready();
	void _process(const double delta);
	void _on_player_area_entered(Ball *ptr_area);
	void reset();

	static void _register_methods();
};

#endif 
