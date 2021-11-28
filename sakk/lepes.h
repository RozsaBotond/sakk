#ifndef LEPES_H
#define LEPES_H

#include "lepes.h"
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include "mentes.h"

typedef struct{
  int x;
  int y;
} Hely;

typedef struct{
  bool elpassant;
  bool rosal;
}kulonleges_lep;

bool feher_kiraly_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls);
bool fekete_kiraly_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls);
bool feher_paraszt_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls);
bool fekete_paraszt_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls);
void feher_bastya_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void fekete_bastya_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void feher_kiralyno_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void fekete_kiralyno_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void fekete_futo_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void feher_futo_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void feher_huszar_lep(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void fekete_huszar_lep(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
kulonleges_lep feher_babu_jolepes(Babu sakk_tabla[8][8], bool jolepes[8][8], ListaElem* lista, int i, int j);
kulonleges_lep fekete_babu_jolepes(Babu sakk_tabla[8][8], bool jolepes[8][8], ListaElem* lista, int i, int j);
bool sakk_feher(Babu sakk_tabla[8][8], ListaElem* lista);
bool sakk_fekete(Babu sakk_tabla[8][8], ListaElem* lista);
bool matt_feher(Babu sakk_tabla[8][8], ListaElem* lista);
bool matt_fekete(Babu sakk_tabla[8][8], ListaElem* lista);
bool jelol_csak_feher(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
bool jelol_csak_fekete(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);

#endif
