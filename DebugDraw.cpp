#include "DebugDraw.h"
#include "Constants.h"


void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    renderer->setDrawColor(color.r * 255, color.g * 255, color.b * 255, 255);
    for (int i = 0; i < vertexCount - 1; ++i) {
        renderer->drawLine(vertices[i].x * SCALE, vertices[i].y * SCALE,
                           vertices[i + 1].x * SCALE, vertices[i + 1].y * SCALE);
    }
    renderer->drawLine(vertices[vertexCount - 1].x * SCALE, vertices[vertexCount - 1].y * SCALE,
                       vertices[0].x * SCALE, vertices[0].y * SCALE);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    DrawPolygon(vertices, vertexCount, color);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    renderer->setDrawColor(color.r * 255, color.g * 255, color.b * 255, 255);
    renderer->drawCircle(center.x * SCALE, center.y * SCALE, radius * SCALE);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
    DrawCircle(center, radius, color);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    renderer->setDrawColor(color.r * 255, color.g * 255, color.b * 255, 255);
    renderer->drawLine(p1.x * SCALE, p1.y * SCALE, p2.x * SCALE, p2.y * SCALE);
}

void DebugDraw::DrawTransform(const b2Transform& xf) {
    b2Vec2 p1 = xf.p, p2;
    const float k_axisScale = 0.4f;
    p2 = p1 + k_axisScale * xf.q.GetXAxis();
    renderer->setDrawColor(255, 0, 0, 255);
    renderer->drawLine(p1.x * SCALE, p1.y * SCALE, p2.x * SCALE, p2.y * SCALE);
    p2 = p1 + k_axisScale * xf.q.GetYAxis();
    renderer->setDrawColor(0, 255, 0, 255);
    renderer->drawLine(p1.x * SCALE, p1.y * SCALE, p2.x * SCALE, p2.y * SCALE);
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {
    renderer->setDrawColor(color.r * 255, color.g * 255, color.b * 255, 255);
    renderer->drawPoint(p.x * SCALE, p.y * SCALE);
}
