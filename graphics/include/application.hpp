#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "window.hpp"

class Application
{
private:
	sf::RenderWindow rwin;

	std::vector<Window *> windows;
	
public:
	Application (int width, int height, const char *window_header);

	static Application &initialize (int width, int height, const char *window_header);

	void run ();

	void add_window (Window *window);

	sf::RenderWindow &get_rwin ();
};

#endif