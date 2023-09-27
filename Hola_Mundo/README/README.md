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

Para su instalación se puede encontrar las especificaciones en: https://github.com/erincatto/box2d (Bajo el apartado de Installing using CMake)

Para un correcto funcionamiento en CLion

Seleccionamos Vcpkg
![[Captura de pantalla (2).png]]  

Posteriormente se selecciona el símbolo **+** y se añade vcpkg
![[Captura de pantalla (3).png]]

O en el icono de lápiz si ya se tenia instalado, pero es importante asegurarse que ambas casillas estén seleccionadas.
![[Captura de pantalla (4).png]]

De ahí se selecciona Installed>box2d>install y Add Packages to CMakeLists.txt
![[Captura de pantalla (5).png]]

Esto genera un par de líneas de código el cual al copiarlas se pegan en CMakeLists.txt, cambiando el "main" dentro de los paréntesis de la 2da línea por el nombre del proyecto, en este caso "Temp"
![[Captura de pantalla (6).png]]

Y así al verificar la build de CMake debería de funcionar correctamente.
## Código
- Mencionando aspectos destacables del código es el hecho de que la gravedad tiene un valor de -9.81 pues es un vector que va hacia abajo o -y, si fuera hacia arriba seria positivo
- El valor en si es el valor de gravedad en la tierra
- Es un cuadrado de 1x1m con una densidad de 1kg/m y que se encuentra a 20m de altura.
- Se observa que en el tiempo dado no alcanza a llegar al suelo, pero se sabe que este valor se ve principalmente afectado por la gravedad del planeta

```cpp
#include <iostream>  
#include <Box2d/Box2d.h>  
  
int main(){  
    //Creacion del mundo con gravedad  
    b2Vec2 gravedad(0.0f,-9.81f);
    b2World world(gravedad);  
    //Caracteristicas del cuerpo piso  
    b2BodyDef pisoBodyDef;  
    pisoBodyDef.position.Set(0.0f,-10.0f);  
    //Creacion en el mundo  
    b2Body* pisoBody = world.CreateBody(&pisoBodyDef);  
	  
    //Crear su forma  
    b2PolygonShape groundBox;  
    groundBox.SetAsBox(50.0f,1.0f);  
	  
    pisoBody ->CreateFixture(&groundBox, 0.0f);  
	  
    b2BodyDef bodyDef;  
    bodyDef.type = b2_dynamicBody;  
    bodyDef.position.Set(0.0f,20.0f);  
    b2Body* body = world.CreateBody(&bodyDef);  
	
	//Creacion del cuerpo dinamico/que va a caer
    b2PolygonShape dynamicBox;  
    dynamicBox.SetAsBox(1.0f,1.0f);  
	  
    b2FixtureDef fixtureDef;  
    fixtureDef.shape = &dynamicBox;  
    fixtureDef.density = 1.0f;  
    fixtureDef.friction = 0.3f;  
	  
    body ->CreateFixture(&fixtureDef);  
	
	//Se configuran los tiempos, la velocidad de iteraciones y las posiciones
    float timeStep = 1.0f/60.0f;  
	  
    int32 velocityIterations = 6;  
    int32 positionIteration = 2;  
	
	//Ciclo para imprimir las posiciones segun lo configurado
    for (int32 i = 0; i<60; ++i){  
        world.Step(timeStep,velocityIterations,positionIteration);  
        b2Vec2 position = body ->GetPosition();  
        float angle = body ->GetAngle();  
        printf("%4.2f %4.2f %4.2f\n",position.x,position.y,angle);  
    }  
}
```

