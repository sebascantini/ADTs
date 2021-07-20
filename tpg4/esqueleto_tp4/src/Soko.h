#include "Nivel.h"

#ifndef TP4_SOKOBAN_SOKO_H
#define TP4_SOKOBAN_SOKO_H

class Soko{
public:
    Soko(Nivel);
    void movj(PuntoCardinal);
    void boom();
    void undo();
    bool gane();
    bool pMov(PuntoCardinal);
    Coordenada sigP(Coordenada, PuntoCardinal);
    bool hPar(Coordenada);
    Nat movimientosHechos();

    //Observadores... (para los tests)
    const bool operator==(Soko s) const;
    Coordenada verPosj();
    Nat verTNTs();
    list<Coordenada> verPbox();
    list<Coordenada> verPTNT();
    vector<Coordenada> verPpar();
    vector<Coordenada> verPdep();
    Nat verDocu();
    stack<tuple<Nat, bool, Nat>> verActs();

private:
    Coordenada _posj;
    Nat _TNTs;
    list<Coordenada> _pbox;
    list<Coordenada> _pTNT;
    vector<Coordenada> _ppar;
    vector<Coordenada> _pdep;
    Nat _docu;
    stack<tuple<Nat, bool, Nat>> _acts;
};

void OrdenarCoordenadas(vector<Coordenada> &v);

bool busquedaBinaria(Coordenada c, vector<Coordenada> pos);

bool busquedaLineal(Coordenada, list<Coordenada>);

#endif //TP4_SOKOBAN_SOKO_H
