#include <iostream>
#include "graphics/GLELK.hpp"
//#include "graphics/include/scrollbar.hpp"


const int Win_w = 1280;
const int Win_h = 720;


int main (int argc, char *argv[])
{
	Application::initialize (Win_w, Win_h, "GLELK Graphic editor");

	Palette palette;
	Tool_manager tmg (&palette);
	Canvas canvas (Vector2p (Engine::get_size ().x / 8 + 30, 20), Vector2s (Engine::get_size ().x * 5 >> 3, Engine::get_size ().y - 40), &tmg);
	Image_options_panel options_panel (&canvas);
	//Texture_button tbut ({"graphics/textures/test_button_released.png", "graphics/textures/test_button_hovered.png", "graphics/textures/test_button_pressed.png"}, {Win_w - 130, 10});
	
	Event_system::attach (&tmg);
	Event_system::attach (&options_panel);
	Event_system::attach (&palette);
	Event_system::attach (&canvas);
	//Event_system::attach (&tbut);

	Event_system::attach_redraw (&canvas);
	Event_system::attach_redraw (&tmg);
	Event_system::attach_redraw (&options_panel);
	Event_system::attach_redraw (&palette);
	//Event_system::attach_redraw (&tbut);
/*
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
*/
	Application::run ();

	return 0;
}