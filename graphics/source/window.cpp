#include "../include/window.hpp"


//=============================================================================
// ::::  Abstract_window  ::::
//=============================================================================

 Abstract_window::~Abstract_window ()
{
	for (auto window: subwindows)
		delete window;

	subwindows.clear ();
}
//_____________________________________________________________________________

template<typename T, typename... Args>
void Abstract_window::create_subwindow (Args&... args)
{
	subwindows.emplace_back (new T (args...));
}
//=============================================================================



//=============================================================================
// ::::  Window  ::::
//=============================================================================

Window::Window (Vector2p _pos) :
	pos (_pos)
{
	Event_system::attach_redraw (this);
}
//_____________________________________________________________________________

Window::Window (int16_t x, int16_t y) :
	pos (x, y)
{}
//_____________________________________________________________________________

const Vector2p &Window::get_position () const
{
	return pos;
}
//_____________________________________________________________________________

void Window::set_position (const Vector2p _pos)
{
	pos = _pos;
}
//_____________________________________________________________________________

void Window::set_position (const int16_t x, const int16_t y)
{
	pos = {x, y};
}
//=============================================================================



//=============================================================================
// ::::  Rectangle_window  ::::
//=============================================================================

Rectangle_window::Rectangle_window (const Vector2p _pos, const Vector2s _size, const Color &_color) :
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

const Vector2s &Rectangle_window::get_size ()
{
	return size;
}
//_____________________________________________________________________________

const Color &Rectangle_window::get_color ()
{
	return color;
}
//_____________________________________________________________________________

void Rectangle_window::set_size (const Vector2s sz)
{
	size = sz;
}
//_____________________________________________________________________________

void Rectangle_window::set_color (const Color &col)
{
	color = col;
}
//_____________________________________________________________________________

bool Rectangle_window::contains (const Vector2p point)
{
	return (pos.x < point.x && point.x < (pos.x + size.x) && pos.y < point.y && point.y < (pos.y + size.y));
}
//_____________________________________________________________________________

bool Rectangle_window::contains (int x, int y)
{
	return (pos.x < x && x < (pos.x + size.x) && pos.y < y && y < (pos.y + size.y));
}
//=============================================================================



//=============================================================================
// ::::  Texture_window  ::::
//=============================================================================

Texture_window::Texture_window (const char *texture_file, const Vector2p _pos) :
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

void Texture_window::draw (const Vector2<Vector2s> &area)
{
	texture.draw_sprite (get_position (), area);
}
//_____________________________________________________________________________

const Vector2s Texture_window::get_size ()
{
	return texture.get_size ();
}
//=============================================================================



//=============================================================================
// ::::  Canvas  ::::
//=============================================================================

Canvas::Canvas (const Vector2p pos, const Vector2s size, const Color &color) :
	Rectangle_window (pos, size, color),
	image (size, color)
{

}
//_____________________________________________________________________________
void Canvas::on_redraw ()
{
	Engine::draw::image (pos, image);
}

//=============================================================================