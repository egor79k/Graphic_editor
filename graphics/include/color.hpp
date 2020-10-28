#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include <cstdint>


class Color
{
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	Color (uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a = 255);

	static const Color White;
	static const Color Black;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
};


bool operator== (const Color& l, const Color& r);

bool operator!= (const Color& l, const Color& r);
	
Color operator+ (const Color& l, const Color& r);
	
Color operator- (const Color& l, const Color& r);
	
Color operator* (const Color& l, const Color& r);
	
Color& operator+= (Color& l, const Color& r);
	
Color& operator-= (Color& l, const Color& r);
	
Color& operator*= (Color& l, const Color& r);


#endif