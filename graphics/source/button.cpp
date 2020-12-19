#include "../include/button.hpp"


//=============================================================================
// ::::  Abstract_button  ::::
//=============================================================================

Abstract_button::Abstract_button (const Vector2p pos, Button_reactive *_window) :
	Window (pos),
	window (_window)
{}
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

Texture_button::Texture_button (const Texture_scheme &_texture, const Vector2p pos, Button_reactive *window, const char *_annotation) :
	Abstract_button (pos, window),
	texture (_texture),
	annotation (_annotation)
{
	curr_texture = &texture.released;
	size = curr_texture->get_size ();
}
//_____________________________________________________________________________

void Texture_button::on_redraw ()
{
	curr_texture->draw_sprite (pos, size);
	if (hovered () && annotation != nullptr)
		Engine::draw::text (last_hover_pos + Vector2p (10, 15), annotation, 17);
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
			last_hover_pos = Vector2p (move.x, move.y);
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


//=============================================================================
// ::::  Slider  ::::
//=============================================================================

Slider::Slider (const Vector2p pos, const Vector2s size, const Color &color, int16_t Vector2p::*_axis, const Color_scheme &clr_shm, const Vector2s s_size, Slider_reactive *win) :
	Rectangle_window (pos, size, color),
	cursor (),
	axis (_axis),
	window (win)
{
	Vector2p s_pos = pos;
	if (axis == &Vector2p::x)
		s_pos.y -= (s_size.y - size.y) / 2;
	else
		s_pos.x -= (s_size.x - size.x) / 2;

	slider = new Rectangle_button (clr_shm, s_pos, s_size);
	subwindows.push_back (slider);
}
//_____________________________________________________________________________

float Slider::get_percent ()
{
	Vector2p sz (size.x, size.y);
	Vector2p s_sz (slider->get_size ().x, slider->get_size ().y);
	return static_cast<float> (slider->get_position ().*axis - pos.*axis) / static_cast<float> (sz.*axis - s_sz.*axis);
}
//_____________________________________________________________________________

void Slider::set_percent (float percent)
{
	Vector2p sz (size.x, size.y);
	Vector2p s_sz (slider->get_size ().x, slider->get_size ().y);
	Vector2p s_pos = slider->get_position ();
	s_pos.*axis = static_cast<float> (sz.*axis - s_sz.*axis) * percent + static_cast<float> (pos.*axis);
	slider->set_position (s_pos);
}
//_____________________________________________________________________________

bool Slider::handle_event (const Event &event)
{
	for (auto win: subwindows)
		if (win->handle_event (event))
			break;

	return handle_hoverable (event);
}
//_____________________________________________________________________________

bool Slider::on_mouse_press (const Event::Mouse_click &click)
{
	if (slider->pressed ())
	{
		Vector2p click_pos (click.x, click.y);
		cursor = click_pos.*axis - slider->get_position ().*axis;
		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Slider::on_mouse_release (const Event::Mouse_click &click)
{
	if (slider->pressed ())
	{
		Vector2p click_pos (click.x, click.y);
		Vector2p new_pos = slider->get_position ();
		Vector2p sz (size.x, size.y);
		Vector2p s_sz (slider->get_size ().x, slider->get_size ().y);
		new_pos.*axis = click_pos.*axis - cursor;

		if (new_pos.*axis < pos.*axis)
			new_pos.*axis = pos.*axis;
		else if (new_pos.*axis > pos.*axis + sz.*axis - s_sz.*axis)
			new_pos.*axis = pos.*axis + sz.*axis - s_sz.*axis;

		slider->set_position (new_pos);
		window->on_slider_move (this);
		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Slider::on_mouse_move (const Event::Mouse_move &move)
{
	if (slider->pressed ())
	{
		Vector2p move_pos (move.x, move.y);
		Vector2p new_pos = slider->get_position ();
		Vector2p sz (size.x, size.y);
		Vector2p s_sz (slider->get_size ().x, slider->get_size ().y);
		new_pos.*axis = move_pos.*axis - cursor;

		if (new_pos.*axis < pos.*axis)
			new_pos.*axis = pos.*axis;
		else if (new_pos.*axis > pos.*axis + sz.*axis - s_sz.*axis)
			new_pos.*axis = pos.*axis + sz.*axis - s_sz.*axis;

		slider->set_position (new_pos);
		window->on_slider_move (this);
		return true;
	}

	return false;
}
//=============================================================================