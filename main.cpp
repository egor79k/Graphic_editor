#include <iostream>
#include "graphics/GLELK.hpp"
#include "graphics/include/scrollbar.hpp"


const int Win_w = 1080;
const int Win_h = 700;


int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Wrong arguments!\n");
		return 0;
	}

	Application::initialize (Win_w, Win_h, "Native text");

	//Rectangle_window rect ({20, 20}, {100, 100}, Color::Red);
	//app.add_window (&rect);
	

	Big_image bimg (argv[1], {100, 100}, {900, 500});
	Application::add_window (&bimg);

	Application::run ();

	return 0;
}

/*
const Scrollbar_init init = {
	{"textures/arrow_up_released.png", "textures/arrow_up_pressed.png"},
	{"textures/arrow_down_released.png", "textures/arrow_down_pressed.png"},
	{"textures/slider_released.png", "textures/slider_pressed.png"}
};*/
	// tbut ("textures/arrow_up_released.png", "textures/arrow_up_pressed.png", Vector2<int> (50, 50));
	//app.add_window (&tbut);

	//Rectangle_window rwin (Vector2<int> (10, 10), Vector2<int> (100, 100), Color::Red);
	//rwin.set_position (Vector2<int> (50, 50));
	//app.add_window (&rwin);

	//Texture_window twin (Down, Vector2<int> (200, 200));
	//app.add_window (&twin);

	//Scrollbar scroll (init, 200, Vector2<int> (400, 0));
	//app.add_window (&scroll);