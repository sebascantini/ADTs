
#ifndef TP4_SOKOBAN_NIVEL_H
#define TP4_SOKOBAN_NIVEL_H
#include "Tipos.h"
class Nivel{

public:
    Nivel(aed2_Nivel);
    //Nivel(Coordenada posIni, Nat bombas, list<Coordenada> cajas, vector<Coordenada> paredes, vector<Coordenada> depositos);

    Coordenada posicionInicial();
    Nat bombasIniciales();
    list<Coordenada> cajasIniciales();
    vector<Coordenada> disposiconDeParedes();
    vector<Coordenada> disposicoinDeDepositos();
    Nat depositosOcupados();
private:
    Coordenada posij;
    Nat bombs;
    list<Coordenada> boxes;
    vector<Coordenada> walls;
    vector<Coordenada> depos;
    Nat docup;

};


#endif //TP4_SOKOBAN_NIVEL_H
