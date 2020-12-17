#include "../include/event_system.hpp"


//=============================================================================
// ::::  Event_system  ::::
//=============================================================================

std::vector<Abstract_window *> Event_system::attached_on_redraw;
std::vector<Abstract_window *> Event_system::attached;
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
		if (event.type == Event::Closed)
			Engine::exit ();
		
		for (auto window: attached)
			if (window->handle_event (event))
				break;
	}
}
//_____________________________________________________________________________

void Event_system::attach (Abstract_window *window)
{
	for (auto win: attached)
		if (win == window)
			return;

	attached.push_back (window);
}
//_____________________________________________________________________________

void Event_system::attach_redraw (Abstract_window *window)
{
	for (auto win: attached_on_redraw)
		if (win == window)
			return;

	attached_on_redraw.push_back (window);
}
//_____________________________________________________________________________

void Event_system::detach (Abstract_window *window)
{
	for (size_t i = 0; i < attached.size (); ++i)
		if (attached[i] == window)
		{
			attached[i] = attached.back ();
			attached.pop_back ();
			return;
		}
}
//_____________________________________________________________________________

void Event_system::detach_redraw (Abstract_window *window)
{
	for (size_t i = 0; i < attached_on_redraw.size (); ++i)
		if (attached_on_redraw[i] == window)
		{
			attached_on_redraw[i] = attached_on_redraw.back ();
			attached_on_redraw.pop_back ();
			return;
		}
}
//=============================================================================



//=============================================================================
// ::::  Clickable  ::::
//=============================================================================

bool Clickable::handle_clickable (const Event &event)
{
	switch (event.type)
	{
		case Event::Mouse_pressed:
			return on_mouse_press (event.mouse_click);

		case Event::Mouse_released:
			return on_mouse_release (event.mouse_click);
	}

	return false;
}
//=============================================================================



//=============================================================================
// ::::  Hoverable  ::::
//=============================================================================

bool Hoverable::handle_hoverable (const Event &event)
{
	switch (event.type)
	{
		case Event::Mouse_pressed:
			return on_mouse_press (event.mouse_click);

		case Event::Mouse_released:
			return on_mouse_release (event.mouse_click);

		case Event::Mouse_moved:
			return on_mouse_move (event.mouse_move);
	}

	return false;
}
//=============================================================================



//=============================================================================
// ::::  Textable  ::::
//=============================================================================

bool Textable::handle_textable (const Event &event)
{
	if (event.type == Event::Text_entered)
		return on_text_enter (event.text);

	return false;
}
//=============================================================================


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