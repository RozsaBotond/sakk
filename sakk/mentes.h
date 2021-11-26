#ifndef MENTES_H
#define MENTES_H
#include <stdlib.h>
#include <stdio.h>
#include "fv.h"


typedef struct ListaElem {
    Babu adat[8][8];
    struct ListaElem *kov;
    struct ListaElem *elo;
} ListaElem;


ListaElem* Beszur(ListaElem* lista, Babu adat[8][8]);
ListaElem* Beszur_vege(ListaElem* lista, Babu adat[8][8]);
int Meret_szamol(ListaElem* lista);
void Felszabadit(ListaElem* lista);
ListaElem* Keres(ListaElem* ls, Babu adat[8][8]);
bool Babu_elmozdult(ListaElem* ls, Babu adat[8][8], int x, int y);
bool Lista_hasonlit(Babu adat[8][8], Babu masolando[8][8]);
void Lista_masol(Babu adat[8][8], Babu masolando[8][8]);
ListaElem* Elozo(ListaElem* ls);
void Mentes(ListaElem* ls);

#endif
