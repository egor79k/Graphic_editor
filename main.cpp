#include <iostream>
#include "graphics/GLELK.hpp"
//#include "graphics/include/scrollbar.hpp"


const int Win_w = 1280;
const int Win_h = 720;


int main (int argc, char *argv[])
{
	Application::initialize (Win_w, Win_h, "Native text");

	Palette palette;
	Tool_manager tmg (&palette);
	Canvas canvas (Vector2p (Engine::get_size ().x / 8 + 30, 20), Vector2s (Engine::get_size ().x * 5 >> 3, Engine::get_size ().y - 40), &tmg);
	Texture_button tbut ({"graphics/textures/test_button_released.png", "graphics/textures/test_button_hovered.png", "graphics/textures/test_button_pressed.png"}, {Win_w - 130, 10});
	
	Event_system::attach (&palette);
	Event_system::attach (&tmg);
	Event_system::attach (&canvas);
	Event_system::attach (&tbut);

	Event_system::attach_redraw (&palette);
	Event_system::attach_redraw (&tmg);
	Event_system::attach_redraw (&canvas);
	Event_system::attach_redraw (&tbut);

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