#include "Soko.h"

//Definimos la función ordenar vectores de coordenadas
void OrdenarCoordenadas(vector<Coordenada> &v){
    for (int i = 0; i < v.size(); ++i) {
        int min = i;
        for (int j = i+1; j < v.size(); ++j) {
            if(v[j].first < v[min].first){
                min = j;
            }else if (v[j].first == v[min].first && v[j].second < v[min].second){
                min = j;
            }
        }
        Coordenada aux = v[min];
        v[min] = v[i];
        v[i] = aux;
    }
}

//Definimos la función de busqueda binaria
bool busquedaBinaria(Coordenada coor, vector<Coordenada> pos) {
    int a = 0;
    int b = pos.size();
    if(pos.size()==0)
        return false;
    while (a + 1 < b && pos[a] != coor){
        int c = (a + b) / 2;
        if (pos[c].first < coor.first || (pos[c].first == coor.first && pos[c].second <= coor.second)) {
            a = c;
        } else {
            b = c;
        }
    }
    return pos[a] == coor;
}

bool busquedaLineal(Coordenada coor, list<Coordenada> pos){
    bool rta = false;
    for(Coordenada c : pos)
        if(c == coor)
            rta = true;
    return rta;
}


Soko::Soko(Nivel n){
    this->_posj = n.posicionInicial();
    this->_TNTs = n.bombasIniciales();
    this->_pbox = n.cajasIniciales();
    this->_pTNT = list<Coordenada> ();
    this->_ppar = n.disposiconDeParedes();
    this->_pdep = n.disposicoinDeDepositos();
    this->_acts = stack<tuple<Nat, bool, Nat>>();
    this->_docu = n.depositosOcupados();

    OrdenarCoordenadas(this->_ppar);
    OrdenarCoordenadas(this->_pdep);
}

void Soko::movj(PuntoCardinal dir) {
    this->_posj = sigP(this->_posj, dir);
    bool seMovioCaja = false;
    int cambioEnDepositos = 0;

    list<Coordenada>::iterator it = this->_pbox.begin();
    while (it != this->_pbox.end()) { //preguntar por el .end()
        if ( *it == _posj){
            this->_pbox.erase(it);
            this->_pbox.push_back(sigP(this->_posj, dir));
            seMovioCaja = true;
            break;
        }
        advance(it,1);
    }
    if (seMovioCaja && busquedaBinaria(sigP(this->_posj, dir),this->_pdep)){
        this->_docu++;
        cambioEnDepositos--;
    }
    if (seMovioCaja && busquedaBinaria(this->_posj, this->_pdep)){
        this->_docu--;
        cambioEnDepositos++;
    }
    this->_acts.push(make_tuple(dir,seMovioCaja,cambioEnDepositos));
}


void Soko::boom(){
    this->_acts.push(make_tuple(4, false, 0));
    this->_pTNT.push_back(this->_posj);
    this->_TNTs--;
}

void Soko::undo() {
    this->_docu = this->_docu + get<2>(this->_acts.top());
    if(get<0>(this->_acts.top()) == 4){
        this->_pTNT.pop_back();
        this->_TNTs++;
    }else{
        if(get<1>(this->_acts.top())){
            this->_pbox.pop_back();
            this->_pbox.push_front(this->_posj);
        }
        if(get<0>(this->_acts.top()) < 2){
            if(get<0>(this->_acts.top()) == 0)
                this->_posj = sigP(this->_posj, Sur);
            else
                this->_posj = sigP(this->_posj, Norte);
        }else{
            if(get<0>(this->_acts.top()) == 2)
                this->_posj = sigP(this->_posj, Oeste);
            else
                this->_posj = sigP(this->_posj, Este);
        }
    }
    this->_acts.pop();
}

bool Soko::gane(){
    if(_docu == _pdep.size()){
        return true;
    }
    else{
        return false;
    }
}


bool Soko::pMov(PuntoCardinal d){
    bool cajasContiguas = busquedaLineal(sigP(this->_posj, d), this->_pbox) && (busquedaLineal(sigP(sigP(this->_posj, d), d), this->_pbox));
    bool cajaAdelanteDePared = busquedaLineal(sigP(this->_posj, d), this->_pbox) && hPar(sigP(sigP(this->_posj, d),d));
    bool hayPared = hPar(sigP(this->_posj, d));

    return !cajasContiguas && !cajaAdelanteDePared && !hayPared;
}

Coordenada Soko::sigP(Coordenada c, PuntoCardinal dir) {
    Coordenada res;
    if(dir < 2){
        if(dir == 0)
            res = make_pair(c.first, c.second+1);
        else
            res = make_pair(c.first, c.second-1);
    }
    else{
        if(dir==2)
            res = make_pair(c.first+1,c.second);
        else
            res = make_pair(c.first-1,c.second);
    }
    return res;
}

bool Soko::hPar(Coordenada c) {
    bool res = false;
    if(busquedaBinaria(c, this->_ppar)){
        list<Coordenada> aux = this->_pTNT;
        while(aux.size() > 0){
            if(c.first == aux.front().first || c.second == aux.front().second)
                return res;
            else
                aux.pop_front();
        }
        return !res;
    }
    return res;
}


const bool Soko::operator==(Soko s) const{
    return (this->_docu==s._docu && this->_acts==s._acts && this->_pdep==s._pdep && this->_ppar==s._ppar && this->_pTNT==s._pTNT
            && this->_pbox==s._pbox && this->_posj==s._posj && this->_TNTs==s._TNTs);
}


Nat Soko::movimientosHechos() {
    return this->_acts.size();
}

// Definicion de los observadores
Coordenada Soko::verPosj() {
    return _posj;
}
Nat Soko::verTNTs() {
    return _TNTs;
}
list<Coordenada> Soko::verPbox() {
    return _pbox;
}
list<Coordenada> Soko::verPTNT() {
    return _pTNT;
}
vector<Coordenada> Soko::verPpar() {
    return _ppar;
}
vector<Coordenada> Soko::verPdep() {
    return _pdep;
}
Nat Soko::verDocu() {
    return _docu;
}
stack<tuple<Nat, bool, Nat>> Soko::verActs() {
    return _acts;
}

