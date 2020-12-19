#include "../include/text_tools.hpp"


//=============================================================================
// ::::  Rectangle_text_window  ::::
//=============================================================================

Text_window::Text_window (const Vector2p pos, const char *str, const uint16_t _height, const Color &_color) :
	Window (pos),
	text (str),
	height (_height),
	color (_color)
{}
//_____________________________________________________________________________

void Text_window::on_redraw ()
{
	Engine::draw::text (pos, text.data (), (height * 7) >> 3, color);
}
//=============================================================================



//=============================================================================
// ::::  Rectangle_text_window  ::::
//=============================================================================

Rectangle_text_window::Rectangle_text_window (
	const Vector2p pos,
	const char *str,
	const Vector2s size,
	const Color &bkg_color,
	const Color &_text_color) :
	Rectangle_window (pos, size, bkg_color),
	text (str),
	text_color (_text_color)
{}
//_____________________________________________________________________________

void Rectangle_text_window::on_redraw ()
{
	Rectangle_window::on_redraw ();
	Engine::draw::text (pos, text.data (), (size.y * 7) >> 3, text_color);
}
//=============================================================================



//=============================================================================
// ::::  Text_field  ::::
//=============================================================================

Text_field::Text_field (
	const Vector2p pos,
	const Vector2s size,
	Text_field_reactive *win,
	const Color &bkg_color,
	const Color &text_color) :
	Rectangle_text_window (pos, "", size, bkg_color, text_color),
	active (false),
	window (win)
{}
//_____________________________________________________________________________

bool Text_field::is_active ()
{
	return active;
}
//_____________________________________________________________________________

void Text_field::set_active (const bool cond)
{
	active = cond;
}
//_____________________________________________________________________________

bool Text_field::handle_event (const Event &event)
{
	for (auto win: subwindows)
		if (win->handle_event (event))
			return true;

	switch (event.type)
	{
		case Event::Text_entered:
			return on_text_enter (event.text);

		case Event::Mouse_pressed:
			return on_mouse_press (event.mouse_click);

		case Event::Mouse_released:
			return on_mouse_release (event.mouse_click);
	}

	return false;
}
//_____________________________________________________________________________

bool Text_field::on_text_enter    (const Event::Text &symbol)
{
	if (active)
	{
		if (symbol.unicode != Text::Enter)
		{
			if (symbol.unicode != Text::Backspace)
				text.push_back (symbol.unicode);
			else
				if (text.size ())
					text.pop_back ();
		}
		else
			window->on_text_enter (this, text.data ());
		
		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Text_field::on_mouse_press   (const Event::Mouse_click &click)
{
	if (active ^ contains (click.x, click.y))
	{
		active = !active;
		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Text_field::on_mouse_release (const Event::Mouse_click &click)
{
	return false;
}
//=============================================================================



//=============================================================================
// ::::  Text_dialog_window  ::::
//=============================================================================

const Color_scheme Text_dialog_window::default_accept_button_scheme = {Color (0, 180, 0), Color (0, 160, 0), Color (0, 140, 0)};
//_____________________________________________________________________________

Text_dialog_window::Text_dialog_window (const Vector2p pos, const Vector2s size, const Color &color, const char *question, Text_field_reactive *win) :
	Rectangle_window (pos, size, color),
	text_field (new Text_field (
		Vector2p (pos.x + 10, pos.y + (size.y >> 1)),
		Vector2s (size.x - (size.y >> 1) - 20, (size.y >> 1) - 10),
		win))
{
	subwindows.push_back (new Text_window (pos, question, (size.y >> 1) - 10));

	Vector2p field_pos = text_field->get_position ();
	Vector2s field_size = text_field->get_size ();

	subwindows.push_back (new Rectangle_button (
		default_accept_button_scheme,
		Vector2p (field_pos.x + field_size.x, field_pos.y),
		Vector2s (field_size.y, field_size.y),
		this));

	subwindows.push_back (text_field);
}
//_____________________________________________________________________________

bool Text_dialog_window::on_button_press   (Abstract_button *button)
{
	return false;
}
//_____________________________________________________________________________

bool Text_dialog_window::on_button_release (Abstract_button *button)
{
	if (button->hovered ())
	{
		Event text_event = {};
		text_event.text.unicode = Text::Enter;
		text_field->set_active (true);
		text_field->on_text_enter (text_event.text);
		return true;
	}

	return false;
}
//=============================================================================