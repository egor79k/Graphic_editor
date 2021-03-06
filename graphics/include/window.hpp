#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_


//=============================================================================
// [] Abstract_window
//    The most generilized abstract type of window. This class realizes
//    standart virtual event handlers and contains definitions of abstract
//    functions to react on events.
//
// [] Window
//    Base class for all GUI elements, witch are related to Engine window and
//    have position into it. Window overrides all abstract event reactions as
//    do-nothing functions.
//
// [] Rectangle_window
//    A basic rectangle with size and color.
//
// [] Texture_window
//    
//=============================================================================


class Abstract_window;
class Window;
class Rectangle_window;
class Dragable_rectangle_window;
class Texture_window;


#include <vector>

#include "../EngineSet.hpp"
#include "abstract_window.hpp"
#include "vector2.hpp"
#include "event.hpp"
#include "event_system.hpp"
#include "color.hpp"
#include "pixel_array.hpp"


//=============================================================================
class Window : public Abstract_window
{
protected:
	Vector2p pos;

public:
	Window () = default;
	Window (Vector2p _pos);
	Window (int16_t x, int16_t y);

	const Vector2p &get_position () const;
	void set_position (const Vector2p _pos);
	void set_position (const int16_t x, const int16_t y);
};
//=============================================================================



//=============================================================================
class Rectangle_window : public Window
{
protected:
	Vector2s size;
	Color color;

public:
	Rectangle_window () = default;
	Rectangle_window (const Vector2p _pos, const Vector2s _size, const Color &_color = Color::White);

	const Vector2s &get_size ();
	const Color &get_color ();
	void set_size (const Vector2s sz);
	void set_color (const Color &col);
	bool contains (const Vector2p point);
	bool contains (int x, int y);

	virtual void on_redraw ();
};
//=============================================================================



//=============================================================================
class Dragable_rectangle_window : public Rectangle_window, public Hoverable
{
protected:
	bool pressed;
	Vector2p cursor;

public:
	Dragable_rectangle_window () = default;
	Dragable_rectangle_window (const Vector2p _pos, const Vector2s _size, const Color &_color = Color::White);

	virtual bool handle_event (const Event &event);
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);
};
//=============================================================================



//=============================================================================
class Texture_window : public Window
{
protected:
	Engine::Texture texture;

public:
	Texture_window (const char *texture_file, const Vector2p _pos);

	//Texture_window (char *_texture, Vector2<int> _pos, Vector2<i>, Vector2<int> _size = Vector2<int> (), const Color &_col = Color::White);

	virtual void on_redraw ();

	void draw (const Vector2<Vector2s> &area);

	const Vector2s get_size ();
};
//=============================================================================



#endif // _WINDOW_HPP_