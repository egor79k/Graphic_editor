#ifndef _SCROLLBAR_HPP_
#define _SCROLLBAR_HPP_

#include "window.hpp"
#include "button.hpp"


class Scrollable_window : public Window
{
public:
	virtual void scroll_str     (int delta) = 0;
	virtual void scroll_page    (int delta) = 0;
	virtual void scroll_percent (int percent) = 0;
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



const Scrollbar_init Default_scrollbar_texture = {
	{"graphics/textures/arrow_up_released.png", "graphics/textures/arrow_up_pressed.png"},
	{"graphics/textures/arrow_down_released.png", "graphics/textures/arrow_down_pressed.png"},
	{"graphics/textures/slider_released.png", "graphics/textures/slider_pressed.png"}
};



class Scrollbar : public Window
{
private:
	Scrollable_window *scroll_window;

	uint32_t height;
	Texture_button arrow_up;
	Texture_button arrow_down;
	Texture_button slider;
	//Rectangle_window background;

	/*static const int windows_num = 4;
	Window *windows[windows_num];*/

public:
	Scrollbar (Scrollable_window *swin, Vector2<int> pos, uint32_t _height, const Scrollbar_init &init = Default_scrollbar_texture, const Color &background = Color::White);

	virtual void draw ();

	virtual bool handle_event (const Event &event);
};



class Big_image : public Scrollable_window
{
private:
	static const int Scroll_step = 10;
	Texture_window image;
	Scrollbar scrollbar;

public:
	Big_image (const char *file);

	virtual void draw ();

	virtual bool handle_event (const Event &event);

	void scroll_str     (int delta);
	void scroll_page    (int delta);
	void scroll_percent (int percent);
	void scroll_home    ();
	void scroll_end     ();
};


#endif