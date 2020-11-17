#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include <vector>
#include "../EngineSet.hpp"
#include "window.hpp"

using Engine = SFML_engine;

class Application
{
private:
	//sf::RenderWindow rwin;

	static std::vector<Window *> windows;

	
public:
	//Application (int width, int height, const char *window_header);

	//Application (const Application &) = delete;

	//Application &operator= (const Application &) = delete;

	static void initialize (int width, int height, const char *window_header);

	static void run ();

	static void add_window (Window *window);

	//void add_window (Abstract_window *window);
};

#endif