#include "../include/application.hpp"


//=============================================================================
// ::::  Application  ::::
//=============================================================================

std::vector<Window *> Application::windows;
//-----------------------------------------------------------------------------

void Application::initialize (int width, int height, const char *window_header)
{
	Engine::initialize (width, height, window_header);
}
//-----------------------------------------------------------------------------
	
void Application::run ()
{
	while (Engine::working ())
	{
		Engine::fill (Color::White);

		for (auto win: windows)
			win->draw ();

		Event event;

		while (Engine::poll_event (event))
		{
			if (event.type == Event::Closed)
				Engine::exit ();

			Event_system::dispatch_event (event);

			for (auto win: windows)
				if (win->handle_event (event))
					break;

		}

		Engine::flush_screen ();
	}
}
//-----------------------------------------------------------------------------

void Application::add_window (Window *window)
{
	windows.push_back (window);
}
//-----------------------------------------------------------------------------
/*
void Application::add_window (Abstract_window *window)
{
	win_man.add_window (window);
}*/
//=============================================================================