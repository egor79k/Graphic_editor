#ifndef _EVENT_SYSTEM_HPP_
#define _EVENT_SYSTEM_HPP_

class Event_system;

#include <vector>
#include "window.hpp"

//=============================================================================
class Event_system
{
private:
	static std::vector<Abstract_window *> attached_on_redraw;
	static std::vector<Abstract_window *> attached_on_mouse_press;
	static std::vector<Abstract_window *> attached_on_mouse_release;
	static std::vector<Abstract_window *> attached_on_mouse_move;

public:
	static void dispatch_redraw ();
	static void dispatch_event ();

	static void attach_redraw (Abstract_window *window);
	static void attach_mouse_press (Abstract_window *window);
	static void attach_mouse_release (Abstract_window *window);
	static void attach_mouse_move (Abstract_window *window);
};
//=============================================================================

#endif // _EVENT_SYSTEM_HPP_