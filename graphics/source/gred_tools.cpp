#include "../include/gred_tools.hpp"


//=============================================================================
// ::::  Pencil  ::::
//=============================================================================
/*
void start_apply (Pixel_array &image, const Vector2p pos)
{

}*/


void Pencil::apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1)
{
	int16_t x0 = pos_0.x;
	int16_t y0 = pos_0.y;
	int16_t x1 = pos_1.x;
	int16_t y1 = pos_1.y;
	int16_t dx = abs (x1 - x0);
	int16_t dy = abs (y1 - y0);
	int16_t Vector2p::*axis_0 = &Vector2p::x;
	int16_t Vector2p::*axis_1 = &Vector2p::y;

	if (dy > dx)
		std::swap (axis_0, axis_1);

		float k = static_cast<float> (pos_1.*axis_1 - pos_0.*axis_1) / static_cast<float> (pos_1.*axis_0 - pos_0.*axis_0);

		if (pos_0.*axis_0 > pos_1.*axis_0)
		{
			std::swap (pos_0.*axis_0, pos_1.*axis_0);
			std::swap (pos_0.*axis_1, pos_1.*axis_1);
		}

		for (int16_t x = pos_0.*axis_0; x < pos_1.*axis_0; ++x)
		{
			if (dy > dx)
			{
				image.set_pixel (k * (x - pos_0.*axis_0) + pos_0.*axis_1, x, Color::Blue);
				image.set_pixel (k * (x - pos_0.*axis_0) + pos_0.*axis_1 + 1, x, Color::Blue);
				image.set_pixel (k * (x - pos_0.*axis_0) + pos_0.*axis_1 - 1, x, Color::Blue);
			}
			else
			{
				image.set_pixel (x, k * (x - pos_0.*axis_0) + pos_0.*axis_1, Color::Blue);
				image.set_pixel (x, k * (x - pos_0.*axis_0) + pos_0.*axis_1 + 1, Color::Blue);
				image.set_pixel (x, k * (x - pos_0.*axis_0) + pos_0.*axis_1 - 1, Color::Blue);
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
	if (canvas.contains (click.x, click.y))
	{
		prev_pos = Vector2p (click.x, click.y) - canvas.pos;
		applying = true;
		return true;
	}

	return false;
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
		if (canvas.contains (move.x, move.y))
		{
			Vector2p curr_pos = Vector2p (move.x, move.y) - canvas.pos;
			tools[curr_tool]->apply (canvas.image, prev_pos, curr_pos);
			prev_pos = curr_pos;
			return true;
		}
	}

	return false;
}
//=============================================================================