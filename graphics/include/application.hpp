#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

class Application;

#include <vector>
#include "../EngineSet.hpp"
#include "event_system.hpp"
#include "window.hpp"


//=============================================================================
class Application
{
private:
	static std::vector<Window *> windows;

	
public:
	Application () = delete;

	static void initialize (int width, int height, const char *window_header);

	static void step ();

	static void run ();

	static void add_window (Window *window);
};
//=============================================================================

#endif