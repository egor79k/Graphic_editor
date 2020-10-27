#include "../include/application.hpp"


Application::Application (int width, int height, const char *window_header)
{
	Engine::initialize (width, height, window_header);
}

	
void Application::run ()
{
	while (Engine::working ())
	{
		//rwin.clear (sf::Color (255, 255, 255));

		//for (int i = 0; i < windows.size (); ++i)
		//	windows[i]->draw ();

		Event event;

		while (Engine::poll_event (event))
		{
			if (event.type == Event::Closed)
				Engine::exit ();
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

		Engine::flush_screen ();
	}
}

/*
void Application::add_window (Window *window)
{
	windows.push_back (window);
}


sf::RenderWindow &Application::get_rwin ()
{
	return rwin;
}*/