#include <iostream>
#include <Box2d/Box2d.h>

int main(){
    //Creacion de la Luna con gravedad
    b2Vec2 gravedad(0.0f,-6.62f);
    b2World world(gravedad);
    //Caracteristicas del cuerpo
    b2BodyDef pisoBodyDef;
    pisoBodyDef.position.Set(0.0f,-10.0f);
    //Creacion en la Luna
    b2Body* pisoBody = world.CreateBody(&pisoBodyDef);

    //crear su forma
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f,1.0f);

    pisoBody ->CreateFixture(&groundBox, 0.0f);

    //Creacion del cubo
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f,20.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f,1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    body ->CreateFixture(&fixtureDef);

    //Ajustes para que el tiempo corra
    float timeStep = 1.0f/60.0f;

    int32 velocityIterations = 6;
    int32 positionIteration = 2;

    for (int32 i = 0; i<60; ++i){
        world.Step(timeStep,velocityIterations,positionIteration);
        b2Vec2 position = body ->GetPosition();
        float angle = body ->GetAngle();
        printf("%4.2f %4.2f %4.2f\n",position.x,position.y,angle);
    }
}
