#include <Box2D/Box2D.h>
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//https://box2d.org/documentation/ - para ver como hacer esfera
//Bala de cañon (densidad libre, tamano real) disparada en la luna a velocidad 900km/h
//A un angulo de 60°
int main() {
    // Define gravedad de la luna
    b2Vec2 gravity(0.0f, -1.62f);

    // Construct a world object, which will hold and simulate the rigid bodies
    b2World world(gravity);

    // Create a dynamic body for the bullet
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
    b2Body* body = world.CreateBody(&bodyDef);

    // Define another box shape for the bullet
    b2PolygonShape dynamicBox; //b2CircleShape?? no void to set
    dynamicBox.SetAsBox(0.11f, 0.11f);

    // Define the dynamic body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 7874.0f; //Densidad del hierro
    fixtureDef.friction = 0.1f;

    // Add the shape to the body
    body->CreateFixture(&fixtureDef);

    // Set the initial velocity of the bullet
    float angle = 60.0f; // Angle in degrees
    float speed = 250.0f; // Speed in m/s =900km/h
    float vx = speed * std::cos(angle * M_PI / 180.0f);
    float vy = speed * std::sin(angle * M_PI / 180.0f);

    body->SetLinearVelocity(b2Vec2(vx, vy));

    // Simulate the world
    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    for (int i = 0; i < 60; ++i)
    {
        world.Step(timeStep, velocityIterations, positionIterations);
        std::cout << body->GetPosition().x << " " << body->GetPosition().y << std::endl;

    }

    // Remember to clean up
    world.DestroyBody(body);

    return 0;
}