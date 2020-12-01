#ifndef _GRED_TOOLS_HPP_
#define _GRED_TOOLS_HPP_

#include "window.hpp"
#include "pixel_array.hpp"
#include <cmath>
#include <vector>
#include <memory>

//=============================================================================
class Abstract_tool
{
public:
	//virtual void start_apply (Pixel_array &image, const Vector2p pos) = 0;
	virtual void apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1) = 0;
	//virtual void stop_apply (Pixel_array &image, const Vector2p pos) = 0;

};
//=============================================================================



//=============================================================================
class Pencil : public Abstract_tool
{
public:
	//virtual void start_apply (Pixel_array &image, const Vector2p pos);
	virtual void apply (Pixel_array &image, Vector2p pos_0, Vector2p pos_1);
	//virtual void stop_apply (Pixel_array &image, const Vector2p pos);
};
//=============================================================================



//=============================================================================
class Tool_manager : public Rectangle_window
{
protected:
	enum {
		PENCIL,
		ERASER,
		TOOLS_NUM
	};

	Vector2p prev_pos;
	int curr_tool;
	std::vector<std::unique_ptr<Abstract_tool>> tools;
	Canvas canvas;
	bool applying;

public:
	Tool_manager ();

	virtual bool on_mouse_press   (const Event::Mouse_click &click);
	virtual bool on_mouse_release (const Event::Mouse_click &click);
	virtual bool on_mouse_move    (const Event::Mouse_move &move);
};
//=============================================================================

#endif // _GRED_TOOLS_HPP_