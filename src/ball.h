#ifndef BALL_H
#define BALL_H

#include <Area2D.hpp>
#include <RandomNumberGenerator.hpp>
#include <Godot.hpp>

#include "sfx_player.h"

class Ball : public godot::Area2D {
private:
	GODOT_CLASS(Ball, godot::Area2D)
	

	const double DEFAULT_SPEED = 500;


	double speed;
	godot::Vector2 initial_pos;
	godot::Vector2 direction;
	//wrapped in a godot::Ref because in theory that should handle the memory properly
	godot::Ref<godot::RandomNumberGenerator> random_direction_component;
	real_t rand_x_direction;
	real_t rand_y_direction;


public:
	/*will be used to handle sound effects.
	set to public so I can easily call it's functions
	and so I only have to call get_node once
	*/
	SFXPlayer* sound_effects;


	/*C++ constructor and destructor
	Generally not super used in this project
	Godot functions can't be called in a C++ 
	constructor I believe and memory is generally automatically
	managed by Godot*/
	Ball(){};
	~Ball(){};


	//Godot constructor
	void _init();

	//methods
	void _ready();
	void _process(const double delta);
	void reset();
	godot::Vector2 get_direction();
	void set_direction(godot::Vector2 new_direction);

	//Registers the classes so Godot use them
	static void _register_methods();
};

#endif 
