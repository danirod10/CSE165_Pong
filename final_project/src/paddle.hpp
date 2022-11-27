#ifndef PADDLE_H
#define PADDLE_H

#include <Area2D.hpp>
#include <Godot.hpp>
#include <Input.hpp>
#include <RandomNumberGenerator.hpp>

#include "ball.hpp"

class Paddle : public godot::Area2D {
private:
	GODOT_CLASS(Paddle, godot::Area2D)

	/*Not a const since we register it in _register_methods() so Godot can change it through the
	editor. This makes it easier to test things through Godot since we don't need to recompile our
	C++ code everytime we want to chnage the movespeed of the paddles*/
	int MOVE_SPEED;
	
	
	godot::String _up;
	godot::String _down;
	godot::Input *_input;
	godot::Ref<godot::RandomNumberGenerator> _random;

	real_t _screen_size_y;

public:
	void _init();
	void _ready();
	void _process(const double p_delta);
	void _on_area_entered(Ball *p_area);

	static void _register_methods();
};

#endif // PADDLE_H
