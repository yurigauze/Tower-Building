// line.h
#ifndef LINE_H
#define LINE_H

#include "../Render/Renderer.h"
#include "../Constants.h"
#include "../box2d/box2d.h"
#include "../Utils/Utils.h"


class Line {
public:
    Line(b2World* world_, float x, float y);

    void render(Renderer* renderer) const;
    void attachToHook(b2Body* hookBody);
    void setMotorSpeed(float speed);  // Método para configurar a velocidade do motor na junta com o gancho


    b2Body* getBody() const { return body; }
    b2Body* getTipBody() const { return tipBody; }
    b2RevoluteJoint* getJointWithHook() const { return jointWithHook; }  // Getter para acessar a junta com o gancho
    
protected:
    b2Body* tipBody;
    b2RevoluteJoint* jointWithHook;
    b2Body* body; // Corpo físico do bloco
    Color color;// Propriedades de cor do bloco
};

#endif

