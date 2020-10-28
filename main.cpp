#include <iostream>
#include "graphics/GLELK.hpp"


const int Win_w = 800;
const int Win_h = 500;
const char Down[] = "textures/arrow_up_released.png";


int main ()
{
	Application app (Win_w, Win_h, "Native text");

	Rectangle_window rwin (Vector2<int> (10, 10), Vector2<int> (100, 100), Color::Red);
	Texture_window twin (Down, Vector2<int> (200, 200));
	//rwin.set_position (Vector2<int> (50, 50));
	app.add_window (&rwin);
	app.add_window (&twin);

	app.run ();

	return 0;
}