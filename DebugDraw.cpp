#include "DebugDraw.h"

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    renderer->setDrawColor(color.r * 255, color.g * 255, color.b * 255, 255);
    for (int i = 0; i < vertexCount - 1; ++i) {
        renderer->drawLine(vertices[i].x, vertices[i].y, vertices[i + 1].x, vertices[i + 1].y);
    }
    renderer->drawLine(vertices[vertexCount - 1].x, vertices[vertexCount - 1].y, vertices[0].x, vertices[0].y);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    DrawPolygon(vertices, vertexCount, color);  // Simplificação, pode ser aprimorado para desenhar formas sólidas.
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    renderer->setDrawColor(color.r * 255, color.g * 255, color.b * 255, 255);
    renderer->drawCircle(center.x, center.y, radius);  // Supondo que você tem um método para desenhar círculos.
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
    DrawCircle(center, radius, color);  // Simplificação, pode ser aprimorado para desenhar círculos sólidos.
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    renderer->setDrawColor(color.r * 255, color.g * 255, color.b * 255, 255);
    renderer->drawLine(p1.x, p1.y, p2.x, p2.y);
}

void DebugDraw::DrawTransform(const b2Transform& xf) {
    b2Vec2 p1 = xf.p, p2;
    const float k_axisScale = 0.4f;
    p2 = p1 + k_axisScale * xf.q.GetXAxis();
    renderer->setDrawColor(255, 0, 0, 255);
    renderer->drawLine(p1.x, p1.y, p2.x, p2.y);
    p2 = p1 + k_axisScale * xf.q.GetYAxis();
    renderer->setDrawColor(0, 255, 0, 255);
    renderer->drawLine(p1.x, p1.y, p2.x, p2.y);
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {
    renderer->setDrawColor(color.r * 255, color.g * 255, color.b * 255, 255);
    renderer->drawPoint(p.x, p.y);
}
