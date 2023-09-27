# Hola Mundo 
**Alejandra Jazmin Peña Jacobo**
## Conceptos

### Gravedad
Es el vector de fuerza que se genera por un planeta o un objeto con mucha masa, el cual actúa sobre los objetos cercanos, jalándolos al núcleo o centro del planeta.
### Densidad
Es la relación entre el peso y el espacio que ocupa un material, nos ayuda a saber no solo el peso de algo sino que tanto se tiene en determinado espacio o cuando se requiere.
### Fricción
Es la resistencia que oponen los materiales que rodean a un objeto a que este se mueva.
### Box2D
Es un motor de físicas 2D, el cual nos ayuda a realizar ejercicios para comprender mejor la física y a crear simulaciones tomando en cuenta ciertos parámetros.

La instalación y optimo funcionamiento se encuentra en el README de Hola_Mundo
## Código
- Mencionando aspectos destacables del código es el hecho de que la gravedad tiene un valor de -24.79 pues es un vector que va hacia abajo o -y, si fuera hacia arriba seria positivo
- El valor en si es el valor de gravedad en jupiter
- Es un cuadrado de 1x1m con una densidad de 15630kg/m por estar hecho de carburo de tungsteno y que se encuentra a 15m de altura.
- La fricción de modifica a un valor arbitrario pues no se conoce con exactitud la de jupiter.
- Si se compara con los resultados obtenidos en Hola_Mundo se observa que su caída es mucho más rápida, no alcanzando la misma cantidad, sino una menor, referente que esta más acercada del suelo, afectada por la gravedad del planeta y por la densidad del cubo.

```cpp
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
    //15.63 g/cm^3 o 15630.0 kg/m^3    fixtureDef.friction = 0.9f;  
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
```

