#include "../include/scrollbar.hpp"


Big_image::Big_image (const char *file) :
	image (file, Vector2<int> (0, 0))
{}

void Big_image::draw ()
{
	image.draw ();
}

bool Big_image::handle_event (const Event &event)
{
	if (event.type == Event::Mouse_pressed)
	{
		return true;
	}

	return false;
}

void Big_image::scroll_str     (int delta)
{}

void Big_image::scroll_page    (int delta)
{}

void Big_image::scroll_percent (int percent)
{}

void Big_image::scroll_home    ()
{}

void Big_image::scroll_end     ()
{}




Scrollbar::Scrollbar (const Init &init, int _height, Vector2<int> pos, const Color &background) :
	height (_height),
	array_up (init.up.released, pos),
	array_down (init.down.released, Vector2<int> (pos.x, pos.y + _height)),
	slider (init.slider.released, Vector2<int> (pos.x, pos.y + _height / 3))
{}


void Scrollbar::draw ()
{
	array_up.draw ();
	array_down.draw ();
	slider.draw ();
}