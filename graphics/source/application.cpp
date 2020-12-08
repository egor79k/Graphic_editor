#include "../include/application.hpp"


//=============================================================================
// ::::  Application  ::::
//=============================================================================

void Application::initialize (int width, int height, const char *window_header)
{
	Engine::initialize (width, height, window_header);
}
//-----------------------------------------------------------------------------
	
void Application::step ()
{
	Event_system::dispatch_event ();

	Engine::fill (Color (80, 80, 80));
	
	Event_system::dispatch_redraw ();

	Engine::flush_screen ();
}
//-----------------------------------------------------------------------------
	
void Application::run ()
{
	while (Engine::running ())
	{
		Event_system::dispatch_event ();

		Engine::fill (Color::Black);

		Event_system::dispatch_redraw ();

		Engine::flush_screen ();
	}
}
//=============================================================================