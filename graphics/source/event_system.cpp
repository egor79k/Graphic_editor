#include "../include/event_system.hpp"


//=============================================================================
// ::::  Event_system  ::::
//=============================================================================

std::vector<Drawable *> Event_system::attached_on_redraw;
std::vector<Clickable *> Event_system::attached_on_mouse_press;
std::vector<Clickable *> Event_system::attached_on_mouse_release;
std::vector<Clickable *> Event_system::attached_on_mouse_move;
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

void Event_system::attach_redraw (Drawable *window)
{
	attached_on_redraw.push_back (window);
}

void Event_system::attach_mouse_press (Clickable *window)
{
	attached_on_mouse_press.push_back (window);
}
//-----------------------------------------------------------------------------

void Event_system::attach_mouse_release (Clickable *window)
{
	attached_on_mouse_release.push_back (window);
}
//-----------------------------------------------------------------------------

void Event_system::attach_mouse_move (Clickable *window)
{
	attached_on_mouse_move.push_back (window);
}
//=============================================================================



//=============================================================================
// ::::  Clickable  ::::
//=============================================================================

Clickable::Clickable ()
{
	Event_system::attach_mouse_press (this);
	Event_system::attach_mouse_release (this);
	Event_system::attach_mouse_move (this);
}
//_____________________________________________________________________________

Clickable::~Clickable ()
{
	//Event_system::deattach_mouse_press (this);
	//Event_system::deattach_mouse_release (this);
	//Event_system::deattach_mouse_move (this);
}
//_____________________________________________________________________________

bool Clickable::handle_mouse_press (const Event::Mouse_click &click)
{
	return on_mouse_press (click);
}
//_____________________________________________________________________________

bool Clickable::handle_mouse_release (const Event::Mouse_click &click)
{
	return on_mouse_release (click);
}
//_____________________________________________________________________________

bool Clickable::handle_mouse_move (const Event::Mouse_move &move)
{
	return on_mouse_move (move);
}
//=============================================================================



//=============================================================================
// ::::  Drawable  ::::
//=============================================================================

Drawable::Drawable ()
{
	Event_system::attach_redraw (this);
}
//_____________________________________________________________________________

Drawable::~Drawable ()
{
	//Event_system::deattach_redraw (this);
}
//_____________________________________________________________________________

void Drawable::handle_redraw ()
{
	on_redraw ();
}
//=============================================================================