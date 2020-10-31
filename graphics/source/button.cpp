#include "../include/button.hpp"


Texture_button::Texture_button (const char *released_img, const char *pressed_img, Vector2<int> _pos) :
	Window (_pos),
	released_texture (released_img),
	pressed_texture (pressed_img)
{
	curr_texture = &released_texture;
}


void Texture_button::draw ()
{
	curr_texture->draw_sprite (get_position ());
}


bool Texture_button::handle_event (const Event &event)
{
	if (event.type == Event::Mouse_pressed && contains (event.mouse_button.x, event.mouse_button.y))
	{
		curr_texture = &pressed_texture;
		return true;
	}

	if (event.type == Event::Mouse_released)
	{
		curr_texture = &released_texture;
		return true;
	}	

	return false;
}


bool Texture_button::contains (int x, int y)
{
	Vector2<uint32_t> size = curr_texture->get_size ();
	Vector2<int> pos = get_position ();
	return (pos.x < x && x < (pos.x + size.x) && pos.y < y && y < (pos.y + size.y));
}


bool Texture_button::pressed ()
{
	return &pressed_texture == curr_texture;
}


Vector2<uint32_t> Texture_button::get_size ()
{
	return curr_texture->get_size ();
}



/*
Button::Button (const sf::RectangleShape &_rectangle, const sf::Text &_text) :
	rectangle (_rectangle),
	text (_text)
{}


void Button::set_position (const sf::Vector2f &pos)
{
	rectangle.setPosition (pos);
	text.setPosition (pos.x + (rectangle.getSize ().x - text.getString ().getSize () * text.getCharacterSize () / 2) / 2, pos.y + 1);
}


void Button::set_fill_color (const sf::Color &color)
{
	rectangle.setFillColor (color);
}


const sf::Color &Button::get_fill_color () const
{
	return rectangle.getFillColor ();
}


void Button::set_text_color (const sf::Color &color)
{
	text.setFillColor (color);
}


bool Button::contains (int x, int y) const
{
	return rectangle.getGlobalBounds ().contains (x, y);
}


bool Button::contains (sf::Vector2f &coord) const
{
	return rectangle.getGlobalBounds ().contains (coord);
}


void Button::draw (sf::RenderWindow &window) const
{
	window.draw (rectangle);
	window.draw (text);
}


void Button::action ()
{
	printf ("Abstract Action\n");
}*/