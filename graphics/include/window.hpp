#ifndef WINDOW_HPP
#define WINDOW_HPP

//#include <iostream>
#include "../EngineSet.hpp"
#include "vector2.hpp"
#include "event.hpp"
#include "color.hpp"

class Window
{
private:
	Vector2<int> pos;

public:
	Window ();
	Window (Vector2<int> _pos);
	Window (int x, int y);

	virtual void draw ();

	virtual bool handle_event (const Event &event);

	const Vector2<int> get_position () const;

	void set_position (const Vector2<int> _pos);
};


class Rectangle_window : public Window
{
private:
	Vector2<int> size;
	Color color;

public:
	Rectangle_window (Vector2<int> _pos, Vector2<int> _size, const Color &_color = Color::White);

	virtual void draw ();

	virtual bool handle_event (const Event &event);

	const Vector2<int> get_size () const;

	const Color get_color () const;
};


class Texture_window : public Window
{
private:
	Engine::Sprite sprite;

public:
	Texture_window (const char *texture_file, Vector2<int> _pos);

	//Texture_window (char *_texture, Vector2<int> _pos, Vector2<i>, Vector2<int> _size = Vector2<int> (), const Color &_col = Color::White);

	virtual void draw ();

	virtual bool handle_event (const Event &event);
};


#endif