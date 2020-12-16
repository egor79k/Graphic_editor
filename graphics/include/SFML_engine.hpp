#ifndef _SFML_ENGINE_HPP_
#define _SFML_ENGINE_HPP_

#include <SFML/Graphics.hpp>
#include "event.hpp"
#include "vector2.hpp"
#include "color.hpp"
#include "pixel_array.hpp"


class SFML_engine
{
public:
	static void Match_empty (Event &event, sf::Event &sf_event);

	static void Match_size (Event &event, sf::Event &sf_event);

	static void Match_key (Event &event, sf::Event &sf_event);

	static void Match_text (Event &event, sf::Event &sf_event);

	static void Match_mouse_move (Event &event, sf::Event &sf_event);

	static void Match_mouse_click (Event &event, sf::Event &sf_event);

	static void Match_mouse_wheel (Event &event, sf::Event &sf_event);

	struct EMatcher
	{
		Event::Event_type type;
		void (*Match)(Event &, sf::Event &);
	};


	static sf::RenderWindow window;
	static sf::Font text_font;

	static void initialize (int width, int height, const char *window_header);


	static bool poll_event (Event &event);

	static bool running ();

	static void exit ();


	static void flush_screen ();

	static void fill (const Color &col);


	static Vector2s get_size ();



	class Texture
	{
	private:
		sf::Texture texture;
		
	public:
		Texture (const char *texture_file);
		Texture (const char *texture_file, const Vector2<Vector2s> &area);

		void draw_sprite (const Vector2p pos);
		void draw_sprite (const Vector2p pos, const Vector2s size);
		void draw_sprite (const Vector2p pos, const Vector2<Vector2s> &area);
		Vector2s get_size ();
	};


	struct draw
	{
		static void rectangle (const Vector2p pos, const Vector2s size, const Color &col);
		static void image (const Vector2p pos, const Pixel_array &image);
		static void text (const Vector2p pos, const char *string, const int size, const Color &col);
	};
};


#endif