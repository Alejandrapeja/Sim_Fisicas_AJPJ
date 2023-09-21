#include <iostream>
#include <Box2d/Box2d.h>

int main(){
    //Creacion de Jupiter con gravedad
    b2Vec2 gravedad(0.0f,-24.79f); //Se ajusta la gravedad
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
    bodyDef.position.Set(0.0f,15.0f); //Se cambia la altura a 15m
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f,1.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 15600.0f; //Se ajusta la densidad pues esta hecho de carburo de tungsteno
    //15.63 g/cm^3 o 15630.0 kg/m^3
    fixtureDef.friction = 0.9f;
    //Se modifica friccion pero por ser dificil de calcular se usa un valor arbitriario

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
