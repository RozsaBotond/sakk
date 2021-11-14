#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "fv.h"


//a az osszes sargaval kijelolt negyzetet atlatszora allitja
//nem tudum miert true-ra kell allitani nem logikus de mukodik
void alap_hatter(bool sakk_hatter[8][8]){
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        sakk_hatter[i][j]=true;
      }
    }
}
/*parpameterkent kapott sakk tablajanak tombjet allitja be alapallasba.*/
void alap_tabla(Babu sakk_tabla[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            sakk_tabla[i][j]=Ures;
        }
    }
    sakk_tabla[0][0] = VBastya;
    sakk_tabla[1][0] = VHuszar;
    sakk_tabla[2][0] = VFuto;
    sakk_tabla[3][0] = VKiraly;
    sakk_tabla[4][0] = VVezer;
    sakk_tabla[5][0] = VFuto;
    sakk_tabla[6][0] = VHuszar;
    sakk_tabla[7][0] = VBastya;
    sakk_tabla[0][1] = VGyalog;
    sakk_tabla[1][1] = VGyalog;
    sakk_tabla[2][1] = VGyalog;
    sakk_tabla[3][1] = VGyalog;
    sakk_tabla[4][1] = VGyalog;
    sakk_tabla[5][1] = VGyalog;
    sakk_tabla[6][1] = VGyalog;
    sakk_tabla[7][1] = VGyalog;
    sakk_tabla[0][7] = SBastya;
    sakk_tabla[1][7] = SHuszar;
    sakk_tabla[2][7] = SFuto;
    sakk_tabla[3][7] = SKiraly;
    sakk_tabla[4][7] = SVezer;
    sakk_tabla[5][7] = SFuto;
    sakk_tabla[6][7] = SHuszar;
    sakk_tabla[7][7] = SBastya;
    sakk_tabla[0][6] = SGyalog;
    sakk_tabla[1][6] = SGyalog;
    sakk_tabla[2][6] = SGyalog;
    sakk_tabla[3][6] = SGyalog;
    sakk_tabla[4][6] = SGyalog;
    sakk_tabla[5][6] = SGyalog;
    sakk_tabla[6][6] = SGyalog;
    sakk_tabla[7][6] = SGyalog;
}

/* kirajzol egy babut; a forras a betoltott png, a cel nevu kepre rajzol.
 * melyik babut, milyen koordinatakra: melyik, x, y. */
void babu_rajzol(SDL_Renderer *renderer, SDL_Texture *babuk, Babu melyik, int x, int y) {
    if(melyik!=12){
        /* a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk. */
        SDL_Rect src = { (melyik % 6) * 100, (melyik / 6) * 100, MERET, MERET };
        /* a cel kepre, ezekre a koordinatakra masoljuk */
        SDL_Rect dest = { x, y, MERET, MERET };
        /* kepreszlet masolasa */
        SDL_RenderCopy(renderer, babuk, &src, &dest);
    }
}

//A sarga negyzettel kijelolt negyzeteket megjeleniti
void hatter_rajzol(SDL_Renderer *renderer, SDL_Texture *hatter, bool sakk_hatter[8][8] , int x, int y) {
  if(sakk_hatter[x][y]==true){
        /* a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk. */
        SDL_Rect src = { 0 , 0 , MERET, MERET };
        /* a cel kepre, ezekre a koordinatakra masoljuk */
        SDL_Rect dest = { x, y, MERET, MERET };
        /* kepreszlet masolasa */
        SDL_RenderCopy(renderer, hatter, &src, &dest);

  }
}

//betolt egy kepet a renderer parameterkent kapott pointerre és a parameterkent kapott kep helyevel
SDL_Texture* kep_betolt(SDL_Renderer *renderer, char* path){
    SDL_Texture *tmp = IMG_LoadTexture(renderer, path);

    if (tmp == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }
    return tmp;
}

/* kirajzolja a tablat*/
void tabla_rajzol(SDL_Renderer *renderer, SDL_Texture *tabla) {
    /* a forras kepbol ezekrol a koordinatakrol, ilyen meretu reszletet masolunk. */
    SDL_Rect src = { 0, 0, X, Y };
    /* a cel kepre, ezekre a koordinatakra masoljuk */
    SDL_Rect dest = { 0, 0, X, Y };
    /* kepreszlet masolasa */
    SDL_RenderCopy(renderer, tabla, &src, &dest);
}
/* ablak megnyitasa */
void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}
