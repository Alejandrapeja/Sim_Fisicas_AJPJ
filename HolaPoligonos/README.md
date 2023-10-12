# Hola Polígonos 
**Alejandra Jazmin Peña Jacobo**
## Conceptos

### b2PolygonShape
Es parte del modulo de colisiones de Box2D, el cual nos permite crear varios polígonos regulares o irregulares, con simplemente otorgarle las posiciones de los vértices en _x_ y _y_ en un arreglo de vectores, así como un int con el numero de vértices.
### Skin Collision
Es un elemento que se genera a junto al momento de generarse un polígono, para que se generé de forma correcta es necesario que al momento de establecer un b2PolygonShape se verifique que el arreglo de vértices van en sentido anti-horario y que las uniones no se traslapen, para que así se genere esta piel en el exterior y no al interior de la figura.
### Box2D
Es un motor de físicas 2D, el cual nos ayuda a realizar ejercicios para comprender mejor la física y a crear simulaciones tomando en cuenta ciertos parámetros.

La instalación y optimo funcionamiento se encuentra en el README de Hola_Mundo
## Código
- Mencionando aspectos destacables del código se encuentra que el proceso en general para cada polígono solicitado (triangulo rectángulo, cuadrado, pentágono, hexágono y octágono) se sigue la misma estructura pero cambiando el largo del arreglo de vectores así como el valor de su respectivo int.
- Cada vector se declara (*X* , *Y*) un vector por vértice del polígono, se generará uniones entre estos en ese orden por lo que es importante evitar que se traslapen, así como asignar los vértices de derecha a izquierda o en sentido anti-horario.
- Se declara el integral que contiene el valor numérico de la cantidad de vértices que posee el polígono, para posteriormente darle nombre y asignarle el arreglo y este int.

```cpp
#include <iostream>  
#include <Box2d/Box2d.h>  
  
int main() {  
    //Creacion de triangulo rectangulo  
    b2Vec2 verticesT[3];  
    verticesT[0].Set(-4.0f, 1.0f);  
    verticesT[1].Set(-4.0f, 0.0f);  
    verticesT[2].Set(-3.0f, 1.0f);  
  
    int32 countT = 3;  
    b2PolygonShape Triangle;  
    Triangle.Set(verticesT, countT);  
  
    //Creacion de Cuadrado  
    b2Vec2 verticesC[4];  
    verticesC[0].Set(-2.0f, 1.0f);  
    verticesC[1].Set(-2.0f, 0.0f);  
    verticesC[2].Set(-1.0f, 0.0f);  
    verticesC[3].Set(-1.0f, 1.0f);  
  
    int32 countC = 4;  
    b2PolygonShape Square;  
    Square.Set(verticesC, countC);  
  
    //Creacion de pentagono  
    b2Vec2 verticesP[5];  
    verticesP[0].Set(0.5f, 1.0f);  
    verticesP[1].Set(0.0f, 0.5f);  
    verticesP[2].Set(0.25f, 0.0f);  
    verticesP[3].Set(0.75f, 0.0f);  
    verticesP[4].Set(1.0f, 0.5f);  
  
    int32 countP = 5;  
    b2PolygonShape Penta;  
    Penta.Set(verticesP, countP);  
  
    //Creacion de hexagono  
    b2Vec2 verticesH[6];  
    verticesH[0].Set(2.5f, 1.0f);  
    verticesH[1].Set(2.0f, 0.75f);  
    verticesH[2].Set(2.0f, 0.3f);  
    verticesH[3].Set(2.5f, 0.0f);  
    verticesH[4].Set(3.0f, 0.3f);  
    verticesH[5].Set(3.0f, 0.75f);  
  
    int32 countH = 6;  
    b2PolygonShape Hexa;  
    Hexa.Set(verticesH, countH);  
  
    //Creacion de Octagono  
    b2Vec2 verticesO[8];  
    verticesO[0].Set(4.5f, 1.0f);  
    verticesO[1].Set(4.1f, 0.85f);  
    verticesO[2].Set(4.0f, 0.5f);  
    verticesO[3].Set(4.1f, 0.1f);  
    verticesO[4].Set(4.5f, 0.0f);  
    verticesO[5].Set(4.85f, 0.1f);  
    verticesO[6].Set(5.0f, 0.5f);  
    verticesO[7].Set(4.85f, 0.85f);  
  
    int32 countO = 8;  
    b2PolygonShape Octa;  
    Octa.Set(verticesO, countO);  
}
```

