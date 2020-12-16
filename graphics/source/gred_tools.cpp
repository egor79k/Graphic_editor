#include "../include/gred_tools.hpp"


//=============================================================================
// ::::  Pencil  ::::
//=============================================================================

void Pencil::apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1, const Tool_properties &prop)
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
		const Vector2s sz = image.get_size ();

		if (pos_0.*axis_0 > pos_1.*axis_0)
		{
			std::swap (pos_0.*axis_0, pos_1.*axis_0);
			std::swap (pos_0.*axis_1, pos_1.*axis_1);
		}

		for (int16_t x = pos_0.*axis_0; x < pos_1.*axis_0; ++x)
		{
			for (int i = -prop.thickness; i <= prop.thickness; ++i)
				for (int j = -prop.thickness; j <= prop.thickness; ++j)
					if (i * i + j * j < prop.thickness * prop.thickness)
					{
						Vector2p point;

						if (dy > dx)
							point = Vector2p (k * (x - pos_0.*axis_0) + pos_0.*axis_1 + i, x + j);
						else
							point = Vector2p (x + i, k * (x - pos_0.*axis_0) + pos_0.*axis_1 + j);

						if (point.x < 0)
							point.x = 0;
						else if (point.x >= sz.x)
							point.x = sz.x - 1;

						if (point.y < 0)
							point.y = 0;
						else if (point.y >= sz.y)
							point.y = sz.y - 1;

						image.set_pixel (point.x, point.y, prop.color);
					}
		}
}
//=============================================================================



//=============================================================================
// ::::  Tool_manager  ::::
//=============================================================================

const Texture_scheme Tool_manager::default_textures[] = {
	{{"graphics/textures/graphic_tool_set_released.png", {{0, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_hovered.png", {{0, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_pressed.png", {{0, 0}, {64, 64}}}},
	{{"graphics/textures/graphic_tool_set_released.png", {{64, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_hovered.png", {{64, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_pressed.png", {{64, 0}, {64, 64}}}},
	{{"graphics/textures/graphic_tool_set_released.png", {{128, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_hovered.png", {{128, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_pressed.png", {{128, 0}, {64, 64}}}},
};
//_____________________________________________________________________________

Tool_manager::Tool_manager () :
	Rectangle_window (Vector2p (0, 0), Vector2s (Engine::get_size ().x / 8, Engine::get_size ().y), Color (220, 220, 220)),
	curr_tool (PENCIL),
	properties ({Color::Blue, 25}),
	tools (TOOLS_NUM),
	applying (false),
	canvas ({300, 10}, {600, 600})
{
	tools[PENCIL] = std::move (std::unique_ptr<Abstract_tool> (new Pencil));

	subwindows.push_back (new Texture_button (default_textures[PENCIL], {20, 64}, this));
	subwindows.push_back (new Texture_button (default_textures[ERASER], {20, 128}, this));
	subwindows.push_back (new Texture_button (default_textures[FILLER], {20, 192}, this));
}
//_____________________________________________________________________________

bool Tool_manager::handle_event (const Event &event)
{
	for (auto win: subwindows)
		if (win->handle_event (event))
			return true;

	return handle_hoverable (event);
}

bool Tool_manager::on_mouse_press (const Event::Mouse_click &click)
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

bool Tool_manager::on_mouse_move (const Event::Mouse_move &move)
{
	if (applying)
	{
		if (canvas.contains (move.x, move.y))
		{
			Vector2p curr_pos = Vector2p (move.x, move.y) - canvas.pos;
			tools[curr_tool]->apply (canvas.image, prev_pos, curr_pos, properties);
			prev_pos = curr_pos;
			return true;
		}
	}

	return false;
}
//_____________________________________________________________________________

bool Tool_manager::on_button_press (Abstract_button *button)
{
	return true;
}
//_____________________________________________________________________________

bool Tool_manager::on_button_release (Abstract_button *button)
{
	if (button->hovered ())
	{
		int tool = 0;
		for (tool; tool < subwindows.size (); ++tool)
			if (subwindows[tool] == button)
				break;
		printf ("Tool %d choosed\n", tool);
		return true;
	}

	return false;
}
//=============================================================================