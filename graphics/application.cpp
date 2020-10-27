#include "include/application.hpp"


Application::Application (int width, int height, const char *window_header) :
	rwin (sf::VideoMode (width, height), window_header)
{}


Application &Application::initialize (int width, int height, const char *window_header)
{
	static Application app (width, height, window_header);
	return app;
}

	
void Application::run ()
{
	while (rwin.isOpen ())
	{
		rwin.clear (sf::Color (255, 255, 255));

		for (int i = 0; i < windows.size (); ++i)
			windows[i]->draw ();

		sf::Event event;

		while (rwin.pollEvent (event))
		{
			if (event.type == sf::Event::Closed)
				rwin.close ();
/*
			if (static_cast<int> (event.key.code) == static_cast<int> (sf::Mouse::Left))
			{
				sf::Vector2i mouse_pos = sf::Mouse::getPosition (rwin);
					
				if (event.type == sf::Event::MouseButtonPressed)
				{
					for (int i = 0; i < windows.size (); ++i)
					{
						if (windows[i]->contains (mouse_pos.x, mouse_pos.y))
						{
							windows[i]->action ();
							break;
						}
					}
				}
			}*/
		}

		rwin.display ();
	}
}


void Application::add_window (Window *window)
{
	windows.push_back (window);
}


sf::RenderWindow &Application::get_rwin ()
{
	return rwin;
}