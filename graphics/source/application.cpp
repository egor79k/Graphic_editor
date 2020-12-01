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
	
void Application::step ()
{
	Event_system::dispatch_event ();

	Engine::fill (Color::Black);
/*
	Pixel_array pixels (600, 600, Color::White);
	Pencil pen;
	pen.start_applying (pixels, {10, 10});
	for (int16_t i = 10; i < 600; i += 10)
		pen.stop_applying (pixels, {590, i});
	for (int16_t i = 10; i < 600; i += 10)
		pen.stop_applying (pixels, {i, 590});
*/
//	pen.start_applying (pixels, {10, 590});
//	pen.stop_applying (pixels, {590, 10});
//	pen.start_applying (pixels, {10, 10});
//	pen.stop_applying (pixels, {590, 590});
//	pen.start_applying (pixels, {590, 590});
//	pen.stop_applying (pixels, {10, 10});
//	pen.start_applying (pixels, {590, 10});
//	pen.stop_applying (pixels, {10, 590});
/*
	pen.start_applying (pixels, {590, 10});
	for (int16_t i = 10; i < 600; i += 10)
		pen.stop_applying (pixels, {10, i});
	for (int16_t i = 10; i < 600; i += 10)
		pen.stop_applying (pixels, {i, 590});
*/		
	//pixels.set_pixel (10, 10, Color::Red);
	//pixels.set_pixel (190, 190, Color::Red);
	//pixels.set_pixel (190, 10, Color::Red);
	//pixels.set_pixel (10, 190, Color::Red);
	//Engine::draw::image ({300, 10}, pixels);
	
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
//-----------------------------------------------------------------------------

void Application::add_window (Window *window)
{
	windows.push_back (window);
}
//=============================================================================