#ifndef _GRED_TOOLS_HPP_
#define _GRED_TOOLS_HPP_

//=============================================================================
class Abstract_tool
{
public:
	virtual void start_applying (const Pixel_array &image, const Vector2p pos) = 0;
	virtual void stop_applying (const Pixel_array &image, const Vector2p pos) = 0;
};
//=============================================================================



//=============================================================================
class Pencil : public Abstract_tool
{
public:
	virtual void start_applying (const Pixel_array &image, const Vector2p pos);
	virtual void stop_applying (const Pixel_array &image, const Vector2p pos);
};
//=============================================================================

#endif // _GRED_TOOLS_HPP_