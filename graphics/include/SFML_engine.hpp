#ifndef _SFML_ENGINE_HPP_
#define _SFML_ENGINE_HPP_

#include <SFML/Graphics.hpp>
#include "event.hpp"
#include "vector2.hpp"
#include "color.hpp"


class SFML_engine
{
public:
	static void Match_empty (Event &event, sf::Event &sf_event);

	static void Match_size (Event &event, sf::Event &sf_event);

	static void Match_key (Event &event, sf::Event &sf_event);

	static void Match_text (Event &event, sf::Event &sf_event);

	static void Match_mouse_move (Event &event, sf::Event &sf_event);

	static void Match_mouse_button (Event &event, sf::Event &sf_event);

	static void Match_mouse_wheel (Event &event, sf::Event &sf_event);

	struct EMatcher
	{
		Event::Event_type type;
		void (*Match)(Event &, sf::Event &);
	};


	static sf::RenderWindow window;

	static void initialize (int width, int height, const char *window_header);


	static bool poll_event (Event &event);

	static bool working ();

	static void exit ();


	static void flush_screen ();

	static void fill (const Color &col);


	static Vector2<uint32_t> get_size ();



	class Texture
	{
	private:
		sf::Texture texture;
		//sf::Sprite sprite;
		
	public:
		Texture (const char *texture_file);

		void draw_sprite (Vector2<int> pos);
		void draw_sprite (Vector2<int> pos, const Vector2<Vector2<uint32_t>> &area);
		Vector2<uint32_t> get_size ();
		//Texture (const char *texture_file, const Vector2<Vector2<int>> &area, const Color &col);
	};


	struct draw
	{
		static void rectangle (Vector2<int> pos, Vector2<int> size, const Color &col);
		//static void sprite (const Texture &texture, Vector2<int> pos);
		//static void sprite (const Texture &texture, Vector2<int> pos, const Vector2<Vector2<int>> &area);
	};
};


#endif