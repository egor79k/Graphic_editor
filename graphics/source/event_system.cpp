#include "../include/event_system.hpp"


//=============================================================================
// ::::  Event_system  ::::
//=============================================================================

std::vector<Drawable *> Event_system::attached_on_redraw;
std::vector<Clickable *> Event_system::attached_on_mouse_press;
std::vector<Clickable *> Event_system::attached_on_mouse_release;
std::vector<Hoverable *> Event_system::attached_on_mouse_move;
//_____________________________________________________________________________

void Event_system::dispatch_redraw ()
{
	for (auto window: attached_on_redraw)
		window->handle_redraw ();
}
//_____________________________________________________________________________

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
//_____________________________________________________________________________

void Event_system::attach_redraw (Drawable *window)
{
	for (auto win: attached_on_redraw)
		if (win == window)
			return;

	attached_on_redraw.push_back (window);
}

void Event_system::attach_mouse_press (Clickable *window)
{
	for (auto win: attached_on_mouse_press)
		if (win == window)
			return;

	attached_on_mouse_press.push_back (window);
}
//_____________________________________________________________________________

void Event_system::attach_mouse_release (Clickable *window)
{
	for (auto win: attached_on_mouse_release)
		if (win == window)
			return;

	attached_on_mouse_release.push_back (window);
}
//_____________________________________________________________________________

void Event_system::attach_mouse_move (Hoverable *window)
{
	for (auto win: attached_on_mouse_move)
		if (win == window)
			return;

	attached_on_mouse_move.push_back (window);
}
//_____________________________________________________________________________

void Event_system::detach_redraw (Drawable *window)
{
	for (size_t i = 0; i < attached_on_redraw.size (); ++i)
		if (attached_on_redraw[i] == window)
		{
			attached_on_redraw[i] = attached_on_redraw.back ();
			attached_on_redraw.pop_back ();
			return;
		}
}
//_____________________________________________________________________________

void Event_system::detach_mouse_press (Clickable *window)
{
	for (size_t i = 0; i < attached_on_mouse_press.size (); ++i)
		if (attached_on_mouse_press[i] == window)
		{
			attached_on_mouse_press[i] = attached_on_mouse_press.back ();
			attached_on_mouse_press.pop_back ();
			return;
		}
}
//_____________________________________________________________________________

void Event_system::detach_mouse_release (Clickable *window)
{
	for (size_t i = 0; i < attached_on_mouse_release.size (); ++i)
		if (attached_on_mouse_release[i] == window)
		{
			attached_on_mouse_release[i] = attached_on_mouse_release.back ();
			attached_on_mouse_release.pop_back ();
			return;
		}
}
//_____________________________________________________________________________

void Event_system::detach_mouse_move (Hoverable *window)
{
	for (size_t i = 0; i < attached_on_mouse_move.size (); ++i)
		if (attached_on_mouse_move[i] == window)
		{
			attached_on_mouse_move[i] = attached_on_mouse_move.back ();
			attached_on_mouse_move.pop_back ();
			return;
		}
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
	Event_system::detach_redraw (this);
}
//_____________________________________________________________________________

void Drawable::handle_redraw ()
{
	on_redraw ();
}
//=============================================================================



//=============================================================================
// ::::  Clickable  ::::
//=============================================================================

Clickable::Clickable ()
{
	Event_system::attach_mouse_press (this);
	Event_system::attach_mouse_release (this);
}
//_____________________________________________________________________________

Clickable::~Clickable ()
{
	Event_system::detach_mouse_press (this);
	Event_system::detach_mouse_release (this);
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
//=============================================================================



//=============================================================================
// ::::  Hoverable  ::::
//=============================================================================

Hoverable::Hoverable ()
{
	Event_system::attach_mouse_move (this);
}
//_____________________________________________________________________________

Hoverable::~Hoverable ()
{
	Event_system::detach_mouse_move (this);
}
//_____________________________________________________________________________

bool Hoverable::handle_mouse_move (const Event::Mouse_move &move)
{
	return on_mouse_move (move);
}
//=============================================================================


/*
//=============================================================================
// ::::  Button_reactive  ::::
//=============================================================================

bool Button_reactive::handle_button_press (Abstract_button *button)
{
	return on_button_press (button);
}
//_____________________________________________________________________________

bool Button_reactive::handle_button_release (Abstract_button *button)
{
	return on_button_release (button);
}
//=============================================================================
*/

/*
//=============================================================================
// ::::  Dragable  ::::
//=============================================================================

Dragable::Dragable ()
{
	Event_system::attach_mouse_move (this);
}
//_____________________________________________________________________________

Dragable::~Dragable ()
{
	//Event_system::detach_mouse_move (this);
}
//_____________________________________________________________________________

bool Dragable::handle_mouse_move (const Event::Mouse_move &move)
{
	return on_mouse_move (move);
}
//=============================================================================*/