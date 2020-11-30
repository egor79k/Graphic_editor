#include "../include/scrollbar.hpp"


Scrollable_window::Scrollable_window (const Vector2p _pos) :
	Window (_pos)
{}



Scrollbar::Scrollbar (Scrollable_window *swin, const Vector2p pos, uint32_t _height, const Scrollbar_init &init, const Color &background) :
	Window (pos),
	scroll_window (swin),
	height (_height),
	arrow_up ({init.up.released, init.up.released, init.up.pressed}, pos),
	arrow_down ({init.down.released, init.down.released, init.down.pressed}),
	slider ({init.slider.released, init.slider.released, init.slider.pressed})
{
	slider_pos_up = pos.y + arrow_up.get_size ().y;
	slider_pos_down = pos.y + height - arrow_down.get_size ().y - slider.get_size ().y;

	slider.set_position (pos.x, slider_pos_up);
	arrow_down.set_position (pos.x, slider_pos_down + slider.get_size ().y);
}


void Scrollbar::on_redraw ()
{
	Engine::draw::rectangle (pos, Vector2s (arrow_up.get_size ().x, height), Color::White);
	arrow_up.on_redraw ();
	arrow_down.on_redraw ();
	slider.on_redraw ();
}

/*
bool Scrollbar::handle_event (const Event &event)
{
	static int cursor_in_slider_offset;

	if (arrow_up.handle_event (event) && event.type == Event::Mouse_pressed)
	{
		slider.set_position (slider.get_position ().x, slider.get_position ().y - (slider_pos_down - slider_pos_up) * scroll_window->scroll_str (-1));
	}

	if (arrow_down.handle_event (event) && event.type == Event::Mouse_pressed)
	{
		slider.set_position (slider.get_position ().x, slider.get_position ().y + (slider_pos_down - slider_pos_up) * scroll_window->scroll_str (1));
	}

	if (slider.handle_event (event) && event.type == Event::Mouse_pressed)
		cursor_in_slider_offset = event.mouse_click.y - slider.get_position ().y;

	if (slider.pressed () && event.type == Event::Mouse_moved)
	{
		//printf("CP: %d:%d NP: %d:%d\n", slider.get_position ().x, slider.get_position ().y, event.mouse_move.x, event.mouse_move.y);
		int new_slider_pos = event.mouse_move.y - cursor_in_slider_offset;
		if (new_slider_pos >= slider_pos_up)
		{
			if (new_slider_pos > slider_pos_down)
				new_slider_pos = slider_pos_down;
		}
		else
			new_slider_pos = slider_pos_up;

		slider.set_position (slider.get_position ().x, new_slider_pos);
		scroll_window->scroll_percent ((double) (new_slider_pos - slider_pos_up) / (slider_pos_down - slider_pos_up));
	}

	return false;
}
*/


Big_image::Big_image (const char *file, const Vector2p _pos, const Vector2s _size) :
	Scrollable_window (_pos),
	img_offset (),
	size (_size),
	image (file, _pos),
	scrollbar (this, Vector2p (_pos.x + _size.x - Default_scrollbar::Width, _pos.y), _size.y)
{
	Scroll_len = image.get_size ().y - _size.y;
	Scroll_step_percent = (double) Scroll_step / Scroll_len;
	//printf("Window %d:%d, Scbr position %d:%d\n", size.x, size.y, _pos.x + _size.x - Default_scrollbar::Width, _pos.y);
	fflush (stdout);
}

void Big_image::on_redraw ()
{
	image.draw (Vector2<Vector2s> (img_offset, size));
	//printf("Draw img %d : %d | %d : %d\n", img_offset.x, img_offset.y, (img_offset + size).x, (img_offset + size).y);
	scrollbar.on_redraw ();
}
/*
bool Big_image::handle_event (const Event &event)
{
	return scrollbar.handle_event (event);
}
*/
double Big_image::scroll_str     (int delta)
{
	//if ((delta > 0 && Scroll_len - image.get_position ().y) < Scroll_step)
	//{
	//	image.set_position (image.get_position ().x, get_position ().y);
	//	return 
	//}

		img_offset.y += delta * Scroll_step;
		return Scroll_step_percent;
}

double Big_image::scroll_page    (int delta)
{
	return 0;
}

void Big_image::scroll_percent (double percent)
{
	img_offset.y = (double) Scroll_len * percent;
	//printf ("Scroll mile on %f | %f\n", percent, Scroll_step_percent);
}

void Big_image::scroll_home    ()
{}

void Big_image::scroll_end     ()
{}
