#ifndef _TEXT_TOOLS_HPP_
#define _TEXT_TOOLS_HPP_


class Text_window;
class Rectangle_text_window;
class Text_field_reactive;
class Text_field;


#include <string>
#include "button.hpp"
#include "window.hpp"


namespace Text
{
	const char Enter = 13;
	const char Backspace = 8;
};

//=============================================================================
class Text_window : public Window
{
protected:
	std::string text;
	uint16_t height;
	Color color;

public:
	Text_window (const Vector2p pos, const char *str, const uint16_t _height, const Color &_color = Color::Black);

	virtual void on_redraw ();
};
//=============================================================================



//=============================================================================
class Rectangle_text_window : public Rectangle_window
{
protected:
	std::string text;
	Color text_color;

public:
	Rectangle_text_window (const Vector2p pos, const char *str, const Vector2s size, const Color &bkg_color = Color::White, const Color &_text_color = Color::Black);

	virtual void on_redraw ();
};
//=============================================================================



//=============================================================================
class Text_field_reactive
{
public:
	Text_field_reactive () = default;
	virtual ~Text_field_reactive () = default;

	virtual bool on_text_enter (Text_field *text_field, const char *text) = 0;
};
//=============================================================================



//=============================================================================
class Text_field : public Rectangle_text_window, public Textable, public Clickable
{
protected:
	bool active;
	Text_field_reactive *window;

public:
	Text_field (const Vector2p pos, const Vector2s size, Text_field_reactive *win, const Color &bkg_color = Color::White, const Color &_text_color = Color::Black);

	bool is_active ();
	void set_active (const bool cond);

	virtual bool handle_event     (const Event &event);
	virtual bool on_text_enter    (const Event::Text &symbol);
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
};
//=============================================================================



//=============================================================================
class Text_dialog_window : public Rectangle_window, public Button_reactive
{
protected:
	Text_field *text_field;

public:
	static const Color_scheme default_accept_button_scheme;

	Text_dialog_window (const Vector2p pos, const Vector2s size, const Color &color, const char *question, Text_field_reactive *win);

	virtual bool on_button_press   (Abstract_button *button);
	virtual bool on_button_release (Abstract_button *button);
};
//=============================================================================

#endif // _TEXT_TOOLS_HPP_