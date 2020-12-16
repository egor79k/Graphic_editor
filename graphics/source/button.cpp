#include "../include/button.hpp"


//=============================================================================
// ::::  Abstract_button  ::::
//=============================================================================

Abstract_button::Abstract_button (const Vector2p pos, Button_reactive *_window) :
	Window (pos),
	window (_window)
{
	//Event_system::attach_mouse_press (this);
	//Event_system::attach_mouse_release (this);
	//Event_system::attach_mouse_move (this);
}
//_____________________________________________________________________________

bool Abstract_button::handle_event (const Event &event)
{
	for (auto win: subwindows)
		if (win->handle_event (event))
			return true;

	return handle_hoverable (event);
}
//=============================================================================



//=============================================================================
// ::::  Rectangle_button  ::::
//=============================================================================

Rectangle_button::Rectangle_button (const Color_scheme &clr_shm, const Vector2p pos, const Vector2s sz, Button_reactive *window) :
	Abstract_button (pos, window),
	size (sz),
	color (clr_shm)
{
	curr_color = &color.released;
}
//_____________________________________________________________________________

void Rectangle_button::on_redraw ()
{
	Engine::draw::rectangle (pos, size, *curr_color);
}
//_____________________________________________________________________________

bool Rectangle_button::on_mouse_press (const Event::Mouse_click &click)
{
	if (contains (click.x, click.y))
	{
		curr_color = &color.pressed;

		if (window != nullptr)
			window->on_button_press (this);

		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Rectangle_button::on_mouse_release (const Event::Mouse_click &click)
{
	if (pressed ())
	{
		if (contains (click.x, click.y))
		{
			curr_color = &color.hovered;
			// do action ()
		}
		else
		{
			curr_color = &color.released;
			// no action ()
		}

		if (window != nullptr)
			window->on_button_release (this);

		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Rectangle_button::on_mouse_move (const Event::Mouse_move &move)
{
	if (!pressed ())
	{
		if (contains (move.x, move.y))
		{
			curr_color = &color.hovered;
			return true;
		}

		if (hovered ())
		{
			curr_color = &color.released;
			return true;
		}
	}

	return false;
}
//_____________________________________________________________________________

bool Rectangle_button::contains (int16_t x, int16_t y)
{
	return (pos.x < x && x < (pos.x + size.x) && pos.y < y && y < (pos.y + size.y));
}
//_____________________________________________________________________________

bool Rectangle_button::pressed ()
{
	return curr_color == &color.pressed;
}
//_____________________________________________________________________________

bool Rectangle_button::hovered ()
{
	return curr_color == &color.hovered;
}
//_____________________________________________________________________________

void Rectangle_button::set_size (const Vector2s sz)
{
	size = sz;
}
//_____________________________________________________________________________

const Vector2s Rectangle_button::get_size ()
{
	return size;
}
//=============================================================================



//=============================================================================
// ::::  Texture_button  ::::
//=============================================================================

Texture_button::Texture_button (const Texture_scheme &_texture, const Vector2p pos, Button_reactive *window) :
	Abstract_button (pos, window),
	texture (_texture)
{
	curr_texture = &texture.released;
	size = curr_texture->get_size ();
}
//_____________________________________________________________________________

void Texture_button::on_redraw ()
{
	curr_texture->draw_sprite (pos, size);
}
//_____________________________________________________________________________

bool Texture_button::on_mouse_press (const Event::Mouse_click &click)
{
	if (contains (click.x, click.y))
	{
		curr_texture = &texture.pressed;

		if (window != nullptr)
			window->on_button_press (this);

		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Texture_button::on_mouse_release (const Event::Mouse_click &click)
{
	if (pressed ())
	{
		if (contains (click.x, click.y))
		{
			curr_texture = &texture.hovered;
			// do action ()
		}
		else
		{
			curr_texture = &texture.released;
			// no action ()
		}

		if (window != nullptr)
			window->on_button_release (this);

		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Texture_button::on_mouse_move (const Event::Mouse_move &move)
{
	if (!pressed ())
	{
		if (contains (move.x, move.y))
		{
			curr_texture = &texture.hovered;
			return false;
			// If return true problem with hovering neighbour buttons
		}

		if (hovered ())
		{
			curr_texture = &texture.released;
			return true;
		}
	}

	return false;
}
//_____________________________________________________________________________

bool Texture_button::contains (int16_t x, int16_t y)
{
	return (pos.x < x && x < (pos.x + size.x) && pos.y < y && y < (pos.y + size.y));
}
//_____________________________________________________________________________

bool Texture_button::pressed ()
{
	return curr_texture == &texture.pressed;
}
//_____________________________________________________________________________

bool Texture_button::hovered ()
{
	return curr_texture == &texture.hovered;
}
//_____________________________________________________________________________

void Texture_button::set_size (const Vector2s sz)
{
	size = sz;
}
//_____________________________________________________________________________

const Vector2s Texture_button::get_size ()
{
	return size;
}
//=============================================================================