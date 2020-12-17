#ifndef _EVENT_SYSTEM_HPP_
#define _EVENT_SYSTEM_HPP_

class Event_system;
class Drawable;
class Clickable;
class Hoverable;
class Button_reactive;

#include <vector>

#include "../EngineSet.hpp"
#include "abstract_window.hpp"

//=============================================================================
class Event_system
{
private:
	static std::vector<Abstract_window *> attached_on_redraw;
//	static std::vector<Clickable *> attached_on_mouse_press;
//	static std::vector<Clickable *> attached_on_mouse_release;
//	static std::vector<Hoverable *> attached_on_mouse_move;

	static std::vector<Abstract_window *> attached;

public:
	Event_system () = delete;

	static void dispatch_redraw ();
	static void dispatch_event ();

	static void attach (Abstract_window *window);
	static void attach_redraw (Abstract_window *window);

	static void detach (Abstract_window *window);
	static void detach_redraw (Abstract_window *window);

//	static void attach_mouse_press (Clickable *window);
//	static void attach_mouse_release (Clickable *window);
//	static void attach_mouse_move (Hoverable *window);


//	static void detach_mouse_press (Clickable *window);
//	static void detach_mouse_release (Clickable *window);
//	static void detach_mouse_move (Hoverable *window);

};
//=============================================================================



//=============================================================================
class Clickable
{
public:
	Clickable () = default;
	virtual ~Clickable () = default;

	bool handle_clickable (const Event &event);
	virtual bool on_mouse_press   (const Event::Mouse_click &click) = 0;
	virtual bool on_mouse_release (const Event::Mouse_click &click) = 0;
};
//=============================================================================



//=============================================================================
class Hoverable : public Clickable
{
public:
	Hoverable () = default;
	virtual ~Hoverable () = default;

	bool handle_hoverable (const Event &event);
	virtual bool on_mouse_move (const Event::Mouse_move &move) = 0;
};
//=============================================================================



//=============================================================================
class Textable
{
public:
	Textable () = default;
	virtual ~Textable () = default;

	bool handle_textable (const Event &event);
	virtual bool on_text_enter (const Event::Text &symbol) = 0;
};
//=============================================================================


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