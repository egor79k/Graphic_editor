#ifndef _EVENT_SYSTEM_HPP_
#define _EVENT_SYSTEM_HPP_

class Event_system;
class Drawable;
class Clickable;
class Hoverable;
class Button_reactive;

#include <vector>

#include "../EngineSet.hpp"

//=============================================================================
class Event_system
{
private:
	static std::vector<Drawable *> attached_on_redraw;
	static std::vector<Clickable *> attached_on_mouse_press;
	static std::vector<Clickable *> attached_on_mouse_release;
	static std::vector<Hoverable *> attached_on_mouse_move;

public:
	Event_system () = delete;

	static void dispatch_redraw ();
	static void dispatch_event ();

	static void attach_redraw (Drawable *window);
	static void attach_mouse_press (Clickable *window);
	static void attach_mouse_release (Clickable *window);
	static void attach_mouse_move (Hoverable *window);

	static void detach_redraw (Drawable *window);
	static void detach_mouse_press (Clickable *window);
	static void detach_mouse_release (Clickable *window);
	static void detach_mouse_move (Hoverable *window);
};
//=============================================================================



//=============================================================================
class Drawable
{
public:
	Drawable ();
	virtual ~Drawable ();

	virtual void handle_redraw ();
	virtual void on_redraw () = 0;
};
//=============================================================================



//=============================================================================
class Clickable
{
public:
	Clickable ();
	virtual ~Clickable ();

	virtual bool handle_mouse_press   (const Event::Mouse_click &click);
	virtual bool handle_mouse_release (const Event::Mouse_click &click);

	virtual bool on_mouse_press   (const Event::Mouse_click &click) = 0;
	virtual bool on_mouse_release (const Event::Mouse_click &click) = 0;
};
//=============================================================================



//=============================================================================
class Hoverable : public Clickable
{
public:
	Hoverable ();

	virtual ~Hoverable ();

	virtual bool handle_mouse_move (const Event::Mouse_move &move);

	virtual bool on_mouse_move (const Event::Mouse_move &move) = 0;
};
//=============================================================================


/*
//=============================================================================
class Button_reactive
{
public:
	Button_reactive () = default;

	virtual ~Button_reactive () = default;

	virtual bool handle_button_press   (Abstract_button *button);
	virtual bool handle_button_release (Abstract_button *button);

	virtual bool on_button_press   (Abstract_button *button) = 0;
	virtual bool on_button_release (Abstract_button *button) = 0;
};
//=============================================================================
*/

/*
//=============================================================================
class Dragable : public Clickable
{
public:
	Dragable ();

	~Dragable ();
};
//=============================================================================
*/
#endif // _EVENT_SYSTEM_HPP_