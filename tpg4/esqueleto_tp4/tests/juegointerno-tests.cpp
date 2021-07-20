//
// Created by msorondo on 7/12/20.
//

#include "../src/Juego.h"
#include "gtest-1.8.1/gtest.h"

TEST(Juego, testEficiente){
    set<Coordenada> paredesSet = {make_pair(-2, -1), make_pair(-2, 0), make_pair(-2, 1),
                                  make_pair(-1, 2), make_pair(0, 2), make_pair(1, 2),
                                  make_pair(2, 1), make_pair(2, 0), make_pair(2, -1),
                                  make_pair(-1, -2), make_pair(0, -2), make_pair(1, -2),};
    vector<Coordenada> paredes = { make_pair(-2, -1), make_pair(-2, 0), make_pair(-2, 1),
                                   make_pair(-1, -2), make_pair(-1, 2), make_pair(0, -2),
                                   make_pair(0, 2), make_pair(1, -2), make_pair(1, 2),
                                   make_pair(2, -1), make_pair(2, 0), make_pair(2, 1) };
    list<Coordenada> cajas = {make_pair(0, 1) , make_pair(0,-1)};
    set<Coordenada> cajasSet = {make_pair(0, 1), make_pair(0,-1)};

    vector<Coordenada> depos = {make_pair(-1, 1), make_pair(1,-1)};
    set<Coordenada> deposSet = {make_pair(-1, 1), make_pair(1,-1)};

    aed2_Nivel aedN;
    aedN.paredes = paredesSet;
    aedN.cajas = cajasSet;
    aedN.depositos = deposSet;
    aedN.cantidadBombas = 2;
    aedN.posicionInicial = make_pair(0,0);


    list<Coordenada> cajas2 = {make_pair(0,-1)};
    set<Coordenada> cajasSet2 = {make_pair(0,-1)};

    vector<Coordenada> depos2 = {make_pair(1,-1)};
    set<Coordenada> deposSet2 = {make_pair(1,-1)};

    aed2_Nivel aedN2;
    aedN2.paredes = paredesSet;
    aedN2.cajas = cajasSet2;
    aedN2.depositos = deposSet2;
    aedN2.cantidadBombas = 2;
    aedN2.posicionInicial = make_pair(0,0);

    vector<aed2_Nivel> ln = {aedN2,aedN};

    Juego j(ln);
    j.mover(Sur);

    ASSERT_EQ(j.verSoko().verPosj(), make_pair(0,0));
    j.mover(Este);
    j.mover(Este);
    ASSERT_EQ(j.verSoko().verPosj(), make_pair(1,0));
    j.tirarBomba();
    j.mover(Este);
    ASSERT_EQ(j.verSoko().verPosj(), make_pair(2,0));
    j.deshacer();
    j.deshacer();
    j.mover(Este);
    ASSERT_EQ(j.verSoko().verPosj(), make_pair(1,0));
    j.mover(Oeste);

    j.mover(Oeste);
    j.mover(Sur);
    j.mover(Este);

    Soko s(aedN);
    ASSERT_EQ(j.verSoko(),s);
    j.mover(Oeste);
    j.mover(Sur);
    j.mover(Este);

    j.mover(Norte);
    j.mover(Este);
    j.mover(Norte);
    j.mover(Oeste);
    ASSERT_EQ(j.verSoko().verPosj(), make_pair(0,1));

}

