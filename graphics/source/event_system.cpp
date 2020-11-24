#include "../include/event_system.hpp"


//=============================================================================
// ::::  Event_system  ::::
//=============================================================================

std::vector<Abstract_window *> Event_system::attached_on_redraw;
std::vector<Abstract_window *> Event_system::attached_on_mouse_press;
std::vector<Abstract_window *> Event_system::attached_on_mouse_release;
std::vector<Abstract_window *> Event_system::attached_on_mouse_move;
//-----------------------------------------------------------------------------

void Event_system::dispatch_redraw ()
{
	for (auto window: attached_on_redraw)
		window->handle_redraw ();
}
//-----------------------------------------------------------------------------

void Event_system::dispatch_event ()
{
	Event event;
	while (Engine::poll_event (event))
	{
		switch (event.type)
		{
			case Event::Closed:
				Engine::exit ();
				break;

			case Event::Mouse_pressed:
				for (auto window: attached_on_mouse_press)
					if (window->handle_mouse_press (event.mouse_click))
						break;
				break;

			case Event::Mouse_released:
				for (auto window: attached_on_mouse_release)
					if (window->handle_mouse_release (event.mouse_click))
						break;
				break;

			case Event::Mouse_moved:
				for (auto window: attached_on_mouse_move)
					if (window->handle_mouse_move (event.mouse_move))
						break;
				break;
		}
	}
}
//-----------------------------------------------------------------------------

void Event_system::attach_redraw (Abstract_window *window)
{
	attached_on_redraw.push_back (window);
}

void Event_system::attach_mouse_press (Abstract_window *window)
{
	attached_on_mouse_press.push_back (window);
}
//-----------------------------------------------------------------------------

void Event_system::attach_mouse_release (Abstract_window *window)
{
	attached_on_mouse_release.push_back (window);
}
//-----------------------------------------------------------------------------

void Event_system::attach_mouse_move (Abstract_window *window)
{
	attached_on_mouse_move.push_back (window);
}
//=============================================================================