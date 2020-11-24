#ifndef _BUTTON_HPP_
#define _BUTTON_HPP_

template <typename T>
struct Button_scheme;
class Abstract_button;
class Rectangle_button;
class Texture_button;


#include "window.hpp"

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
class Abstract_button : public Window
{
public:
	Abstract_button (const Vector2f &pos);
};
//=============================================================================



//=============================================================================
class Rectangle_button : public Abstract_button
{
private:
	Vector2f size;
	Color *curr_color;
	Color_scheme color;

public:
	Rectangle_button (const Color_scheme &clr_shm, const Vector2f &pos, const Vector2f &sz);

	virtual void on_redraw ();
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);

	bool contains (int x, int y);

	bool pressed ();
	bool hovered ();

	void set_size (const Vector2f &sz);
	const Vector2f get_size ();
};
//=============================================================================



//=============================================================================
class Texture_button : public Abstract_button
{
private:
	Vector2f size;
	Engine::Texture *curr_texture;
	Texture_scheme texture;

public:
	Texture_button (const Image_scheme &img_shm, const Vector2f &pos = Vector2f ());

	virtual void on_redraw ();
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);

	bool contains (int x, int y);

	bool pressed ();
	bool hovered ();

	void set_size (const Vector2f &sz);
	const Vector2f get_size ();
};
//=============================================================================

#endif // _BUTTON_HPP_