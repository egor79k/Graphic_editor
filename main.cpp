#include <iostream>
#include <SFML/Graphics.hpp>
#include "graphics/include/application.hpp"


const int Win_w = 800;
const int Win_h = 500;


int main ()
{
	//Application app::initialize (Win_w, Win_h, "Native text");
	static Application app (Win_w, Win_h, "Native text");

	//app::run ();

	return 0;
}