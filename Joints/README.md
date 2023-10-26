# Hola Joints
**Alejandra Jazmin Peña Jacobo**
## Conceptos

### SFML
Simple and Fast Multimedia Library, es una librería que permite darles una interfaz sencilla a varios componentes del equipo/programas, su instalación depende de añadir a CmakeList.txt lo siguiente (a parte de la integración de Box2D)

```cpp
include(FetchContent)  
set(BUILD_SHARED_LIBS OFF)  
FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)  
FetchContent_MakeAvailable(SFML)
target_link_libraries([ProjectName] PRIVATE sfml-system
```

### Box2D
Es un motor de físicas 2D, el cual nos ayuda a realizar ejercicios para comprender mejor la física y a crear simulaciones tomando en cuenta ciertos parámetros.

La instalación y optimo funcionamiento se encuentra en el README de Hola_Mundo
## Código
- Mencionando aspectos destacables del código se encuentra que la estructura es diferente a la acostumbrada, pues se crean clases con las cuales crear y obtener lo que se necesita para la creación de cuerpos y otras funcionalidades
- En el siguiente código se muestra la inicialización de la clase, para saber en donde se colocará tanto en el mundo como coordenadas, de manera predeterminada es un cuerpo dinámico, si se quisiera uno estático se tendría que especificar o crear otra clase, además de que se añadió un void Color para poder personalizar de una forma más rápida las ilustraciones.
- Se crea la ventana, se define la gravedad, se crean los cuerpos y se comienza a definir la unión entre estos (suele tener un formato: b2[Tipo]JointDef), se inicializa esta unión otorgando los valores que se solicitan que suelen ser body (para acceder al de la clase basta con poner cube.getBody()) y anchor, que vendría a ser una ubicación dentro de un cuerpo (se accede desde el getBody().GetWorldCenter() para obtener el centro de la figura) y finalmente se crea en el mundo.
- Manteniendo el resto del código, podemos controlar el movimiento de la figura 1 para ver más claramente las restricciones y posibilidades de cada tipo de joint:
	- Distance.- Mantiene a los cuerpos unidos a cierta distancia, actúa como un tubo(requiere de 2 cuerpos y 2 puntos de anclaje para cada uno).
	- Gear.- Hace que el movimiento de un cuerpo afecte a otro, pero funciona mas como la unión de 2 joints (revolute o prismatic), no se logró realizar su simulación pues no detecta los joints creados anteriormente como un formato aceptable.
	- Prismatic.- Une a 2 figuras y permite a la primera deslizarse de forma paralela a la 2da manteniendo un ángulo/axis dada (requiere de 2 cuerpos un punto de anclaje y una axis).
	- Revolute.- Une a 2 figuras y permite a la primera rotar anclada a la 2da (requiere 2 cuerpos y un punto de anclaje).
	- Weld.-Une 2 figuras sin permitir ningún tipo de movimiento (Requiere de 2 cuerpos y un punto de anclaje).
	- Wheel.- Similar al revolute, pero permite a la figura alejarse a voluntad como si estuviera sujeta con un elástico, a la vez que esta figura puede rotar conforme se mueve (requiere 2 cuerpos, un punto de anclaje y un axis)

```cpp
  
#include <SFML/Graphics.hpp>  
#include <Box2D/Box2D.h>  
  
constexpr float SCALE = 30.0f;  
  
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
  
int main() {  
    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML works!");  
  
    b2Vec2 gravity(0.0f, 0.0f);  
    b2World world(gravity);  
  
    Cube cube(world, 400, 300);  
    Cube cube2(world, 500, 300);  
    cube2.Color(sf::Color::Green);  
  
    b2DistanceJointDef jointDis;  
  
    //Creacion del joint Distance  
    jointDis.Initialize(cube.getBody(),cube2.getBody(),cube.getBody()->GetWorldCenter(),cube2.getBody()->GetWorldCenter());  
    world.CreateJoint(&jointDis);  
  
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
```

