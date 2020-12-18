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