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
