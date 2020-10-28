#ifndef _SFML_ENGINE_HPP_
#define _SFML_ENGINE_HPP_

#include <SFML/Graphics.hpp>
#include "event.hpp"
#include "vector2.hpp"
#include "color.hpp"


class SFML_engine
{
public:
	/*void Match_empty (Event &event, sf::Event &sf_event)
	{}

	void Match_size (Event &event, sf::Event &sf_event)
	{
		event.size.width = sf_event.size.width;
		event.size.height = sf_event.size.height;
	}

	void Match_key (Event &event, sf::Event &sf_event)
	{
		event.key.alt = sf_event.key.alt;
		event.key.control = sf_event.key.control;
		event.key.shift = sf_event.key.shift;
		event.key.system = sf_event.key.system;
	}

	void Match_text (Event &event, sf::Event &sf_event)
	{
		event.text.unicode = sf_event.text.unicode;
	}

	void Match_mouse_move (Event &event, sf::Event &sf_event)
	{
		event.mouse_button.button = (int) sf_event.mouseButton.button;
		event.mouse_button.x = sf_event.mouseButton.x;
		event.mouse_button.y = sf_event.mouseButton.y;
	}

	void Match_mouse_button (Event &event, sf::Event &sf_event)
	{
		event.mouse_button.button = (int) sf_event.mouseButton.button;
		event.mouse_move.x = sf_event.mouseMove.x;
		event.mouse_move.y = sf_event.mouseMove.y;
	}

	void Match_mouse_wheel (Event &event, sf::Event &sf_event)
	{
		event.mouse_wheel.delta = sf_event.mouseWheel.delta;
		event.mouse_wheel.x = sf_event.mouseWheel.x;
		event.mouse_wheel.y = sf_event.mouseWheel.y;
	}


	struct EMatcher
	{
		Event::Event_type type;
		void (*SFML_engine::Match) (Event &, sf::Event &);
	};

	const static EMatcher Event_match[24] = {
		{Event::Closed, Match_empty},
		{Event::Resized, Match_size},
		{Event::Unfocused, Match_empty},
		{Event::Focused, Match_empty},
		{Event::Text_entered, Match_text},
		{Event::Key_pressed, Match_key},
		{Event::Key_released, Match_key},
		{Event::Mouse_wheel_moved, Match_mouse_wheel},
		{Event::Unused_event, Match_empty},
		{Event::Mouse_pressed, Match_mouse_button},
		{Event::Mouse_released, Match_mouse_button},
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
	};*/

	static sf::RenderWindow window;

	static void initialize (int width, int height, const char *window_header);

	static bool poll_event (Event &event);

	static bool working ();

	static void flush_screen ();

	static void fill (const Color &col);

	static void exit ();

	class Sprite
	{
	private:
		sf::Texture texture;
		sf::Sprite sprite;
		
	public:
		Sprite (const char *texture_file, const Vector2<int> pos = {0, 0});

		Sprite (const char *texture_file, const Vector2<Vector2<int>> &area, const Color &col);

		void draw ();
	};

	struct draw
	{
		static void rectangle (Vector2<int> pos, Vector2<int> size, const Color &col);
	};
};


#endif