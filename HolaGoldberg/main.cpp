#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

constexpr float SCALE = 30.0f;


class Circle {
public:
    Circle(b2World &world, float x, float y, bool Dynamic, float h,float w,float r,float density) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        if(Dynamic){
            bodydef.type = b2_dynamicBody;
        }

        body = world.CreateBody( &bodydef);
        origin = b2Vec2(x/SCALE, y/SCALE);
        b2CircleShape circle;
        circle.m_p.Set((h/2)/SCALE, (w/2)/SCALE);
        circle.m_radius = r/SCALE;

        b2FixtureDef fixturedef;
        fixturedef.shape = &circle;
        fixturedef.density = density;
        body->CreateFixture(&fixturedef);

        cir.setRadius(r);
        cir.setFillColor(sf::Color::Cyan);
        cir.setOrigin(h/2, w/2);
    }

    void update() {
        cir.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        cir.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(cir);
    }

    void resetPosition() {
        body->SetTransform(origin, body->GetAngle());
        body->SetLinearVelocity(b2Vec2(0,0));
    }

    void stop() {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }

    void color(sf::Color color){
        cir.setFillColor(color);
    }

    b2Body *getBody() {
        return body;
    }

private:
    sf::CircleShape cir;
    b2Body *body;
    b2Vec2 origin;
};

class Cube {
public:
    Cube(b2World &world, float x, float y, bool Dynamic, float h,float w,float ang, float density) {
        b2BodyDef bodydef;
        bodydef.position.Set(x / SCALE, y / SCALE);
        if(Dynamic) {
            bodydef.type = b2_dynamicBody;
        }
        bodydef.angle = ang * b2_pi;
        OrgAngle = ang * b2_pi;
        body = world.CreateBody(&bodydef);
        origin = b2Vec2(x/SCALE, y/SCALE);
        b2PolygonShape shape;
        shape.SetAsBox((h / 2) / SCALE, (w / 2) / SCALE);

        b2FixtureDef fixturedef;
        fixturedef.shape = &shape;
        fixturedef.density = density;
        body->CreateFixture(&fixturedef);

        box.setSize(sf::Vector2f(h, w));
        box.setFillColor(sf::Color::Red);
        box.setOrigin(h/2, w/2);
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void update() {
        box.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
        box.setRotation(body->GetAngle() * 180 / b2_pi);
    }

    void draw(sf::RenderWindow &win) const {
        win.draw(box);
    }

    void resetPosition() {
        body->SetTransform(origin, OrgAngle);
        body->SetLinearVelocity(b2Vec2(0,0));
    }

    void stop() {
        body->SetLinearVelocity(b2Vec2(0, 0));
    }

    void color(sf::Color color){
        box.setFillColor(color);
    }

    b2Body *getBody() {
        return body;
    }

private:
    sf::RectangleShape box;
    b2Body *body;
    b2Vec2 origin;
    float OrgAngle;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");

    b2Vec2 gravity(0.0f, 0.01f);
    b2World world(gravity);

    //Formas o Cuerpos
        //Controlados
    Circle circ(world,75,75,true,10,10,10,1);
    Cube cube(world, 300, 100,true,10,10,0,0);
    Circle circ2(world,195,270,true,10,10,10,1);
    Circle circ3(world,465,400,true,10,10,10,5);
    Circle circ4(world,440,620,true,10,10,10,0.1);
    circ4.color(sf::Color::Yellow);
        //Escenario
    Cube scn1(world, 10, 300,false,300,10,0.1,0);
    scn1.color(sf::Color::White);
    Cube scn2(world, 220, 420,false,100,10,0,0);
    scn2.color(sf::Color::White);
    Cube scn3(world, 120, 440,false,100,10,-0.05,0);
    scn3.color(sf::Color::White);
    Cube scn4(world, 460, 420,false,40,10,0,0);
    scn4.color(sf::Color::White);
    Cube scn5(world, 285, 410,false ,10,30,0,0);
    scn5.color(sf::Color::White);
    Cube scn6(world, 220, 280,false ,50,10,0,0);
    scn6.color(sf::Color::White);
    Cube scn7(world, 500, 200,false ,10,200,0,0);
    scn7.color(sf::Color::White);
    Cube scn8(world, 10, 450,false ,10,150,0,0);
    scn8.color(sf::Color::White);
    Cube scn9(world, 10, 500,false ,300,10,0.05,0);
    scn9.color(sf::Color::White);
    Cube scn11(world, 700, 500,false ,300,10,0,0);
    scn11.color(sf::Color::White);

        //ParaJoints
            //Revolute
    Cube cube1(world, 25,100, true,50,10,0,0);
    Cube cube2(world, 85,100, true,50,10,0,1);
    cube1.color(sf::Color::White);
    cube2.color(sf::Color::Green);
            //Revolute2
    Cube cube3(world, 75,200, true,50,10,0,1);
    Cube cube4(world, 135,200, true,50,10,0,0);
    cube4.color(sf::Color::White);
    cube3.color(sf::Color::Magenta);
            //Distance
    Cube dis1(world, 250, 400,true,10,40,0,10);
    Cube dis2(world, 450, 400,true,10,40,0,5);
            //Pulley
    Cube plat1(world,520,440, true,50,10,0,0.1);
    Cube plat2(world,220,750, true,50,10,0,0.1);
    Cube point1(world,520,100, false,10,10,0,0);
    Cube point2(world,220,500, false,10,10,0,0);
    point1.color(sf::Color::Blue);
    point2.color(sf::Color::Blue);
    plat1.color(sf::Color::Blue);
    plat2.color(sf::Color::Blue);
            //Prismatic
    Cube scn10(world, 550, 500,true ,10,300,0,0);
    scn10.color(sf::Color::White);
    Cube plat3(world,520,430, true,50,10,0,0.1);
    Cube plat4(world,220,740, true,50,10,0,0.1);
            //Gear
    Cube gear(world,350,630,true,200,10,0,1);
    gear.color(sf::Color::Magenta);
            //Gear 2
    Cube hold1(world,100,800,true,800,10,0,1);
    hold1.color(sf::Color::Magenta);
            //Gear 3
    Cube push(world,370,370,true,100,10,0,0.1);
    push.color(sf::Color::Green);

    //JOINTS
        //Revolucion
    b2RevoluteJointDef jointRev;
    jointRev.Initialize(cube2.getBody(),cube1.getBody(),cube1.getBody()->GetWorldCenter());
    b2RevoluteJoint* jointr3 = (b2RevoluteJoint*)world.CreateJoint(&jointRev);

    b2RevoluteJointDef jointRev2;
    jointRev2.Initialize(cube4.getBody(),cube3.getBody(),cube4.getBody()->GetWorldCenter());
    b2RevoluteJoint* jointr2 = (b2RevoluteJoint*)world.CreateJoint(&jointRev2);
        //Distance
    b2DistanceJointDef jointDis;
    jointDis.Initialize(dis1.getBody(),dis2.getBody(),dis1.getBody()->GetWorldCenter(),dis2.getBody()->GetWorldCenter());
    world.CreateJoint(&jointDis);
        //Pulley
    b2PulleyJointDef jointPul;
    jointPul.Initialize(plat1.getBody(),plat2.getBody(),point1.getBody()->GetWorldCenter(),point2.getBody()->GetWorldCenter(),plat1.getBody()->GetWorldCenter(),plat2.getBody()->GetWorldCenter(), 1);
    world.CreateJoint(&jointPul);
        //Prismaticas
    b2PrismaticJointDef jointPris;
    jointPris.Initialize(scn10.getBody(),plat3.getBody(),scn10.getBody()->GetWorldCenter(),b2Vec2(0,1));
    jointPris.enableLimit = true;
    jointPris.lowerTranslation = -1.0f;
    jointPris.upperTranslation = 8.0f;
    world.CreateJoint(&jointPris);
    b2PrismaticJointDef jointPris2;
    jointPris2.Initialize(scn10.getBody(),plat4.getBody(),scn10.getBody()->GetWorldCenter(),b2Vec2(0,1));
    jointPris2.enableLimit = true;
    jointPris2.lowerTranslation = -6.0f;
    jointPris2.upperTranslation = 1.0f;
    world.CreateJoint(&jointPris2);

    b2RevoluteJointDef jointRev3;
    jointRev3.Initialize(gear.getBody(),scn10.getBody(),gear.getBody()->GetWorldCenter());
    b2RevoluteJoint* jointr = (b2RevoluteJoint*)world.CreateJoint(&jointRev3);

    b2GearJointDef jointGea;
    jointGea.bodyA = jointr2->GetBodyB(); //Dinamico Prismatico 1
    jointGea.bodyB = jointr->GetBodyA(); //Dinamico revolute p/gear
    jointGea.joint1 = jointr2;
    jointGea.joint2 = jointr;
    jointGea.ratio = 1.0f;
    world.CreateJoint(&jointGea);

    b2PrismaticJointDef jointPris3;
    jointPris3.Initialize(hold1.getBody(),scn10.getBody(),scn10.getBody()->GetWorldCenter(),b2Vec2(1,0));
    jointPris3.enableLimit = true;
    jointPris3.lowerTranslation = -20.0f;
    jointPris3.upperTranslation = 1.0f;
    b2PrismaticJoint* jointp = (b2PrismaticJoint*)world.CreateJoint(&jointPris3);

    b2GearJointDef jointGea2;
    jointGea2.bodyA = jointp->GetBodyA(); //Dinamico Prismatico 1
    jointGea2.bodyB = jointr->GetBodyA(); //Dinamico revolute p/gear
    jointGea2.joint1 = jointp;
    jointGea2.joint2 = jointr;
    jointGea2.ratio = 1.0f;
    world.CreateJoint(&jointGea2);

    b2RevoluteJointDef jointRev4;
    jointRev4.Initialize(push.getBody(),scn10.getBody(),push.getBody()->GetWorldCenter());
    b2RevoluteJoint* jointr4 = (b2RevoluteJoint*)world.CreateJoint(&jointRev4);

    b2GearJointDef jointGea3;
    jointGea3.bodyA = jointr3->GetBodyA(); //Dinamico Prismatico 1
    jointGea3.bodyB = jointr4->GetBodyA(); //Dinamico revolute p/gear
    jointGea3.joint1 = jointr3;
    jointGea3.joint2 = jointr4;
    jointGea3.ratio = 1.0f;
    world.CreateJoint(&jointGea3);

    while (window.isOpen()) {
        sf::Event event;

        circ.getBody()->ApplyForceToCenter(b2Vec2(0.f,0.2f), true);
        push.getBody()->ApplyForceToCenter(b2Vec2(0.1f,0.f), true);
        while (window.pollEvent(event)) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                circ.resetPosition();
                circ2.resetPosition();
                cube2.resetPosition();
                cube3.resetPosition();
                dis1.resetPosition();
                dis2.resetPosition();
            }

            // The Z key event to close the window
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                window.close();
                return 0; // return from the main function, effectively ending the program
            }
        }

        world.Step(1 / 60.f, 8, 3);

        #pragma region update
        circ.update();
        circ2.update();
        circ3.update();
        circ4.update();
        cube.update();
        cube2.update();
        cube3.update();
        dis1.update();
        dis2.update();
        plat1.update();
        plat2.update();
        plat3.update();
        plat4.update();
        gear.update();
        hold1.update();
        push.update();

        #pragma endregion
        window.clear();

        #pragma region draw
        circ.draw(window);
        circ2.draw(window);
        circ3.draw(window);
        circ4.draw(window);
        cube.draw(window);
        cube1.draw(window);
        cube2.draw(window);
        cube3.draw(window);
        cube4.draw(window);
        scn1.draw(window);
        scn2.draw(window);
        scn3.draw(window);
        scn4.draw(window);
        scn5.draw(window);
        scn6.draw(window);
        scn7.draw(window);
        scn8.draw(window);
        scn9.draw(window);
        scn10.draw(window);
        scn11.draw(window);
        dis1.draw(window);
        dis2.draw(window);
        plat1.draw(window);
        plat2.draw(window);
        plat3.draw(window);
        plat4.draw(window);
        point1.draw(window);
        point2.draw(window);
        gear.draw(window);
        hold1.draw(window);
        push.draw(window);
        #pragma endregion
        window.display();
    }
    return 0;
}

