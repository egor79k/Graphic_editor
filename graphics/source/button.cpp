#include "../include/button.hpp"


//=============================================================================
// ::::  Abstract_button  ::::
//=============================================================================

Abstract_button::Abstract_button (const Vector2f &pos) :
	Window (pos)
{
	Event_system::attach_mouse_press (this);
	Event_system::attach_mouse_release (this);
	Event_system::attach_mouse_move (this);
}
//=============================================================================



//=============================================================================
// ::::  Rectangle_button  ::::
//=============================================================================

Rectangle_button::Rectangle_button (const Color_scheme &clr_shm, const Vector2f &pos, const Vector2f &sz) :
	Abstract_button (pos),
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

bool Rectangle_button::contains (int x, int y)
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

void Rectangle_button::set_size (const Vector2f &sz)
{
	size = sz;
}
//_____________________________________________________________________________

const Vector2f Rectangle_button::get_size ()
{
	return size;
}
//=============================================================================



//=============================================================================
// ::::  Texture_button  ::::
//=============================================================================

Texture_button::Texture_button (const Image_scheme &img_shm, const Vector2f &pos) :
	Abstract_button (pos),
	texture ({Engine::Texture (img_shm.released), Engine::Texture (img_shm.hovered), Engine::Texture (img_shm.pressed)})
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
			return true;
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

bool Texture_button::contains (int x, int y)
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

void Texture_button::set_size (const Vector2f &sz)
{
	size = sz;
}
//_____________________________________________________________________________

const Vector2f Texture_button::get_size ()
{
	return size;
}
//=============================================================================