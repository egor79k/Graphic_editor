#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "vector2.hpp"
#include "event.hpp"

class Window
{
private:
	Vector2<int> pos;

public:
	Window ();

	virtual void draw ();

	virtual bool handle_event (const Event &event);
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