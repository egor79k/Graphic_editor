#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

template <typename T>
struct Button_scheme;
class Abstract_button;
class Rectangle_button;
class Texture_button;


#include "window.hpp"
#include "event_system.hpp"

//=============================================================================
template <typename T>
struct Button_scheme
{
	T released;
	T hovered;
	T pressed;
};

typedef Button_scheme<Color> Color_scheme;
typedef Button_scheme<const char *> Image_scheme;
typedef Button_scheme<Engine::Texture> Texture_scheme;
//=============================================================================



//=============================================================================
class Abstract_button : public Window, public Clickable
{
public:
	Abstract_button (const Vector2p pos);
};
//=============================================================================



//=============================================================================
class Rectangle_button : public Abstract_button
{
private:
	Vector2s size;
	Color *curr_color;
	Color_scheme color;

public:
	Rectangle_button (const Color_scheme &clr_shm, const Vector2p pos, const Vector2s sz);

	virtual void on_redraw ();
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);

	bool contains (int x, int y);

	bool pressed ();
	bool hovered ();

	void set_size (const Vector2s sz);
	const Vector2s get_size ();
};
//=============================================================================



//=============================================================================
class Texture_button : public Abstract_button
{
private:
	Vector2s size;
	Engine::Texture *curr_texture;
	Texture_scheme texture;

public:
	Texture_button (const Texture_scheme &_texture, const Vector2p pos = Vector2p ());

	virtual void on_redraw ();
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);

	bool contains (int x, int y);

	bool pressed ();
	bool hovered ();

	void set_size (const Vector2s sz);
	const Vector2s get_size ();
};
//=============================================================================

#endif // _BUTTON_HPP_