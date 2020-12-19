#include "../include/application.hpp"


//=============================================================================
// ::::  Application  ::::
//=============================================================================

Color Application::bkg_color;
//-----------------------------------------------------------------------------

void Application::initialize (int width, int height, const char *window_header, const Color &color)
{
	Engine::initialize (width, height, window_header);
	bkg_color = color;
}
//-----------------------------------------------------------------------------
	
void Application::step ()
{
	Event_system::dispatch_event ();

	Engine::fill (bkg_color);
	
	Event_system::dispatch_redraw ();

	Engine::flush_screen ();
}
//-----------------------------------------------------------------------------
	
void Application::run ()
{
	while (Engine::running ())
	{
		Event_system::dispatch_event ();

		Engine::fill (bkg_color);

		Event_system::dispatch_redraw ();

		Engine::flush_screen ();
	}
}
//=============================================================================