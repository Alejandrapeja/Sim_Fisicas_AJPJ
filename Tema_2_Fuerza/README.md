# Tema 2 Fuerza
**Alejandra Jazmin Peña Jacobo**
## Conceptos

### Gravedad
Es el vector de fuerza que se genera por un planeta o un objeto con mucha masa, el cual actúa sobre los objetos cercanos, jalándolos al núcleo o centro del planeta.
### Densidad
Es la relación entre el peso y el espacio que ocupa un material, nos ayuda a saber no solo el peso de algo sino que tanto se tiene en determinado espacio o cuando se requiere.
### Fricción
Es la resistencia que oponen los materiales que rodean a un objeto a que este se mueva.
### Velocidad
Es un vector, por lo mismo sabemos que tiene componentes **_x_** y componentes **_y_**, los cuales son necesarios para que box2d simule la velocidad lineal.
### Box2D
Es un motor de físicas 2D, el cual nos ayuda a realizar ejercicios para comprender mejor la física y a crear simulaciones tomando en cuenta ciertos parámetros.

La instalación y optimo funcionamiento se encuentra en el README de Hola_Mundo
## Código
- Mencionando aspectos destacables del código es el hecho de que la gravedad tiene un valor de -1.62 pues es un vector que va hacia abajo o -y, si fuera hacia arriba seria positivo
- El valor en si es el valor de gravedad en la luna
- Es un cuadrado de 11x11cm = 0.11x0.11m con una densidad de 7874kg/m por estar hecho de hierro y en este caso no existe un piso con el cual medir su distancia por lo que solo se encuentra en el origen de la simulación 0,0
- La fricción de modifica a un valor arbitrario pues no se conoce con exactitud la de júpiter.
- En este caso se observa los efectos de la velocidad en el eje x y el eje y, en el cual son mayores en el eje y, y aun que este en movimiento, no deja de verse afectada por la gravedad.

## código
```cpp
#include <Box2D/Box2D.h>  
#include <cmath>  
#include <iostream>  

//Definiciones para poder utilizar pi
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
  
    // Crea un cuerpo dinamico para la bala   
    b2BodyDef bodyDef;  
    bodyDef.type = b2_dynamicBody;  
    bodyDef.position.Set(0.0f, 0.0f);  
    b2Body* body = world.CreateBody(&bodyDef);  
  
    // Se define la forma de una caja 
    b2PolygonShape dynamicBox; // para lograr hacerla un circulo se usaria b2CircleShape (aun que de momento se desconoce la implementacion pues no tiene un void set, por lo que es difente al b2PolygonShape)  
    dynamicBox.SetAsBox(0.11f, 0.11f);  
  
    // Da definiciones/caracteristicas del cuerpo
    b2FixtureDef fixtureDef;  
    fixtureDef.shape = &dynamicBox;  
    fixtureDef.density = 7874.0f; //Densidad del hierro  
    fixtureDef.friction = 0.1f;  
  
    // Se añade la figura al cuerpo  
    body->CreateFixture(&fixtureDef);  
  
    // Se define la velocidad inicial de la bala  
    float angle = 60.0f; // Angulo en grados  
    float speed = 250.0f; // Velocidad en m/s =900km/h 
    //Se usa trigonometria para obtener los componentes 
    float vx = speed * std::cos(angle * M_PI / 180.0f); 
    float vy = speed * std::sin(angle * M_PI / 180.0f);  
  
    body->SetLinearVelocity(b2Vec2(vx, vy));  
  
    // Se definen los valores necesarios para correr la simulacion  
    float timeStep = 1.0f / 60.0f;  
    int32 velocityIterations = 6;  
    int32 positionIterations = 2;  

	//Ciclo en el cual se imprime por cada paso la posicion de la bala
    for (int i = 0; i < 60; ++i)  
    {  
        world.Step(timeStep, velocityIterations, positionIterations);  
        std::cout << body->GetPosition().x << " " << body->GetPosition().y << std::endl;  
  
    }  
  
    // y se limpia el mundo
    world.DestroyBody(body);  
  
    return 0;  
}
```

