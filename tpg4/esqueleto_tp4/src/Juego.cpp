#include "Juego.h"

Juego::Juego(vector<aed2_Nivel> ns) : _nivelActual(Soko(Nivel(ns.front()))), _niveles(ns){}

bool Juego::mover(PuntoCardinal d) {
    bool res = false;
    if(this->_nivelActual.pMov(d))
        this->_nivelActual.movj(d);
    if(this->_nivelActual.gane()){
        this->_niveles.erase(this->_niveles.begin());
        //Este chequeo lo agregamos para corregir un error del modulo
        if(this->_niveles.size() != 0)
            this->_nivelActual = Soko(Nivel(this->_niveles.front()));
        res = true;
    }
    return res;
}

void Juego::tirarBomba() {
    if(this->_nivelActual.verTNTs() != 0){
        this->_nivelActual.boom();
    }
}

void Juego::deshacer() {
    //Este chequeo lo agregamos para corregir un error del modulo
    if(this->_nivelActual.movimientosHechos() > 0){
        this->_nivelActual.undo();
    }
}

Soko Juego::verSoko() const {
    return this->_nivelActual;
}