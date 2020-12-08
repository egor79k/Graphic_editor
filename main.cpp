#include <iostream>
#include "graphics/GLELK.hpp"
#include "graphics/include/scrollbar.hpp"


const int Win_w = 1280;
const int Win_h = 720;


int main (int argc, char *argv[])
{
	Application::initialize (Win_w, Win_h, "Native text");

	Tool_manager tmg;
	Texture_button tbut ({"graphics/textures/test_button_released.png", "graphics/textures/test_button_hovered.png", "graphics/textures/test_button_pressed.png"}, {Win_w - 130, 10});
	Texture_button pencil ({{"graphics/textures/graphic_tool_set_released.png", {{0, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_hovered.png", {{0, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_pressed.png", {{0, 0}, {64, 64}}}}, {20, 100});
	Rectangle_button rbut ({{0, 255, 0}, {50, 150, 50}, {0, 100, 0}}, {10, 300}, {50, 50});
	
	Vector2s size (128, 128);
	bool growup = false;

	while (Engine::running ())
	{
		if (size.x == 128)
			growup = false;
		else if (size.x == 70)
			growup = true;

		if (growup)
			size += {1, 1};
		else
			size -= {1, 1};

		tbut.set_size (size);
		Application::step ();
	}

	//Application::run ();

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