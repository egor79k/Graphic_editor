#ifndef _SCROLLBAR_HPP_
#define _SCROLLBAR_HPP_

class Scrollable_window;
class Scrollbar;
class Big_image;

#include "window.hpp"
#include "button.hpp"


class Scrollable_window : public Window
{
public:
	Scrollable_window (Vector2f _pos);

	virtual double scroll_str   (int delta) = 0;
	virtual double scroll_page  (int delta) = 0;
	virtual void scroll_percent (double percent) = 0;
	virtual void scroll_home    () = 0;
	virtual void scroll_end     () = 0;
};



struct Scrollbar_init
{
	struct Press_set
	{
		const char *released;
		const char *pressed;
	};

	Press_set up;
	Press_set down;
	Press_set slider;
};


namespace Default_scrollbar
{
const Scrollbar_init Texture = {
	{"graphics/textures/arrow_up_released.png", "graphics/textures/arrow_up_pressed.png"},
	{"graphics/textures/arrow_down_released.png", "graphics/textures/arrow_down_pressed.png"},
	{"graphics/textures/slider_released.png", "graphics/textures/slider_pressed.png"}
};

const int Width = 16;
};



class Scrollbar : public Window
{
private:
	Scrollable_window *scroll_window;

	uint32_t height;
	int slider_pos_up;
	int slider_pos_down;
	
	Texture_button arrow_up;
	Texture_button arrow_down;
	Texture_button slider;

public:
	Scrollbar (Scrollable_window *swin, const Vector2f &pos, uint32_t _height, const Scrollbar_init &init = Default_scrollbar::Texture, const Color &background = Color::White);

	virtual void on_redraw ();

	//virtual bool handle_event (const Event &event);
};



class Big_image : public Scrollable_window
{
private:
	Vector2f img_offset;
	Vector2f size;
	static const uint32_t Scroll_step = 10;
	uint32_t Scroll_len;
	double Scroll_step_percent;
	Texture_window image;
	Scrollbar scrollbar;

public:
	Big_image (const char *file, const Vector2f &_pos = Vector2f (), const Vector2f &_size = Vector2f (Engine::get_size ().x, Engine::get_size ().y));

	virtual void on_redraw ();

	//virtual bool handle_event (const Event &event);

	double scroll_str   (int delta);
	double scroll_page  (int delta);
	void scroll_percent (double percent);
	void scroll_home    ();
	void scroll_end     ();
};


#endif