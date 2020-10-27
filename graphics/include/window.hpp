#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>

class Window
{
public:
	Window ();
	virtual void draw () const = 0;
};

/*
class Rectangle_window : public Window
{
private:
	sf::rectangleShape rectangle

public:
	Rectangle_window () :
		Window ()
	{}

	virtual void draw (sf::RenderWindow &window) const;
};
*/

#endif