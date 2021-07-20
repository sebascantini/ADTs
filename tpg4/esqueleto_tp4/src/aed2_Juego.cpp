#include "aed2_Juego.h"

aed2_Juego::aed2_Juego(vector<aed2_Nivel> ns) : j(Juego(ns)) {
}

bool aed2_Juego::hayPared(Coordenada c) const {
    return this->j.verSoko().hPar(c);
}

bool aed2_Juego::hayDeposito(Coordenada c) const {
    return busquedaBinaria(c,this->j.verSoko().verPdep());
}

bool aed2_Juego::hayCaja(Coordenada c) const {
    return busquedaLineal(c, this->j.verSoko().verPbox());
}

Coordenada aed2_Juego::posicionActual() const {
    return this->j.verSoko().verPosj();
}

Nat aed2_Juego::cantidadBombas() const {
    return this->j.verSoko().verTNTs();
}

bool aed2_Juego::sePuedeMover(PuntoCardinal pc) const {
    return this->j.verSoko().pMov(pc);
}

// IMPORTANTE: Debe devolver:
// - true si al mover se completa el nivel actual
// - false en caso contrario.
bool aed2_Juego::mover(PuntoCardinal pc) {
    return this->j.mover(pc);
}

void aed2_Juego::tirarBomba() {
    this->j.tirarBomba();
}

void aed2_Juego::deshacer() {
    this->j.deshacer();
}

