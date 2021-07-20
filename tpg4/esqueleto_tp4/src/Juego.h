#include "Soko.h"

#ifndef TP4_SOKOBAN_JUEGO_H
#define TP4_SOKOBAN_JUEGO_H

class Juego{
public:
    Juego(vector<aed2_Nivel>);
    bool mover(PuntoCardinal);
    void tirarBomba();
    void deshacer();

    Soko verSoko() const;
private:
    vector<aed2_Nivel> _niveles;
    Soko _nivelActual;
};

#endif //TP4_SOKOBAN_JUEGO_H

