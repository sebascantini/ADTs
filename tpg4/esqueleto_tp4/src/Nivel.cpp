#include "Nivel.h"
list<Coordenada> deSetAList(set<Coordenada> s){
    list<Coordenada> l;
    for(Coordenada c:s){
        l.push_back(c);
    }
    return l;
}
vector<Coordenada> deSetAVec(set<Coordenada> s){
    vector<Coordenada> v;
    for(Coordenada c:s){
        v.push_back(c);
    }
    return v;
}
Nivel::Nivel(aed2_Nivel n) {
    this->posij = n.posicionInicial;
    this->bombs = n.cantidadBombas;
    this->boxes = deSetAList(n.cajas);
    this->walls = deSetAVec(n.paredes);
    this->depos = deSetAVec(n.depositos);
    this->docup = 0;
    list<Coordenada>::iterator  iteradorCajas = this->boxes.begin();
    while (iteradorCajas != this->boxes.end()){
        for (int i = 0; i < depos.size(); ++i) {
            if(*iteradorCajas == depos[i]){
                this->docup++;
            }
        }
        iteradorCajas++;
    }
}

Coordenada Nivel::posicionInicial() {
    return this->posij;
}

Nat Nivel::bombasIniciales() {
    return this->bombs;
}

vector<Coordenada> Nivel::disposiconDeParedes() {
    return this->walls;
}

vector<Coordenada> Nivel::disposicoinDeDepositos() {
    return this->depos;
}

list<Coordenada> Nivel::cajasIniciales() {
    return this->boxes;
}

Nat Nivel::depositosOcupados() {
    return this->docup;
}