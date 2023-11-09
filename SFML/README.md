# Hola SFML
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
- Mencionando aspectos destacables del código se encuentra que la estructura es diferente a la acostumbrada, pues se crean clases con las cuales crear y obtener lo que se necesita para la creación de cuerpos y otras funcionalidades.
- En el main() se crea una ventana sobre la cual se va a ilustrar la simulación, asi como también se asigna la gravedad, y se crea un cubo dinámico.
- Posteriormente mientras la ventana este abierta se le aplican diferentes valores de fuerza cada vez que se presione alguna tecla (WASD) o se regresa a su estado original (space), incluso se deteniene por completo(R) y para evitar tener que forzar la cerrada de la ventana se le asigna a Z esa función.
- Finalmente se le asigna los pasos al mundo o la velocidad en la que transcurre el tiempo por así decirlo, se actualiza la posición del cubo, se limpia la pantalla, se dibuja la actualización y se muestra en el mundo, esto es lo que le da la apariencia de movimiento.

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
        body = world.CreateBody(&bodydef);  
  
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
  
        window.clear();  
        cube.draw(window);  
        window.display();  
    }  
    return 0;  
}
```

