#include "gtest-1.8.1/gtest.h"
#include "../src/Soko.h"

TEST(Soko, OrdenYBusqueda) {
    vector<Coordenada> todasDistintas = {make_pair(2, 5), make_pair(1, 2), make_pair(5, 6), make_pair(4, 8)};
    vector<Coordenada> todasIguales = {make_pair(1, 2), make_pair(1, 2), make_pair(1, 2)};
    vector<Coordenada> compararPorLaSegunda = {make_pair(3, 5), make_pair(1, 2), make_pair(3, 3), make_pair(1, 5)};

    vector<Coordenada> sc1 = {make_pair(1, 2), make_pair(2, 5), make_pair(4, 8), make_pair(5, 6)};
    vector<Coordenada> sc2 = {make_pair(1, 2), make_pair(1, 2), make_pair(1, 2)};
    vector<Coordenada> sc3 = {make_pair(1, 2), make_pair(1, 5), make_pair(3, 3), make_pair(3, 5)};

    OrdenarCoordenadas(todasDistintas);
    OrdenarCoordenadas(todasIguales);
    OrdenarCoordenadas(compararPorLaSegunda);

    ASSERT_EQ(todasIguales, sc2);
    ASSERT_EQ(todasDistintas, sc1);
    ASSERT_EQ(compararPorLaSegunda, sc3);

    ASSERT_TRUE(busquedaBinaria(make_pair(5, 6), todasDistintas));
    ASSERT_TRUE(busquedaBinaria(make_pair(1, 2), todasIguales));
    ASSERT_TRUE(busquedaBinaria(make_pair(3, 5), compararPorLaSegunda));
    ASSERT_FALSE(busquedaBinaria(make_pair(2,4), todasIguales));
}

//Medio trucho esto, lo podemos hacer mejor?
TEST(Soko, movimientos){
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
    Soko s(n);

    s.movj(Este);
    s.movj(Norte);

    ASSERT_EQ(s.verPosj(),make_pair(1,1));
    stack<tuple<Nat, bool, Nat>> st;
    st.push(make_tuple(Este, false, 0));
    st.push(make_tuple(Norte, false, 0));
    ASSERT_EQ(s.verActs(), st);

    s.movj(Oeste);
    st.push(make_tuple(Oeste, true, -1));

    ASSERT_EQ(s.verPosj(),make_pair(0,1));
    ASSERT_EQ(s.verActs(),st);
    ASSERT_EQ(1,s.verDocu());
    list<Coordenada> v ={make_pair(-1,1)};
    ASSERT_EQ(s.verPbox(),v);
    ASSERT_EQ(s.gane(),true);

}
//No sabemos como chequear esto.

TEST(Soko, Bombas){
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
    aedN.cantidadBombas = 2;
    aedN.posicionInicial = make_pair(0,0);

    Nivel n(aedN);
    Soko s(n);
    ASSERT_EQ(2,s.verTNTs());
    s.boom();
    ASSERT_EQ(1,s.verTNTs());
    list<Coordenada> v = {make_pair(0,0)};
    ASSERT_EQ(s.verPTNT(),v);
    stack<tuple<Nat, bool, Nat>> st;
    st.push(make_tuple(4,false,0));
    ASSERT_EQ(s.verActs(), st);

}


TEST(Soko, comprobarVictoria){
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

    Nivel n(aedN);
    Soko s(n);

    s.movj(Este);
    s.movj(Norte);
    s.movj(Oeste);
    ASSERT_EQ(s.gane(),false);
    s.movj(Sur);
    s.movj(Oeste);
    s.movj(Sur);
    s.movj(Este);
    ASSERT_EQ(s.gane(),true);

}
TEST(Soko, undo){
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

    Nivel n(aedN);
    Soko s(n);

    s.movj(Oeste);
    s.undo();
    stack<tuple<Nat, bool, Nat>> st;
    ASSERT_EQ(s.verActs(),st);
    ASSERT_EQ(make_pair(0,0), s.verPosj());

    s.movj(Oeste);
    s.movj(Norte);
    s.movj(Este);

    s.undo();
    s.undo();
    s.undo();

    ASSERT_EQ(make_pair(0,0), s.verPosj());
    ASSERT_EQ(s.verActs(), st);
    s.movj(Este);
    s.movj(Norte);
    s.movj(Oeste);

    s.undo();
    ASSERT_EQ(s.verDocu(),0);
    ASSERT_EQ(make_pair(1,1),s.verPosj());
    list<Coordenada> v = {make_pair(0,1),make_pair(0,-1)};
    ASSERT_EQ(s.verPbox(),v);

    s.boom();
    s.undo();

    list<Coordenada> ls;
    ASSERT_EQ(s.verTNTs(), 2);
    ASSERT_EQ(s.verPTNT(), ls);


}

TEST(Soko, puedeMover){
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

    Nivel n(aedN);
    Soko s(n);
    ASSERT_TRUE(s.pMov(Este));

    ASSERT_FALSE(s.pMov(Norte));

    s.movj(Este);
    s.movj(Norte);

    ASSERT_TRUE(s.pMov(Oeste));
    ASSERT_FALSE(s.pMov(Norte));
    ASSERT_FALSE(s.pMov(Este));

    s.boom();
    ASSERT_TRUE(s.pMov(Este));
    ASSERT_TRUE(s.pMov(Norte));

}