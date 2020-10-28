#include "../include/application.hpp"


Application::Application (int width, int height, const char *window_header) :
	windows (std::vector<Window *> ())
{
	Engine::initialize (width, height, window_header);
}

	
void Application::run ()
{
	while (Engine::working ())
	{
		Engine::fill (Color::White);

		for (int i = 0; i < windows.size (); ++i)
			windows[i]->draw ();

		Event event;

		while (Engine::poll_event (event))
		{
			if (event.type == Event::Closed)
				Engine::exit ();

			for (int i = 0; i < windows.size (); ++i)
				if (windows[i]->handle_event (event))
					break;
		}

		Engine::flush_screen ();
	}
}


void Application::add_window (Window *window)
{
	windows.push_back (window);
}