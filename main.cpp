#include <iostream>
#include "graphics/GLELK.hpp"
#include "graphics/include/scrollbar.hpp"



const int Win_w = 800;
const int Win_h = 500;
const char Down[] = "textures/arrow_up_released.png";

const Scrollbar::Init init = {
	{"textures/arrow_up_released.png", "textures/arrow_up_pressed.png"},
	{"textures/arrow_down_released.png", "textures/arrow_down_pressed.png"},
	{"textures/slider_released.png", "textures/slider_pressed.png"}
};

int main ()
{
	Application app (Win_w, Win_h, "Native text");

	//Big_image ();
	printf ("%u x %u", Engine::get_size().x, Engine::get_size().y);

	Scrollbar scroll (init, 200, Vector2<int> (400, 0));

	Rectangle_window rwin (Vector2<int> (10, 10), Vector2<int> (100, 100), Color::Red);
	Texture_window twin (Down, Vector2<int> (200, 200));
	//rwin.set_position (Vector2<int> (50, 50));
	app.add_window (&rwin);
	app.add_window (&twin);
	app.add_window (&scroll);

	app.run ();

	return 0;
}