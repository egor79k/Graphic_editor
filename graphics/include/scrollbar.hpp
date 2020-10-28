#ifndef _SCROLLBAR_HPP_
#define _SCROLLBAR_HPP_

#include "window.hpp"


class Scrollable_window : public Window
{
public:
	virtual void scroll_str     (int delta) = 0;
	virtual void scroll_page    (int delta) = 0;
	virtual void scroll_percent (int percent) = 0;
	virtual void scroll_home    () = 0;
	virtual void scroll_end     () = 0;
};



class Big_image : public Scrollable_window
{
private:
	static const int Scroll_step = 10;
	Texture_window image;
	//Scrollbar scrollbar;

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



class Scrollbar : public Window
{
private:
	Scrollable_window *scroll_window;

	int height;
	Texture_window array_up;
	Texture_window array_down;
	Texture_window slider;
	//Rectangle_window background;

	/*static const int windows_num = 4;
	Window *windows[windows_num];*/

public:
	struct Init
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

	Scrollbar (Scrollable_window *swin, const Init &init, int _height, Vector2<int> pos, const Color &background = Color::White);

	virtual void draw ();

	virtual bool handle_event (const Event &event);
};


#endif