#include <iostream>
#include "graphics/GLELK.hpp"


const int Win_w = 800;
const int Win_h = 500;


int main ()
{
	Application app (Win_w, Win_h, "Native text");

	Window win;
	app.add_window (&win);

	app.run ();

	return 0;
}