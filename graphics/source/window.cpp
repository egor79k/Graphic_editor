#include "../include/window.hpp"


//=============================================================================
// ::::  Abstract_window  ::::
//=============================================================================

void Abstract_window::handle_redraw ()
{
	for (auto win: subwindows)
		win->handle_redraw ();

	on_redraw ();
}
//_____________________________________________________________________________

bool Abstract_window::handle_mouse_press (const Event::Mouse_click &click)
{
	for (auto win: subwindows)
		if (win->handle_mouse_press (click))
			return true;

	return on_mouse_press (click);
}
//_____________________________________________________________________________

bool Abstract_window::handle_mouse_release (const Event::Mouse_click &click)
{
	for (auto win: subwindows)
		if (win->handle_mouse_release (click))
			return true;

	return on_mouse_release (click);
}
//_____________________________________________________________________________

bool Abstract_window::handle_mouse_move (const Event::Mouse_move &move)
{
	for (auto win: subwindows)
		if (win->handle_mouse_move (move))
			return true;

	return on_mouse_move (move);
}
//=============================================================================



//=============================================================================
// ::::  Window  ::::
//=============================================================================

Window::Window (Vector2f _pos) :
	pos (_pos)
{
	Event_system::attach_redraw (this);
}
//_____________________________________________________________________________

Window::Window (float x, float y) :
	pos (x, y)
{}
//_____________________________________________________________________________

const Vector2f &Window::get_position () const
{
	return pos;
}
//_____________________________________________________________________________

void Window::set_position (const Vector2f &_pos)
{
	pos = _pos;
}
//_____________________________________________________________________________

void Window::set_position (const float x, const float y)
{
	pos = {x, y};
}
//_____________________________________________________________________________

void Window::on_redraw ()
{}
//_____________________________________________________________________________

bool Window::on_mouse_press   (const Event::Mouse_click &click)
{
	return false;
}
//_____________________________________________________________________________

bool Window::on_mouse_release (const Event::Mouse_click &click)
{
	return false;
}
//_____________________________________________________________________________

bool Window::on_mouse_move    (const Event::Mouse_move &move)
{
	return false;
}
//_____________________________________________________________________________
//=============================================================================



//=============================================================================
// ::::  Rectangle_window  ::::
//=============================================================================

Rectangle_window::Rectangle_window (const Vector2f &_pos, const Vector2f &_size, const Color &_color) :
		Window (_pos),
		size (_size),
		color (_color)
	{}
//_____________________________________________________________________________

void Rectangle_window::on_redraw ()
{
	Engine::draw::rectangle (pos, size, color);
}
//_____________________________________________________________________________

const Vector2f &Rectangle_window::get_size ()
{
	return size;
}
//_____________________________________________________________________________

const Color &Rectangle_window::get_color ()
{
	return color;
}
//_____________________________________________________________________________

void Rectangle_window::set_size (const Vector2f &sz)
{
	size = sz;
}
//_____________________________________________________________________________

void Rectangle_window::set_color (const Color &col)
{
	color = col;
}
//_____________________________________________________________________________

//=============================================================================


/*
//=============================================================================
// ::::  Window  ::::
//=============================================================================

Window::Window () :
	pos (Vector2<int> ())
{}
//_____________________________________________________________________________

Window::Window (Vector2<int> _pos) :
	pos (_pos)
{}
//_____________________________________________________________________________

Window::Window (int x, int y) :
	pos (Vector2<int> (x, y))
{}
//_____________________________________________________________________________

bool Window::handle_event (const Event &event)
{
	//printf("Event %d handled in Window\n", event.type);
	return false;
}
//_____________________________________________________________________________

const Vector2<int> Window::get_position () const
{
	return pos;
}
//_____________________________________________________________________________

void Window::set_position (const Vector2<int> _pos)
{
	pos = _pos;
}
//_____________________________________________________________________________

void Window::set_position (const int x, const int y)
{
	pos = Vector2<int> (x, y);
}
//=============================================================================
*/


//=============================================================================
// ::::  Texture_window  ::::
//=============================================================================

Texture_window::Texture_window (const char *texture_file, const Vector2f &_pos) :
	Window (_pos),
	texture (texture_file)
{}
//_____________________________________________________________________________

/*Texture_window::Texture_window (char *_texture, Vector2<int> _pos, Vector2<int> _size, const Color &_color) :
	Rectangle_window (_pos, _size, _color),
	texture (_texture)
{}*/

void Texture_window::on_redraw ()
{
	texture.draw_sprite (pos);
}
//_____________________________________________________________________________

void Texture_window::draw (const Vector2<Vector2f> &area)
{
	texture.draw_sprite (get_position (), area);
}
//_____________________________________________________________________________

const Vector2f Texture_window::get_size ()
{
	return texture.get_size ();
}
//=============================================================================