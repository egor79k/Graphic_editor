#ifndef _VECTOR2_HPP_
#define _VECTOR2_HPP_


template<typename T>
class Vector2
{
public:
	T x;
	T y;

	Vector2 ();

	Vector2 (T _x, T _y);

	//Vector2 (const Vector2 &) = default;
};


template<typename T>
Vector2<T>::Vector2 (T _x, T _y) :
	x (_x),
	y (_y)
{}

template<typename T>
Vector2<T>::Vector2 () :
	x (0),
	y (0)
{}


template<typename T>
Vector2<T> operator- (const Vector2<T>& r)
{
	return Vector2<T> (-r.x, -r.y);
}

template<typename T>
Vector2<T>& operator+= (Vector2<T>& l, const Vector2<T>& r)
{
	l.x += r.x;
	l.y += l.y;
	return l;
}

template<typename T>
Vector2<T>& operator-= (Vector2<T>& l, const Vector2<T>& r)
{
	l.x -= r.x;
	l.y -= l.y;
	return l;
}

template<typename T>
Vector2<T> operator+ (const Vector2<T>& l, const Vector2<T>& r)
{
	return Vector2<T> (l.x + r.x, l.y + r.y);
}

template<typename T>
Vector2<T> operator- (const Vector2<T>& l, const Vector2<T>& r)
{
	return Vector2<T> (l.x - r.x, l.y - r.y);
}

template<typename T>
Vector2<T> operator* (const Vector2<T>& l, T r)
{
	return Vector2<T> (l.x * r, l.y * r);
}

template<typename T>
Vector2<T> operator* (T l, const Vector2<T>& r)
{
	return Vector2<T> (l * r.x, l * r.y);
}

template<typename T>
Vector2<T>& operator*= (Vector2<T>& l, T r)
{
	l.x *= r;
	l.y *= r;
	return l;
}

template<typename T>
Vector2<T> operator/ (const Vector2<T>& l, T r)
{
	return Vector2<T> (l.x / r, l.y / r);
}

template<typename T>
Vector2<T>& operator/= (Vector2<T>& l, T r)
{
	l.x /= r;
	l.y /= r;
	return l;
}

template<typename T>
bool operator== (const Vector2<T>& l, const Vector2<T>& r)
{
	return (l.x == r.x && l.y == r.y);
}

template<typename T>
bool operator!= (const Vector2<T>& l, const Vector2<T>& r)
{
	return (l.x != r.x || l.y != r.y);
}


#endif