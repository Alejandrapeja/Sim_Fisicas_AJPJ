
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;

class Rectangle {
public:
    Rectangle(b2World &world, float x, float y) {
        b2BodyDef pisobodydef;
        pisobodydef.position.Set(x / SCALE, y / SCALE);
        body  = world.CreateBody(&pisobodydef);

        b2PolygonShape groundBox;
        groundBox.SetAsBox((10.f / 2) / SCALE, (50.f / 2) / SCALE);

        body->CreateFixture(&groundBox,0.0f );

        box.setSize(sf::Vector2f(10.f, 50.f));
        box.setFillColor(sf::Color::Green);
        box.setOrigin(5.f, 5.f);
    }

    void update() {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void Color(sf::Color color){
        box.setFillColor(color);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(box);
    }

    void resetPosition() {
        body->SetTransform(b2Vec2(0, 0), body->GetAngle());
    }

    void stop() {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }

    b2Body *getBody() {
        return body;
    }

private:
    sf::RectangleShape box;
    b2Body *body;
};


class Cube {
public:
    Cube(b2World &world, float x, float y) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        bodydef.type = b2_dynamicBody;
        body  = world.CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((10.f / 2) / SCALE, (10.f / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = 1.0f;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(10.f, 10.f));
        box.setFillColor(sf::Color::Red);
        box.setOrigin(5.f, 5.f);
    }

    void update() {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void Color(sf::Color color){
        box.setFillColor(color);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(box);
    }

    void resetPosition() {
        body->SetTransform(b2Vec2(0, 0), body->GetAngle());
    }

    void stop() {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }

    b2Body *getBody() {
        return body;
    }

private:
    sf::RectangleShape box;
    b2Body *body;
};

int main5() {
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");

    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    Cube cube(world, 400, 300);
    Rectangle cube2(world, 500, 300);
    Cube cube3(world, 400, 400);

    //Creacion del joint de Rotacion
    b2RevoluteJointDef jointRev;
    jointRev.Initialize(cube2.getBody(),cube.getBody(),cube2.getBody()->GetWorldCenter());
    world.CreateJoint(&jointRev);


    //Creacion del joint prismatico
    b2PrismaticJointDef jointPris;
    jointPris.Initialize(cube3.getBody(),cube.getBody(),cube3.getBody()->GetWorldCenter(),b2Vec2(0.0f,1.0f));
    world.CreateJoint(&jointPris);

    //Creacion del joint Engrane

    b2GearJointDef jointGea;
    jointGea.bodyA=cube.getBody();
    jointGea.bodyB=cube2.getBody();
    //jointGea.joint1= jointRev; No detecta los joints, no funciona
    world.CreateJoint(&jointGea);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                cube.getBody()->ApplyForceToCenter(b2Vec2(-0.1f, 0.0f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                cube.getBody()->ApplyForceToCenter(b2Vec2(0.0f, 0.1f), true);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                cube.resetPosition();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                cube.stop();
            }

            // The Z key event to close the window
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                window.close();
                return 0; // return from the main function, effectively ending the program
            }
        }

        world.Step(1 / 60.f, 8, 3);
        cube.update();
        cube2.update();

        window.clear();
        cube.draw(window);
        cube2.draw(window);
        window.display();
    }
    return 0;
}