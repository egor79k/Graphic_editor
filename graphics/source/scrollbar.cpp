#include "../include/scrollbar.hpp"


Scrollbar::Scrollbar (Scrollable_window *swin, Vector2<int> pos, uint32_t _height, const Scrollbar_init &init, const Color &background) :
	scroll_window (swin),
	height (_height),
	arrow_up (init.up.released, init.up.pressed, pos),
	arrow_down (init.down.released, init.down.pressed, Vector2<int> (pos.x, pos.y + _height)),
	slider (init.slider.released, init.slider.pressed, Vector2<int> (pos.x, pos.y + arrow_up.get_size ().y))
{}


void Scrollbar::draw ()
{
	arrow_up.draw ();
	arrow_down.draw ();
	slider.draw ();
}


bool Scrollbar::handle_event (const Event &event)
{
	if (arrow_up.handle_event (event) && event.type == Event::Mouse_pressed)
		scroll_window->scroll_str (1);

	if (arrow_down.handle_event (event) && event.type == Event::Mouse_pressed)
		scroll_window->scroll_str (-1);

	slider.handle_event (event);

	if (slider.pressed () && event.type == Event::Mouse_moved)
	{
		printf("CP: %d:%d NP: %d:%d\n", slider.get_position ().x, slider.get_position ().y, event.mouse_move.x, event.mouse_move.y);
		slider.set_position (slider.get_position ().x, event.mouse_move.y);
	}

	return false;
}



Big_image::Big_image (const char *file) :
	image (file, Vector2<int> (0, 0)),
	scrollbar (this, Vector2<int> (Engine::get_size ().x - 50, 0), Engine::get_size ().y - 50)
{}

void Big_image::draw ()
{
	image.draw ();
	scrollbar.draw ();
}

bool Big_image::handle_event (const Event &event)
{
	return scrollbar.handle_event (event);
}

void Big_image::scroll_str     (int delta)
{
	image.set_position (image.get_position () + Vector2<int>(0, delta * Scroll_step));
}

void Big_image::scroll_page    (int delta)
{}

void Big_image::scroll_percent (int percent)
{}

void Big_image::scroll_home    ()
{}

void Big_image::scroll_end     ()
{}
