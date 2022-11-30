#ifndef Wall_H
#define Wall_H

#include <Area2D.hpp>
#include <Godot.hpp>

#include "ball.hpp"

class Wall : public godot::Area2D {
private:
	GODOT_CLASS(Wall, godot::Area2D)

public:

	void _init(){};
	void _on_wall_area_entered(Ball *ptr_ball);

	static void _register_methods();
};

#endif 
