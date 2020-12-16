#ifndef _PIXEL_ARRAY_HPP_
#define _PIXEL_ARRAY_HPP_

#include <vector>
#include "vector2.hpp"
#include "color.hpp"

//=============================================================================
class Pixel_array
{
private:
	uint8_t *pixels;
	Vector2s size;

public:
	Pixel_array (const Vector2s _size, const Color &color);
	Pixel_array (const uint16_t width, const uint16_t height, const Color &color);
	~Pixel_array ();

	void set_pixel (const Vector2s point, const Color &color);
	void set_pixel (const uint16_t x, const uint16_t y, const Color &color);

	const Color &get_pixel (const Vector2s point) const;
	const Color &get_pixel (const uint16_t x, const uint16_t y) const;

	void fill (const Color &color);

	const Vector2s get_size () const;

	const uint8_t *get_origin () const;
};
//=============================================================================

#endif // _PIXEL_ARRAY_HPP_