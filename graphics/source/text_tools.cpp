#include "../include/text_tools.hpp"

//=============================================================================
// ::::  Text_window  ::::
//=============================================================================

Text_window::Text_window (
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

void Text_window::on_redraw ()
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
	const Vector2s size) :
	Text_window (pos, "", size)
{}
//_____________________________________________________________________________

//=============================================================================