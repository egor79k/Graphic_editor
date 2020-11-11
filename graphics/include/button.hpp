#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "window.hpp"

/*
class Button : public Window
{
private:
	Vector2<int> pos;

public:
	virtual void draw () = 0;

	virtual bool handle_event (const Event &event);

	bool on_mouse_click ();
	bool on_mouse_release ();
	bool on_mouse_inside ();


};
*/


class Texture_button : public Window
{
private:
	Engine::Texture *curr_texture;
	Engine::Texture released_texture;
	Engine::Texture pressed_texture;

public:
	Texture_button (const char *released_img, const char *pressed_img, Vector2<int> _pos = Vector2<int> ());

	virtual void draw ();

	virtual bool handle_event (const Event &event);

	bool contains (int x, int y);

	bool pressed ();

	Vector2<uint32_t> get_size ();
};



/*
	Button (const sf::RectangleShape &_rectangle, const sf::Text &_text);

	void set_position (const sf::Vector2f &pos);

	void set_fill_color (const sf::Color &color);

	const sf::Color &get_fill_color () const;

	void set_text_color (const sf::Color &color);

	bool contains (int x, int y) const;

	bool contains (sf::Vector2f &coord) const;

	virtual void draw (sf::RenderWindow &window) const;
	
	virtual void action ();*/
#endif