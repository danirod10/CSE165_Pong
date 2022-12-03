#ifndef PADDLE_H
#define PADDLE_H

#include <Area2D.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <RandomNumberGenerator.hpp>

#include "ball.h"

class Paddle : public godot::Area2D {
private:
	GODOT_CLASS(Paddle, godot::Area2D)


	const int MOVE_SPEED = 500;
	
	
	godot::String up;
	godot::String down;
	godot::Input* input;
	godot::Ref<godot::RandomNumberGenerator> random;
	godot::Vector2 initial_pos;
	real_t screen_size_y;

public:

	/*C++ constructor and destructor
	Generally not super used in this project
	Godot functions can't be called in a C++ 
	constructor I believe and memory is generally automatically
	managed by Godot*/
	Paddle(){};
	~Paddle(){};


	//Godot constructor
	void _init(){};

	//methods
	void _ready();
	void _process(const double delta);
	void _on_area_entered(Ball *ptr_area);
	void reset();
	godot::Vector2 get_initial_position();
	void set_initial_position(godot::Vector2 new_inital_pos);

	static void _register_methods();
};

#endif 
