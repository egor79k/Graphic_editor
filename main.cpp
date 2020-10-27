#include <iostream>
#include "graphics/GLELK.hpp"


const int Win_w = 800;
const int Win_h = 500;


int main ()
{
	//Application app::initialize (Win_w, Win_h, "Native text");
	Application app (Win_w, Win_h, "Native text");

	app.run ();
	//Engine::initialize (Win_w, Win_h, "Native");
	//SFML_engine::window.setSize (sf::Vector2u (Win_w, Win_h));

	return 0;
}