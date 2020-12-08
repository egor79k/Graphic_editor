#include "../include/SFML_engine.hpp"


sf::RenderWindow SFML_engine::window (sf::VideoMode (100, 100), "Text");


void SFML_engine::initialize (int width, int height, const char *window_header)
{
	window.create (sf::VideoMode (width, height), window_header);
}


void SFML_engine::Match_empty (Event &event, sf::Event &sf_event)
{}

void SFML_engine::Match_size (Event &event, sf::Event &sf_event)
{
	event.size.width = sf_event.size.width;
	event.size.height = sf_event.size.height;
}

void SFML_engine::Match_key (Event &event, sf::Event &sf_event)
{
	event.key.code = (Keyboard::Key) sf_event.key.code;
	event.key.alt = sf_event.key.alt;
	event.key.control = sf_event.key.control;
	event.key.shift = sf_event.key.shift;
	event.key.system = sf_event.key.system;
}

void SFML_engine::Match_text (Event &event, sf::Event &sf_event)
{
	event.text.unicode = sf_event.text.unicode;
}

void SFML_engine::Match_mouse_move (Event &event, sf::Event &sf_event)
{
	event.mouse_move.x = sf_event.mouseMove.x;
	event.mouse_move.y = sf_event.mouseMove.y;
}

void SFML_engine::Match_mouse_click (Event &event, sf::Event &sf_event)
{
	event.mouse_click.button = (Mouse::Button) sf_event.mouseButton.button;
	event.mouse_click.x = sf_event.mouseButton.x;
	event.mouse_click.y = sf_event.mouseButton.y;
}

void SFML_engine::Match_mouse_wheel (Event &event, sf::Event &sf_event)
{
	event.mouse_wheel.delta = sf_event.mouseWheel.delta;
	event.mouse_wheel.x = sf_event.mouseWheel.x;
	event.mouse_wheel.y = sf_event.mouseWheel.y;
}


bool SFML_engine::poll_event (Event &event)
{
	const static EMatcher Event_match[] = {
		{Event::Closed, Match_empty},
		{Event::Resized, Match_size},
		{Event::Unfocused, Match_empty},
		{Event::Focused, Match_empty},
		{Event::Text_entered, Match_text},
		{Event::Key_pressed, Match_key},
		{Event::Key_released, Match_key},
		{Event::Mouse_wheel_moved, Match_mouse_wheel},
		{Event::Unused_event, Match_empty},
		{Event::Mouse_pressed, Match_mouse_click},
		{Event::Mouse_released, Match_mouse_click},
		{Event::Mouse_moved, Match_mouse_move},
		{Event::Mouse_went_in, Match_empty},
		{Event::Mouse_went_out, Match_empty},
		{Event::Unused_event, Match_empty},
		{Event::Unused_event, Match_empty},
		{Event::Unused_event, Match_empty},
		{Event::Unused_event, Match_empty},
		{Event::Unused_event, Match_empty},
		{Event::Unused_event, Match_empty},
		{Event::Unused_event, Match_empty},
		{Event::Unused_event, Match_empty},
		{Event::Unused_event, Match_empty},
		{Event::Unused_event, Match_empty}
	};

	sf::Event sf_event;

	if (window.pollEvent (sf_event))
	{
		event.type = Event_match[sf_event.type].type;
		Event_match[sf_event.type].Match (event, sf_event);
		return true;
	}

	return false;
}

bool SFML_engine::running ()
{
	return window.isOpen ();
}

void SFML_engine::exit ()
{
	window.close ();
}


void SFML_engine::flush_screen ()
{
	window.display ();
}

void SFML_engine::fill (const Color &col)
{
	window.clear (sf::Color (col.r, col.g, col.b, col.a));
}


Vector2s SFML_engine::get_size ()
{
	sf::Vector2u size = window.getSize ();
	return Vector2s (size.x, size.y);
}



SFML_engine::Texture::Texture (const char *texture_file)
{
	texture.loadFromFile (texture_file);
}


SFML_engine::Texture::Texture (const char *texture_file, const Vector2<Vector2s> &area)
{
	texture.loadFromFile (texture_file, sf::IntRect (area.x.x, area.x.y, area.y.x, area.y.y));
}


void SFML_engine::Texture::draw_sprite (const Vector2p pos)
{
	sf::Sprite sprite (texture);
	sprite.setPosition (pos.x, pos.y);
	window.draw (sprite);
}


void SFML_engine::Texture::draw_sprite (const Vector2p pos, const Vector2s size)
{
	sf::Sprite sprite (texture);
	sprite.setPosition (pos.x, pos.y);
	sprite.setScale ((float) size.x / texture.getSize ().x, (float) size.y / texture.getSize ().y);
	window.draw (sprite);
}


void SFML_engine::Texture::draw_sprite (const Vector2p pos, const Vector2<Vector2s> &area)
{
	sf::Sprite sprite (texture, sf::IntRect (area.x.x, area.x.y, area.y.x, area.y.y));
	sprite.setPosition (pos.x, pos.y);
	window.draw (sprite);
}


Vector2s SFML_engine::Texture::get_size ()
{
	sf::Vector2u size = texture.getSize ();
	return Vector2s (size.x, size.y);
}



void SFML_engine::draw::rectangle (const Vector2p pos, const Vector2s size, const Color &col)
{
	sf::RectangleShape rect (sf::Vector2f (size.x, size.y));
	rect.setPosition (pos.x, pos.y);
	rect.setFillColor (sf::Color (col.r, col.g, col.b, col.a));

	window.draw (rect);
}


void SFML_engine::draw::image (const Vector2p pos, const Pixel_array &image)
{
	sf::Texture texture;
	texture.create (image.get_size ().x, image.get_size ().y);
	texture.update (image.get_origin ());
	sf::Sprite sprite (texture);
	sprite.setPosition (pos.x, pos.y);
	window.draw (sprite);
}