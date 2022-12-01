#ifndef BALL_H
#define BALL_H

#include <Area2D.hpp>
#include <Godot.hpp>

class Ball : public godot::Area2D {
private:
	GODOT_CLASS(Ball, godot::Area2D)
	

	const real_t DEFAULT_SPEED = 500;
	
	//Default Direction is not a const because I wanted
	//to make it accessable to Godot's engine so I can change 
	//default direction for different Ball's without making a new class
	//however this code won't be changing it
	godot::Vector2 DEFAULT_DIRECTION;
	bool motion_paused;
	
	real_t speed;
	godot::Vector2 initial_pos;
	godot::Vector2 direction;
public:

	
	void _init();
	void _ready();
	void _process(const double p_delta);
	void reset();
	godot::Vector2 get_direction();
	void set_direction(godot::Vector2 new_direction);
	godot::Vector2 get_initial_position();
	void set_initial_position(godot::Vector2 new_inital_pos);
	bool get_motion_paused();
	void set_motion_paused(bool b);


	static void _register_methods();
};

#endif 
