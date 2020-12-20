#include <iostream>
#include "graphics/GLELK.hpp"

const int Win_w = 1280;
const int Win_h = 720;


int main (int argc, char *argv[])
{
	Application::initialize (Win_w, Win_h, "GLELK Graphic editor", Color (80, 80, 80));

	Palette palette;
	Tool_manager tmg (&palette);
	Canvas canvas (Vector2p (Engine::get_size ().x / 8 + 30, 20), Vector2s (Engine::get_size ().x * 5 >> 3, Engine::get_size ().y - 40), &tmg);
	Image_options_panel options_panel (&canvas);
	
	Event_system::attach (&tmg);
	Event_system::attach (&options_panel);
	Event_system::attach (&palette);
	Event_system::attach (&canvas);

	Event_system::attach_redraw (&canvas);
	Event_system::attach_redraw (&tmg);
	Event_system::attach_redraw (&options_panel);
	Event_system::attach_redraw (&palette);

	Application::run ();

	return 0;
}