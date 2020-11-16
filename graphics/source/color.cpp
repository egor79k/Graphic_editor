#include "../include/color.hpp"


Color::Color () :
	Color (White)
{}


Color::Color (uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a) :
	r (_r),
	g (_g),
	b (_b),
	a (_a)
{}


const Color Color::White = Color (255, 255, 255);
const Color Color::Black = Color (0,   0,   0  );
const Color Color::Red   = Color (255, 0,   0  );
const Color Color::Green = Color (0  , 255, 0  );
const Color Color::Blue  = Color (0  , 0  , 255);


bool operator== (const Color& l, const Color& r)
{
	return (l.r == r.r && l.g == r.g && l.b == r.b && l.a == r.a);
}


bool operator!= (const Color& l, const Color& r)
{
	return (l.r != r.r || l.g != r.g || l.b != r.b || l.a != r.a);
}
	

Color operator+ (const Color& l, const Color& r)
{
	return Color (
		((l.r + r.r) > 255 ? 255 : (l.r + r.r)),
		((l.g + r.g) > 255 ? 255 : (l.g + r.g)),
		((l.b + r.b) > 255 ? 255 : (l.b + r.b)),
		((l.a + r.a) > 255 ? 255 : (l.a + r.a))
	);
}
	
Color operator- (const Color& l, const Color& r)
{
	return Color (
		((l.r - r.r) < 0 ? 0 : (l.r - r.r)),
		((l.g - r.g) < 0 ? 0 : (l.g - r.g)),
		((l.b - r.b) < 0 ? 0 : (l.b - r.b)),
		((l.a - r.a) < 0 ? 0 : (l.a - r.a))
	);
}
	
Color operator* (const Color& l, const Color& r)
{
	return Color (
		(l.r * r.r) / 255,
		(l.g * r.g) / 255,
		(l.b * r.b) / 255,
		(l.a * r.a) / 255
	);
}
	
Color& operator+= (Color& l, const Color& r)
{
	l = operator+ (l, r);
	return l;
}
	
Color& operator-= (Color& l, const Color& r)
{
	l = operator- (l, r);
	return l;
}
	
Color& operator*= (Color& l, const Color& r)
{
	l = operator* (l, r);
	return l;
}