#ifndef Wall_H
#define Wall_H

#include <Area2D.hpp>
#include <Godot.hpp>

#include "ball.h"

class Wall : public godot::Area2D {
private:
	GODOT_CLASS(Wall, godot::Area2D)

public:
	/*C++ constructor and destructor
	Generally not super used in this project
	Godot functions can't be called in a C++ 
	constructor I believe and memory is generally automatically
	managed by Godot*/
	Wall(){};
	~Wall(){};


	//Godot constructor
	void _init(){};

	//methods
	void _on_wall_area_entered(Ball *ptr_ball);

	static void _register_methods();
};

#endif 
