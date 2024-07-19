// line2.h
#ifndef LINE_H
#define LINE_H

#include "../Render/Renderer.h"
#include "../Constants.h"
#include "../box2d/box2d.h"
#include "../Utils/Utils.h"

class Line {
public:
    Line(b2World* world_);

    void render(Renderer* renderer) const;

    b2Body* getBody() const { return body; }
    
protected:
    b2Body* body; // Corpo físico do bloco
    Color color;// Propriedades de cor do bloco
};

#endif

