#include "../include/pixel_array.hpp"


//=============================================================================
// ::::  Abstract_window  ::::
//=============================================================================

Pixel_array::Pixel_array (const Vector2s _size, const Color &color) :
	pixels (new uint8_t[_size.x * _size.y * sizeof (Color)]),
	size (_size)
{
	Color *img = reinterpret_cast<Color *> (pixels);
	for (int i = 0; i < size.x * size.y; ++i)
		img[i] = color;

}
//_____________________________________________________________________________

Pixel_array::Pixel_array (const uint16_t width, const uint16_t height, const Color &color) :
	Pixel_array ({width, height}, color)
{}
//_____________________________________________________________________________

Pixel_array::~Pixel_array ()
{
	delete[] pixels;
}
//_____________________________________________________________________________

void Pixel_array::set_pixel (const Vector2s point, const Color &color)
{
	*(reinterpret_cast<Color *> (pixels + (point.y * size.x + point.x) * sizeof (Color))) = color;
}
//_____________________________________________________________________________

void Pixel_array::set_pixel (const uint16_t x, const uint16_t y, const Color &color)
{
	*(reinterpret_cast<Color *> (pixels + (y * size.x + x) * sizeof (Color))) = color;
}
//_____________________________________________________________________________

const Color &Pixel_array::get_pixel (const Vector2s point) const
{
	return *(reinterpret_cast<Color *> (pixels + (point.y * size.x + point.x) * sizeof (Color)));
}
//_____________________________________________________________________________

const Color &Pixel_array::get_pixel (const uint16_t x, const uint16_t y) const
{
	return *(reinterpret_cast<Color *> (pixels + (y * size.x + x) * sizeof (Color)));
}
//_____________________________________________________________________________

void Pixel_array::fill (const Color &color)
{
	Color *img = reinterpret_cast<Color *> (pixels);
	for (int i = 0; i < size.x * size.y; ++i)
		img[i] = color;
}
//_____________________________________________________________________________

void Pixel_array::copy_from (const uint16_t width, const uint16_t height, const uint8_t *image)
{
	delete[] pixels;

	pixels = new uint8_t[width * height * sizeof (Color)];
	size = {width, height};

	Color *img_to = reinterpret_cast<Color *> (pixels);
	const Color *img_from = reinterpret_cast<const Color *> (image);

	for (int i = 0; i < width * height; ++i)
		img_to[i] = img_from[i];
}
//_____________________________________________________________________________

void Pixel_array::resize (const uint16_t width, const uint16_t height, const Color &color)
{
	if (width != size.x && height != size.y)
	{
		delete[] pixels;

		size = {width, height};

		pixels = new uint8_t[width * height * sizeof (Color)];
	}

	fill (color);
}
//_____________________________________________________________________________

const Vector2s Pixel_array::get_size () const
{
	return size;
}
//_____________________________________________________________________________

const uint8_t *Pixel_array::get_origin () const
{
	return pixels;
}
//=============================================================================