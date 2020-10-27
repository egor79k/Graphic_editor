#include "../include/window.hpp"
#include <iostream>


Window::Window () {}

void Window::draw ()
{
	//puts ("Window draw!\n");
}

bool Window::handle_event (const Event &event)
{
	printf("Event %d handled\n", event.type);
	return true;
}