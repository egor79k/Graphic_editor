#ifndef _TEXT_TOOLS_HPP_
#define _TEXT_TOOLS_HPP_

#include <string>
#include "button.hpp"
#include "window.hpp"


namespace Text
{
	const char Enter = 13;
	const char Backspace = 8;
};


//=============================================================================
class Text_window : public Rectangle_window
{
protected:
	std::string text;
	Color text_color;

public:
	Text_window (const Vector2p pos, const char *str, const Vector2s size, const Color &bkg_color = Color::White, const Color &_text_color = Color::Black);

	virtual void on_redraw ();
};
//=============================================================================



//=============================================================================
class Text_field_reactive
{
	Text_field_reactive () = default;
	virtual ~Text_field_reactive () = default;

	virtual bool on_text_enter (const char *text) = 0;
};
//=============================================================================



//=============================================================================
class Text_field : public Text_window, public Textable, public Clickable
{
protected:
	bool active;

public:
	Text_field (const Vector2p pos, const Vector2s size);

	virtual bool handle_event     (const Event &event);
	virtual bool on_text_enter    (const Event::Text &symbol);
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
};
//=============================================================================

#endif // _TEXT_TOOLS_HPP_