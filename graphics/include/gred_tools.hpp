#ifndef _GRED_TOOLS_HPP_
#define _GRED_TOOLS_HPP_

#include <cmath>
#include <vector>
#include <memory>

#include "abstract_window.hpp"
#include "button.hpp"
#include "event_system.hpp"
#include "pixel_array.hpp"
#include "window.hpp"


struct Tool_properties
{
	Color color;
	uint8_t thickness = 1;
};


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
class Tool_manager : public Rectangle_window, public Hoverable, public Button_reactive
{
protected:
	enum {
		PENCIL,
		ERASER,
		FILLER,
		TOOLS_NUM
	};

	int curr_tool;
	Vector2p prev_pos;
	Tool_properties properties;
	std::vector<std::unique_ptr<Abstract_tool>> tools;
	bool applying;
	
	Canvas canvas;
	
	static const Texture_scheme default_textures[];

public:
	Tool_manager ();

	virtual bool handle_event (const Event &event);
	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);
	virtual bool on_button_press   (Abstract_button *button);
	virtual bool on_button_release (Abstract_button *button);
};
//=============================================================================

#endif // _GRED_TOOLS_HPP_