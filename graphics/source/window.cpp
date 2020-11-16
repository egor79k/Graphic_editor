#include "../include/window.hpp"


//====================================================================
// ::::  Abstract_window  ::::
//====================================================================

bool Abstract_window::handle_mouse_press (const Event::Mouse_click &click)
{
	for (auto win: subwindows)
		if (win->handle_mouse_press (click))
			return true;

	return on_mouse_press (click);
}
//--------------------------------------------------------------------

bool Abstract_window::handle_mouse_release (const Event::Mouse_click &click)
{
	for (auto win: subwindows)
		if (win->handle_mouse_release (click))
			return true;

	return on_mouse_release (click);
}
//--------------------------------------------------------------------

bool Abstract_window::handle_mouse_move (const Event::Mouse_move &move)
{
	for (auto win: subwindows)
		if (win->handle_mouse_move (move))
			return true;

	return on_mouse_move (move);
}
//====================================================================



//====================================================================
// ::::  Windows_manager  ::::
//====================================================================

void Windows_manager::handle_event (const Event &event)
{
	switch (event.type)
	{
		case Event::Mouse_pressed:
			for (auto win: windows)
				if (win->handle_mouse_press (event.mouse_click))
					break;
			break;

		case Event::Mouse_released:
			for (auto win: windows)
				if (win->handle_mouse_release (event.mouse_click))
					break;
			break;

		case Event::Mouse_moved:
			for (auto win: windows)
				if (win->handle_mouse_move (event.mouse_move))
					break;
			break;
	}
}
//--------------------------------------------------------------------

void Windows_manager::add_window (Abstract_window *window)
{
	windows.push_back (window);
}
//====================================================================



//====================================================================
// ::::  Window  ::::
//====================================================================

Window::Window () :
	pos (Vector2<int> ())
{}
//--------------------------------------------------------------------

Window::Window (Vector2<int> _pos) :
	pos (_pos)
{}
//--------------------------------------------------------------------

Window::Window (int x, int y) :
	pos (Vector2<int> (x, y))
{}
//--------------------------------------------------------------------

void Window::draw ()
{
	//puts ("Window draw!\n");
}
//--------------------------------------------------------------------

bool Window::handle_event (const Event &event)
{
	//printf("Event %d handled in Window\n", event.type);
	return false;
}
//--------------------------------------------------------------------

const Vector2<int> Window::get_position () const
{
	return pos;
}
//--------------------------------------------------------------------

void Window::set_position (const Vector2<int> _pos)
{
	pos = _pos;
}
//--------------------------------------------------------------------

void Window::set_position (const int x, const int y)
{
	pos = Vector2<int> (x, y);
}
//====================================================================



//====================================================================
// ::::  Rectangle_window  ::::
//====================================================================

Rectangle_window::Rectangle_window (Vector2<int> _pos, Vector2<uint32_t> _size, const Color &_color) :
		Window (_pos),
		size (_size),
		color (_color)
	{}
//--------------------------------------------------------------------

void Rectangle_window::draw ()
{
	Engine::draw::rectangle (Window::get_position (), size, color);
	//puts ("Rectangle_window draw!\n");
}
//--------------------------------------------------------------------

bool Rectangle_window::handle_event (const Event &event)
{
	//printf("Event %d handled in Rectangle_window\n", event.type);
	return false;
}
//--------------------------------------------------------------------

const Vector2<uint32_t> Rectangle_window::get_size () const
{
	return size;
}
//--------------------------------------------------------------------
	
const Color Rectangle_window::get_color () const
{
	return color;
}
//====================================================================



//====================================================================
// ::::  Texture_window  ::::
//====================================================================

Texture_window::Texture_window (const char *texture_file, Vector2<int> _pos) :
	Window (_pos),
	texture (texture_file)
{}
//--------------------------------------------------------------------

/*Texture_window::Texture_window (char *_texture, Vector2<int> _pos, Vector2<int> _size, const Color &_color) :
	Rectangle_window (_pos, _size, _color),
	texture (_texture)
{}*/

void Texture_window::draw ()
{
	texture.draw_sprite (get_position ());
}
//--------------------------------------------------------------------

bool Texture_window::handle_event (const Event &event)
{
	//printf("Event %d handled in Texture_window\n", event.type);
	return false;
}
//--------------------------------------------------------------------

void Texture_window::draw (Vector2<Vector2<uint32_t>> area)
{
	texture.draw_sprite (get_position (), area);
}
//--------------------------------------------------------------------

Vector2<uint32_t> Texture_window::get_size ()
{
	return texture.get_size ();
}
//====================================================================