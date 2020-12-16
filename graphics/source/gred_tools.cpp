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
// ::::  Filler  ::::
//=============================================================================

void Filler::fill_area (Pixel_array &image, Vector2p pos_0, const Color &color)
{
/*	const Color old_color = image.get_pixel (pos_0.x, pos_0.y);
	const Vector2s size = image.get_size ();

	if ((pos_0.y - 1) >= 0 && image.get_pixel (pos_0.x, pos_0.y - 1) == old_color)
		fill_area (image, {pos_0.x, pos_0.y - 1}, color);

	if ((pos_0.y + 1) < size.y && image.get_pixel (pos_0.x, pos_0.y + 1) == old_color)
		fill_area (image, {pos_0.x, pos_0.y + 1}, color);

	if ((pos_0.x - 1) >= 0 && image.get_pixel (pos_0.x - 1, pos_0.y) == old_color)
		fill_area (image, {pos_0.x - 1, pos_0.y}, color);

	if ((pos_0.x + 1) < size.x && image.get_pixel (pos_0.x + 1, pos_0.y) == old_color)
		fill_area (image, {pos_0.x + 1, pos_0.y}, color);

	image.set_pixel (pos_0.x, pos_0.y, color);*/
}

void Filler::apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1, const Tool_properties &prop)
{
	//fill_area (image, pos_0, prop.color);
}
//=============================================================================



//=============================================================================
// ::::  Palette  ::::
//=============================================================================

const Color Palette::palette_bkg_color = Color (220, 220, 220);
const Vector2s Palette::palette_size = {300, 400};
const Vector2s Palette::shade_field_size = {256, 256};
const Vector2s Palette::color_line_size  = {256, 25};
//_____________________________________________________________________________

Palette::Palette (const Vector2p pos) :
	Rectangle_window (pos, palette_size, palette_bkg_color),
	shade_field (shade_field_size, Color::White),
	color_line (color_line_size, Color::White)
{
	//for (int x = 0; x < color_line_size.x; ++x)
	//	for (int y = 0; y < color_line_size.y; ++y)
	//		color_line.set_pixel (x, y, Color (255, x))
}

bool Palette::handle_event (const Event &event)
{
	return false;
}
bool Palette::on_mouse_press   (const Event::Mouse_click &click)
{
	return false;
}
bool Palette::on_mouse_release (const Event::Mouse_click &click)
{
	return false;
}
//=============================================================================



//=============================================================================
// ::::  Canvas  ::::
//=============================================================================

Canvas::Canvas (const Vector2p pos, const Vector2s size, Tool_manager *_tool_manager, const Color &color) :
	Rectangle_window (pos, size, color),
	image (size, color),
	tool_manager (_tool_manager)
{}
//_____________________________________________________________________________

void Canvas::clear ()
{
	image.fill (color);
}
//_____________________________________________________________________________

void Canvas::on_redraw ()
{
	Engine::draw::image (pos, image);
}
//_____________________________________________________________________________

bool Canvas::handle_event (const Event &event)
{
	for (auto win: subwindows)
		if (win->handle_event (event))
			return true;

	return handle_hoverable (event);
}
//_____________________________________________________________________________

bool Canvas::on_mouse_press   (const Event::Mouse_click &click)
{
	if (contains (click.x, click.y))
	{
		tool_manager->start_apply (this, Vector2p (click.x, click.y) - pos);
		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Canvas::on_mouse_release (const Event::Mouse_click &click)
{
	if (tool_manager->is_applying ())
	{
		tool_manager->stop_apply (this, Vector2p (click.x, click.y) - pos);
		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Canvas::on_mouse_move    (const Event::Mouse_move &move)
{
	if (tool_manager->is_applying () && contains (move.x, move.y))
	{
		tool_manager->apply (this, Vector2p (move.x, move.y) - pos);
		return true;
	}

	return false;
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

Tool_manager::Tool_manager (Palette *_palette) :
	Rectangle_window (Vector2p (0, 0), Vector2s (Engine::get_size ().x >> 3, Engine::get_size ().y), Palette::palette_bkg_color),
	curr_tool (PENCIL),
	start_pos (),
	properties ({Color::Blue, 5}),
	tools (TOOLS_NUM),
	applying (false),
	//canvas (Vector2p (Engine::get_size ().x / 8 + 30, 20), Vector2s (Engine::get_size ().x * 5 >> 3, Engine::get_size ().y - 40)),
	palette (_palette)
{
	//Event_system::attach_redraw (&canvas);

	tools[PENCIL] = std::move (std::unique_ptr<Abstract_tool> (new Pencil));
	tools[ERASER] = std::move (std::unique_ptr<Abstract_tool> (new Eraser));
	tools[FILLER] = std::move (std::unique_ptr<Abstract_tool> (new Filler));

	subwindows.push_back (new Texture_button (default_textures[PENCIL], {20, 64}, this));
	subwindows.push_back (new Texture_button (default_textures[ERASER], {20, 128}, this));
	subwindows.push_back (new Texture_button (default_textures[FILLER], {20, 192}, this));
}
//_____________________________________________________________________________

void Tool_manager::start_apply (Canvas *canvas, Vector2p pos)
{
	start_pos = pos;
	applying = true;
}
//_____________________________________________________________________________

void Tool_manager::apply (Canvas *canvas, Vector2p pos)
{
	if (curr_tool != ERASER)
		tools[curr_tool]->apply (canvas->image, start_pos, pos, properties);
	else
		tools[curr_tool]->apply (canvas->image, start_pos, pos, {canvas->get_color (), properties.thickness});

	start_pos = pos;
}
//_____________________________________________________________________________

void Tool_manager::stop_apply (Canvas *canvas, Vector2p pos)
{
	if (curr_tool != ERASER)
		tools[curr_tool]->apply (canvas->image, start_pos, pos, properties);
	else
		tools[curr_tool]->apply (canvas->image, start_pos, pos, {canvas->get_color (), properties.thickness});

	applying = false;
}
//_____________________________________________________________________________

bool Tool_manager::is_applying ()
{
	return applying;
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
/*	if (canvas.contains (click.x, click.y))
	{
		start_pos = Vector2p (click.x, click.y) - canvas.pos;
		applying = true;
		return true;
	}
*/
	return false;
}
//_____________________________________________________________________________

bool Tool_manager::on_mouse_release (const Event::Mouse_click &click)
{
/*	if (applying)
	{
		Vector2p curr_pos = Vector2p (click.x, click.y) - canvas.pos;
		if (curr_tool != ERASER)
			tools[curr_tool]->apply (canvas.image, start_pos, curr_pos, properties);
		else
			tools[curr_tool]->apply (canvas.image, start_pos, curr_pos, {canvas.get_color (), properties.thickness});

		applying = false;
		return true;
	}
*/
	return false;
}
//_____________________________________________________________________________

bool Tool_manager::on_mouse_move (const Event::Mouse_move &move)
{
/*	if (applying)
	{
		if (canvas.contains (move.x, move.y))
		{
			Vector2p curr_pos = Vector2p (move.x, move.y) - canvas.pos;
			if (curr_tool != ERASER)
				tools[curr_tool]->apply (canvas.image, start_pos, curr_pos, properties);
			else
				tools[curr_tool]->apply (canvas.image, start_pos, curr_pos, {canvas.get_color (), properties.thickness});
			start_pos = curr_pos;
			return true;
		}
	}
*/
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
		curr_tool = tool;
		return true;
	}

	return false;
}
//=============================================================================