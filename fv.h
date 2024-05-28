
#ifndef FV_H
#define FV_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef enum Babu {
    VKiraly, VVezer, VFuto, VHuszar, VBastya, VGyalog,
    SKiraly, SVezer, SFuto, SHuszar, SBastya, SGyalog,
    Ures
} Babu;
/* a pieces.png fajlban levo figurak merete */
enum M_{ MERET = 100 };
/* a tabla merete a tabla.png fajlban*/
enum ABLAK{
    X = 800,
    Y = 799
};

void alap_hatter(bool sakk_hatter[8][8]);
void alap_tabla(Babu sakk_tabla[8][8]);
void babu_rajzol(SDL_Renderer *renderer, SDL_Texture *babuk, Babu melyik, int x, int y);
void hatter_rajzol(SDL_Renderer *renderer, SDL_Texture *hatter, bool sakk_hatter[8][8] , int x, int y);
void babu_kivalszt(SDL_Renderer *renderer, SDL_Texture *babuk, bool feher);
SDL_Texture* kep_betolt(SDL_Renderer *renderer, char* path);
void tabla_rajzol(SDL_Renderer *renderer, SDL_Texture *tabla);
void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
SDL_Texture* kep_betolt(SDL_Renderer *renderer, char* path);
void menu_rajzol(SDL_Renderer *renderer, SDL_Texture *menu_hatter, SDL_Texture *also_gombok, SDL_Texture *mentes_gombok);

#endif
