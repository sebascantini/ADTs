#include "gtest-1.8.1/gtest.h"
#include "../src/Nivel.h"
TEST(Nivel, nivel){

    set<Coordenada> paredesSet = {make_pair(-2, -1), make_pair(-2, 0), make_pair(-2, 1),
                                  make_pair(-1, 2), make_pair(0, 2), make_pair(1, 2),
                                  make_pair(2, 1), make_pair(2, 0), make_pair(2, -1),
                                  make_pair(-1, -2), make_pair(0, -2), make_pair(1, -2),};
    vector<Coordenada> paredes = { make_pair(-2, -1), make_pair(-2, 0), make_pair(-2, 1),
                                   make_pair(-1, -2), make_pair(-1, 2), make_pair(0, -2),
                                   make_pair(0, 2), make_pair(1, -2), make_pair(1, 2),
                                   make_pair(2, -1), make_pair(2, 0), make_pair(2, 1) };
    list<Coordenada> cajas = {make_pair(0, 1)};
    set<Coordenada> cajasSet = {make_pair(0, 1)};

    vector<Coordenada> depos = {make_pair(-1, 1)};
    set<Coordenada> deposSet = {make_pair(-1, 1)};

    aed2_Nivel aedN;
    aedN.paredes = paredesSet;
    aedN.cajas = cajasSet;
    aedN.depositos = deposSet;
    aedN.cantidadBombas = 0;
    aedN.posicionInicial = make_pair(0,0);

    Nivel n(aedN);
    ASSERT_EQ(n.depositosOcupados(), 0);
    ASSERT_EQ(n.disposiconDeParedes(), paredes);
    ASSERT_EQ(n.disposicoinDeDepositos(), depos);
    ASSERT_EQ(n.cajasIniciales(), cajas);
    ASSERT_EQ(n.posicionInicial(), make_pair(0,0));
    ASSERT_EQ(n.bombasIniciales(), 0);
}