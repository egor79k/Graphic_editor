#ifndef _GRED_TOOLS_HPP_
#define _GRED_TOOLS_HPP_

#include <cmath>
#include <vector>
#include <memory>


struct Tool_properties;
class Abstract_tool;
class Pencil;
class Eraser;
class Filler;
class Palette;
class Canvas;
class Tool_manager;

#include "abstract_window.hpp"
#include "button.hpp"
#include "event_system.hpp"
#include "pixel_array.hpp"
#include "window.hpp"


//=============================================================================
struct Tool_properties
{
	Color color;
	uint8_t thickness = 1;
};
//=============================================================================



//=============================================================================
class Abstract_tool
{
public:
	//virtual void start_apply (Pixel_array &image, const Vector2p pos) = 0;
	virtual void apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1, const Tool_properties &prop) = 0;
	//virtual void stop_apply (Pixel_array &image, const Vector2p pos) = 0;

};
//=============================================================================



//=============================================================================
class Pencil : public Abstract_tool
{
public:
	//virtual void start_apply (Pixel_array &image, const Vector2p pos);
	virtual void apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1, const Tool_properties &prop);
	//virtual void stop_apply (Pixel_array &image, const Vector2p pos);
};
//=============================================================================



//=============================================================================
class Eraser : public Pencil
{};
//=============================================================================



//=============================================================================
class Filler : public Abstract_tool
{
public:
	void fill_area (Pixel_array &image, Vector2p pos_0, const Color &color);

	virtual void apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1, const Tool_properties &prop);
};
//=============================================================================



//=============================================================================
class Palette : public Rectangle_window, public Clickable
{
protected:
	Color frg_color;
	Color bkg_color;
	Pixel_array shade_field;
	Pixel_array color_line;

public:
	static const Color palette_bkg_color;
	static const Vector2s palette_size;
	static const Vector2s shade_field_size;
	static const Vector2s color_line_size;
	
	Palette (const Vector2p pos);

	virtual bool handle_event (const Event &event);
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
};
//=============================================================================



//=============================================================================
class Canvas : public Rectangle_window, public Hoverable
{
protected:
	Pixel_array image;
	Tool_manager *tool_manager;

public:
	Canvas (const Vector2p pos, const Vector2s size, Tool_manager *_tool_manager, const Color &color = Color::White);

	void clear ();

	virtual void on_redraw ();

	virtual bool handle_event     (const Event &event);
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);

	friend class Tool_manager;
};
//=============================================================================



//=============================================================================
class Tool_manager : public Rectangle_window, public Hoverable, public Button_reactive
{
protected:
	enum {
		PENCIL,
		ERASER,
		FILLER,
		TOOLS_NUM,
	};

	int curr_tool;
	Vector2p start_pos;
	Tool_properties properties;
	std::vector<std::unique_ptr<Abstract_tool>> tools;
	bool applying;
	
	//Canvas canvas;
	Palette *palette;
	
	static const Texture_scheme default_textures[];

public:
	Tool_manager (Palette *_palette);

	void start_apply (Canvas *canvas, Vector2p pos);
	void apply (Canvas *canvas, Vector2p pos);
	void stop_apply (Canvas *canvas, Vector2p pos);

	bool is_applying ();

	virtual bool handle_event     (const Event &event);
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);
	virtual bool on_button_press   (Abstract_button *button);
	virtual bool on_button_release (Abstract_button *button);
};
//=============================================================================

#endif // _GRED_TOOLS_HPP_