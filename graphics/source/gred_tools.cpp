#include "../include/gred_tools.hpp"


//=============================================================================
// ::::  Pencil  ::::
//=============================================================================
/*
void start_apply (Pixel_array &image, const Vector2p pos)
{

}*/


void Pencil::apply (Pixel_array &image, const Vector2p pos_0, const Vector2p pos_1)
{
	int16_t x0 = pos_0.x;
	int16_t y0 = pos_0.y;
	int16_t x1 = pos_1.x;
	int16_t y1 = pos_1.y;
	int16_t dx = x1 - x0;
	int16_t dy = y1 - y0;

	if (abs (dy) < abs (dx))
	{
		float k = static_cast<float> (dy) / static_cast<float> (dx);

		if (x0 > x1)
		{
			std::swap (x0, x1);
			std::swap (y0, y1);
		}

		for (int16_t x = x0; x < x1; ++x)
		{
			image.set_pixel (x, k * (x - x0) + y0, Color::Blue);
			image.set_pixel (x, k * (x - x0) + y0 + 1, Color::Blue);
			image.set_pixel (x, k * (x - x0) + y0 - 1, Color::Blue);
		}
	}
	else
	{
		float k = static_cast<float> (dx) / static_cast<float> (dy);

		if (y0 > y1)
		{
			std::swap (y0, y1);
			std::swap (x0, x1);
		}

		for (int16_t y = y0; y < y1; ++y)
		{
			image.set_pixel (k * (y - y0) + x0, y, Color::Blue);
			image.set_pixel (k * (y - y0) + x0 + 1, y, Color::Blue);
			image.set_pixel (k * (y - y0) + x0 - 1, y, Color::Blue);
		}
	}
}
//=============================================================================



//=============================================================================
// ::::  Tool_manager  ::::
//=============================================================================

Tool_manager::Tool_manager () :
	tools (TOOLS_NUM),
	curr_tool (PENCIL),
	canvas ({300, 10}, {600, 600}),
	applying (false)
{
	Event_system::attach_mouse_press (this);
	Event_system::attach_mouse_release (this);
	Event_system::attach_mouse_move(this);

	tools[PENCIL] = std::move (std::unique_ptr<Abstract_tool> (new Pencil));
}
//_____________________________________________________________________________

bool Tool_manager::on_mouse_press   (const Event::Mouse_click &click)
{
	prev_pos = Vector2p (click.x, click.y);
	applying = true;

	return true;
}
//_____________________________________________________________________________

bool Tool_manager::on_mouse_release (const Event::Mouse_click &click)
{
	applying = false;
	return false;
}
//_____________________________________________________________________________

bool Tool_manager::on_mouse_move    (const Event::Mouse_move &move)
{
	if (applying)
	{
		Vector2p curr_pos = Vector2p (move.x, move.y);
		tools[curr_tool]->apply (canvas.image, prev_pos, curr_pos);
		prev_pos = curr_pos;
		return true;
	}

	return false;
}
//=============================================================================