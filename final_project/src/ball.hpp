#ifndef BALL_H
#define BALL_H

#include <Area2D.hpp>
#include <Godot.hpp>

class Ball : public godot::Area2D {
private:
	GODOT_CLASS(Ball, godot::Area2D)
	
	//The defaults are not left as consts, so I can register them as properties Godot's Editor can edit
	//leaves more options open and doesn't require any extra c++ files when I want to 
	//have two balls moving at different speeds or different directions
	real_t DEFAULT_SPEED;
	godot::Vector2 DEFAULT_DIRECTION;
	
	
	real_t _speed;
	godot::Vector2 _initial_pos;

	//made public so ceiling_floor.cpp and paddle.cpp can access Ball.direction easily
	//may make private and use get() and set() functions
	//Is initialized in _init() along with DEAFULT_DIRECTION
	godot::Vector2 direction;
public:

	
	void _init();
	void _ready();
	void _process(const double p_delta);
	void reset();
	godot::Vector2 get_direction();
	void set_direction(godot::Vector2 new_direction);

	static void _register_methods();
};

#endif // BALL_H
