#ifndef _ABSTRACT_WINDOW_HPP_
#define _ABSTRACT_WINDOW_HPP_


#include <vector>
#include "event.hpp"

//=============================================================================
class Abstract_window
{
protected:
	std::vector<Abstract_window *> subwindows;
	//Abstract_window *parent_window;

public:
	Abstract_window () = default;
	virtual ~Abstract_window ();

	size_t add_subwindow (Abstract_window *win);
	void remove_subwindow (Abstract_window *win);
	void remove_subwindow (size_t num);

	virtual bool handle_event (const Event &event);
	virtual void handle_redraw ();
	virtual void on_redraw () = 0;
};
//=============================================================================

#endif // _ABSTRACT_WINDOW_HPP_