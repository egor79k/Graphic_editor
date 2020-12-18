#include "../include/gred_tools.hpp"


//=============================================================================
// ::::  Pencil  ::::
//=============================================================================

void Pencil::apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1, Tool_properties &prop)
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

void Filler::apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1, Tool_properties &prop)
{
	//fill_area (image, pos_0, prop.color);
	image.fill (prop.color);
}
//=============================================================================



//=============================================================================
// ::::  Palette  ::::
//=============================================================================

void Pipette::apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1, Tool_properties &prop)
{
	prop.color = image.get_pixel (pos_1.x, pos_1.y);
}
//=============================================================================



//=============================================================================
// ::::  Palette  ::::
//=============================================================================

const Color Palette::default_bkg_color = Color (150, 150, 150);
const Vector2s Palette::shade_field_size = {256, 256};
const Vector2s Palette::color_line_size  = {256, 25};
//_____________________________________________________________________________

Palette::Palette () :
	Rectangle_window (
		Vector2p (Engine::get_size ().x - (Engine::get_size ().x * 3 >> 4) + 10, Engine::get_size ().y >> 1),
		Vector2s ((Engine::get_size ().x * 3 >> 4) - 20, (Engine::get_size ().y >> 1) - 20),
		default_bkg_color),
	frg_color (Color::Black),
	bkg_color (Color::White)
	//shade_field (shade_field_size, Color::White),
	//color_line (color_line_size, Color::White)
{
	subwindows.push_back (new Slider (
		Vector2p (pos.x + 10, 500),
		Vector2s (size.x - 20, 3),
		Color (200, 0, 0),
		&Vector2p::x,
		{Color::Black, {100, 0, 0}, {150, 0, 0}},
		{7, 15},
		this));

	subwindows.push_back (new Slider (
		Vector2p (pos.x + 10, 525),
		Vector2s (size.x - 20, 3),
		Color (0, 200, 0),
		&Vector2p::x,
		{Color::Black, {0, 100, 0}, {0, 150, 0}},
		{7, 15},
		this));

	subwindows.push_back (new Slider (
		Vector2p (pos.x + 10, 550),
		Vector2s (size.x - 20, 3),
		Color (0, 0, 200),
		&Vector2p::x,
		{Color::Black, {0, 0, 100}, {0, 0, 150}},
		{7, 15},
		this));

	indicator = new Rectangle_window (
		Vector2p (pos.x + 10, 400),
		{50, 50},
		frg_color);

	subwindows.push_back (indicator);
}
//_____________________________________________________________________________

const Color Palette::get_tool_color ()
{
	return frg_color;
}
//_____________________________________________________________________________

void Palette::set_tool_color (const Color &color)
{
	frg_color = color;
	indicator->set_color (color);
	reinterpret_cast<Slider *> (subwindows[RED])->set_percent (static_cast<float> (color.r) / 255.f);
	reinterpret_cast<Slider *> (subwindows[GREEN])->set_percent (static_cast<float> (color.g) / 255.f);
	reinterpret_cast<Slider *> (subwindows[BLUE])->set_percent (static_cast<float> (color.b) / 255.f);
}
//_____________________________________________________________________________

bool Palette::handle_event (const Event &event)
{
	for (auto win: subwindows)
		if (win->handle_event (event))
			return true;

	return false;
}
//_____________________________________________________________________________

bool Palette::on_slider_move (Slider *slider)
{
	int col_num = 0;

	for (col_num; col_num < subwindows.size (); ++col_num)
		if (subwindows[col_num] == slider)
			break;

	switch (col_num)
	{
		case RED:
			frg_color.r = 255 * slider->get_percent ();
			break;

		case GREEN:
			frg_color.g = 255 * slider->get_percent ();
			break;

		case BLUE:
			frg_color.b = 255 * slider->get_percent ();
			break;
	}

	indicator->set_color (frg_color);
	return true;
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
	{{"graphics/textures/graphic_tool_set_released.png", {{192, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_hovered.png", {{192, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_pressed.png", {{192, 0}, {64, 64}}}},
	{{"graphics/textures/graphic_tool_set_released.png", {{256, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_hovered.png", {{256, 0}, {64, 64}}}, {"graphics/textures/graphic_tool_set_pressed.png", {{256, 0}, {64, 64}}}}
};
//_____________________________________________________________________________

Tool_manager::Tool_manager (Palette *_palette) :
	Rectangle_window (Vector2p (0, 0), Vector2s (Engine::get_size ().x >> 3, Engine::get_size ().y), Image_options_panel::default_bkg_color),
	curr_tool (PENCIL),
	start_pos (),
	properties ({_palette->get_tool_color (), 5}),
	tools (TOOLS_NUM),
	applying (false),
	palette (_palette)
{
	tools[PENCIL] = std::move (std::unique_ptr<Abstract_tool> (new Pencil));
	tools[ERASER] = std::move (std::unique_ptr<Abstract_tool> (new Eraser));
	tools[FILLER] = std::move (std::unique_ptr<Abstract_tool> (new Filler));
	tools[PIPETTE] = std::move (std::unique_ptr<Abstract_tool> (new Pipette));

	subwindows.push_back (new Texture_button (default_textures[PENCIL], {20, 64}, this));
	subwindows.push_back (new Texture_button (default_textures[ERASER], {20, 128}, this));
	subwindows.push_back (new Texture_button (default_textures[FILLER], {20, 192}, this));
	subwindows.push_back (new Texture_button (default_textures[PIPETTE], {20, 256}, this));

	Slider *thickness_slider = new Slider (
		Vector2p (size.x - 20, 20),
		Vector2s (3, size.y - 40),
		Color::Black,
		&Vector2p::y,
		{{130, 130, 130}, {100, 100, 100}, Color::Black},
		{20, 10},
		this);

	subwindows.push_back (thickness_slider);

	thickness_slider->set_percent (static_cast<float> (properties.thickness) / 50.f);
}
//_____________________________________________________________________________

void Tool_manager::start_apply (Canvas *canvas, Vector2p pos)
{
	if (curr_tool == ERASER)
		properties.color = canvas->get_color ();
	else
		properties.color = palette->get_tool_color ();

	start_pos = pos;
	applying = true;
}
//_____________________________________________________________________________

void Tool_manager::apply (Canvas *canvas, Vector2p pos)
{
	tools[curr_tool]->apply (canvas->image, start_pos, pos, properties);

	if (curr_tool == PIPETTE)
		palette->set_tool_color (properties.color);

	start_pos = pos;
}
//_____________________________________________________________________________

void Tool_manager::stop_apply (Canvas *canvas, Vector2p pos)
{
	tools[curr_tool]->apply (canvas->image, start_pos, pos, properties);

	if (curr_tool == PIPETTE)
		palette->set_tool_color (properties.color);

	applying = false;
}
//_____________________________________________________________________________

bool Tool_manager::is_applying ()
{
	return applying;
}
//_____________________________________________________________________________

void Tool_manager::on_redraw ()
{
	Rectangle_window::on_redraw ();
	char str[10] = {};
	snprintf (str, 10, "%d", properties.thickness);
	Engine::draw::text ({20, 500}, str, 30, Color::Black);
}
//_____________________________________________________________________________

bool Tool_manager::handle_event (const Event &event)
{
	for (auto win: subwindows)
		if (win->handle_event (event))
			return true;

	return false;
}
//_____________________________________________________________________________

bool Tool_manager::on_button_press (Abstract_button *button)
{
	return false;
}
//_____________________________________________________________________________

bool Tool_manager::on_button_release (Abstract_button *button)
{
	if (button->hovered ())
	{
		int tool = 0;
		for (tool; tool < TOOLS_NUM; ++tool)
			if (subwindows[tool] == button)
				break;

		curr_tool = tool;
		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Tool_manager::on_slider_move (Slider *slider)
{
	properties.thickness = std::max (50 * slider->get_percent (), 1.f);
	return true;
}
//=============================================================================



//=============================================================================
// ::::  Image_options_panel  ::::
//=============================================================================

const Texture_scheme Image_options_panel::default_textures[] = {
	{{"graphics/textures/image_options_set_released.png", {{0, 0}, {64, 64}}}, {"graphics/textures/image_options_set_hovered.png", {{0, 0}, {64, 64}}}, {"graphics/textures/image_options_set_pressed.png", {{0, 0}, {64, 64}}}},
	{{"graphics/textures/image_options_set_released.png", {{64, 0}, {64, 64}}}, {"graphics/textures/image_options_set_hovered.png", {{64, 0}, {64, 64}}}, {"graphics/textures/image_options_set_pressed.png", {{64, 0}, {64, 64}}}},
	{{"graphics/textures/image_options_set_released.png", {{128, 0}, {64, 64}}}, {"graphics/textures/image_options_set_hovered.png", {{128, 0}, {64, 64}}}, {"graphics/textures/image_options_set_pressed.png", {{128, 0}, {64, 64}}}},
	{{"graphics/textures/image_options_set_released.png", {{192, 0}, {64, 64}}}, {"graphics/textures/image_options_set_hovered.png", {{192, 0}, {64, 64}}}, {"graphics/textures/image_options_set_pressed.png", {{192, 0}, {64, 64}}}},
};

const Color Image_options_panel::default_bkg_color (200, 200, 200);
//_____________________________________________________________________________

Image_options_panel::Image_options_panel (Canvas *_canvas) :
	Rectangle_window (
		Vector2p (Engine::get_size ().x - (Engine::get_size ().x * 3 >> 4), 0),
		Vector2s (Engine::get_size ().x * 3 >> 4, Engine::get_size ().y),
		default_bkg_color),
	canvas (_canvas),
	active_temp_subwindow (0)
{
	subwindows.push_back (new Texture_button (default_textures[BIN], Vector2p (pos.x + 20, 84), this));
	subwindows.push_back (new Texture_button (default_textures[NEW], Vector2p (pos.x + 20, 20), this));
	subwindows.push_back (new Texture_button (default_textures[SAVE], Vector2p (pos.x + 84, 20), this));
	subwindows.push_back (new Texture_button (default_textures[OPEN], Vector2p (pos.x + 148, 20), this));
}
//_____________________________________________________________________________

bool Image_options_panel::on_button_press   (Abstract_button *button)
{
	return false;
}
//_____________________________________________________________________________

bool Image_options_panel::on_button_release (Abstract_button *button)
{
	if (button->hovered ())
	{
		int option = -1;
		for (option; option < OPTIONS_NUM; ++option)
			if (subwindows[option] == button)
				break;

		switch (option)
		{
			case BIN:
				canvas->clear ();
				break;

			case NEW:
				canvas->clear ();
				break;

			case SAVE:
				active_temp_subwindow = add_subwindow (new Text_field ({200, 200}, {300, 30}, this, Palette::default_bkg_color, Color (255, 0, 175)));
				break;

			case OPEN:
				remove_subwindow (active_temp_subwindow);
				break;

			default:
				return false;
		}
		return true;
	}

	return false;
}
//_____________________________________________________________________________

bool Image_options_panel::on_text_enter (Text_field *text_field, const char *text)
{
	printf ("Entered: %s\n", text);
	remove_subwindow (active_temp_subwindow);
	return false;
}
//=============================================================================