#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

template <typename T>
struct Button_scheme;
class Button_reactive;
class Abstract_button;
class Rectangle_button;
class Texture_button;
class Slider_reactive;
class Slider;


#include "event_system.hpp"
#include "window.hpp"


//=============================================================================
class Button_reactive
{
public:
	Button_reactive () = default;

	virtual ~Button_reactive () = default;

	virtual bool on_button_press   (Abstract_button *button) = 0;
	virtual bool on_button_release (Abstract_button *button) = 0;
};
//=============================================================================



//=============================================================================
template <typename T>
struct Button_scheme
{
	T released;
	T hovered;
	T pressed;
};

typedef Button_scheme<Color> Color_scheme;
typedef Button_scheme<Engine::Texture> Texture_scheme;
//=============================================================================



//=============================================================================
class Abstract_button : public Window, public Hoverable
{
protected:
	Button_reactive *window;

public:
	Abstract_button (const Vector2p pos, Button_reactive *_window);

	virtual ~Abstract_button () = default;

	virtual bool contains (int16_t x, int16_t y) = 0;

	virtual bool pressed () = 0;
	virtual bool hovered () = 0;

	virtual bool handle_event (const Event &event);
};
//=============================================================================



//=============================================================================
class Rectangle_button : public Abstract_button
{
protected:
	Vector2s size;
	Color *curr_color;
	Color_scheme color;

public:
	Rectangle_button (const Color_scheme &clr_shm, const Vector2p pos, const Vector2s sz, Button_reactive *window = nullptr);

	virtual void on_redraw ();
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);

	bool contains (int16_t x, int16_t y);

	bool pressed ();
	bool hovered ();

	void set_size (const Vector2s sz);
	const Vector2s get_size ();
};
//=============================================================================



//=============================================================================
class Texture_button : public Abstract_button
{
protected:
	Vector2s size;
	Engine::Texture *curr_texture;
	Texture_scheme texture;

public:
	Texture_button (const Texture_scheme &_texture, const Vector2p pos, Button_reactive *window = nullptr);

	virtual void on_redraw ();
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);

	bool contains (int16_t x, int16_t y);

	bool pressed ();
	bool hovered ();

	void set_size (const Vector2s sz);
	const Vector2s get_size ();
};
//=============================================================================



//=============================================================================
class Slider_reactive
{
public:
	Slider_reactive () = default;
	virtual ~Slider_reactive () = default;

	virtual bool on_slider_move (Slider *slider) = 0;
};
//=============================================================================



//=============================================================================
class Slider : public Rectangle_window, public Hoverable
{
protected:
	int cursor;
	int16_t Vector2p::*axis;
	Rectangle_button *slider;
	Slider_reactive *window;

public:
	Slider () = default;
	Slider (const Vector2p pos, const Vector2s size, const Color &color, int16_t Vector2p::*_axis, const Color_scheme &clr_shm, const Vector2s s_size, Slider_reactive *win);

	float get_percent ();
	void set_percent (float percent);

	virtual bool handle_event (const Event &event);
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);
};
//=============================================================================

#endif // _BUTTON_HPP_