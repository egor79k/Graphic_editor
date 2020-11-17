#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_


//=============================================================================
// [] Abstract_window
//    The most generilized abstract type of window. This class realizes
//    standart virtual event handlers and contains definitions of abstract
//    functions to react on events.
//
// [] Windows_manager
//=============================================================================


class Abstract_window;
class Drawable_window;
class Rectangle_window;


#include <vector>
#include "../EngineSet.hpp"
#include "vector2.hpp"
#include "event.hpp"
#include "event_system.hpp"
#include "color.hpp"



//=============================================================================
class Abstract_window
{
protected:
	std::vector<Abstract_window *> subwindows;

public:
	Abstract_window () = default;


	virtual void handle_redraw ();
	virtual bool handle_mouse_press   (const Event::Mouse_click &click);
	virtual bool handle_mouse_release (const Event::Mouse_click &click);
	virtual bool handle_mouse_move    (const Event::Mouse_move &move);

	virtual void on_redraw () = 0;
	virtual bool on_mouse_press   (const Event::Mouse_click &click) = 0;
	virtual bool on_mouse_release (const Event::Mouse_click &click) = 0;
	virtual bool on_mouse_move    (const Event::Mouse_move &move) = 0;
};
//=============================================================================



//=============================================================================
class Drawable_window : public Abstract_window
{
protected:
	Vector2f pos;

public:
	Drawable_window () = default;
	Drawable_window (Vector2f _pos);
	Drawable_window (float x, float y);

	const Vector2f &get_position () const;
	void set_position (const Vector2f &_pos);
	void set_position (const float x, const float y);
};
//=============================================================================



//=============================================================================
class Rectangle_window : public Drawable_window
{
private:
	Vector2f size;
	Color color;

public:
	Rectangle_window () = default;
	Rectangle_window (const Vector2f &_pos, const Vector2f &_size, const Color &_color = Color::White);

	virtual void on_redraw ();
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);
};
//=============================================================================



//=============================================================================
class Window
{
protected:
	Vector2<int> pos;


public:
	Window ();
	Window (Vector2<int> _pos);
	Window (int x, int y);

	virtual void draw () = 0;

	virtual bool handle_event (const Event &event);

	const Vector2<int> get_position () const;

	void set_position (const Vector2<int> _pos);

	void set_position (const int x, const int y);
};
//=============================================================================



//=============================================================================
class Texture_window : public Window
{
private:
	Engine::Texture texture;

public:
	Texture_window (const char *texture_file, Vector2<int> _pos);

	//Texture_window (char *_texture, Vector2<int> _pos, Vector2<i>, Vector2<int> _size = Vector2<int> (), const Color &_col = Color::White);

	virtual void draw ();

	virtual bool handle_event (const Event &event);

	void draw (Vector2<Vector2<uint32_t>> area);

	Vector2<uint32_t> get_size ();
};
//=============================================================================

#endif // _WINDOW_HPP_