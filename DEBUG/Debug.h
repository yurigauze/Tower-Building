#ifndef DEBUG_H
#define DEBUG_H

#include "box2d/box2d.h"

#ifdef V212
class DebugDraw : public b2DebugDraw
#else
class DebugDraw : public b2Draw
#endif
{
public:

	void Setup(int &draw, int &text, int pixels_per_meter_rate);
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	void DrawTransform(const b2Transform& xf);
	void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
	void DrawString(int x, int y, const char* string, ...);
	void DrawAABB(b2AABB* aabb, const b2Color& color);

private:

	// DragonFireSDK needs the draw and text handles to update screen
	int draw_handle;
	int text_handle;

	// since Box2D uses meters instead of pixels a conversion rate is used to render graphics
	int pixels_per_meter;

	inline int Round (float x)
	{
		return (int)(x + 0.5);
	};

};

#endif