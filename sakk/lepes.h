#ifndef LEPES_H
#define LEPES_H

#include "lepes.h"
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include "fv.h"

void feher_kiraly_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void fekete_kiraly_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void feher_paraszt_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void fekete_paraszt_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void feher_bastya_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void fekete_bastya_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void feher_kiralyno_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void fekete_kiralyno_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void fekete_futo_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void feher_futo_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void feher_huszar_lep(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);
void fekete_huszar_lep(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y);

#endif
