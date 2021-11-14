#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "fv.h"
#include "lepes.h"


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(X, Y, &window, &renderer);

    /* kep betoltese */
    SDL_Texture *babuk = kep_betolt(renderer, "img/babuk.png");
    SDL_Texture *tabla = kep_betolt(renderer, "img/tabla.png");
    SDL_Texture *hatter = kep_betolt(renderer, "img/negyzet.png");

    Babu sakk_tabla[8][8];
    bool sakk_hatter[8][8];
    //sakk_tabla es sakk_hatter alaphelyzetere allitasa
    alap_tabla(sakk_tabla);
    alap_hatter(sakk_hatter);

    /* rajz keszitese */
    tabla_rajzol(renderer, tabla);
    SDL_RenderPresent(renderer);



        /* az esemenyvezerelt hurok */
    bool quit = false;
    bool click = false;
    int elozox = 0;
    int elozoy = 0;
    bool kivalasztva = false;
    while (!quit) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        bool rajzoltam = false;
        //kirajzolja a tablan levo sarga negyzeteket
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                  babu_rajzol(renderer, hatter, sakk_hatter[i][j], i*MERET, j*MERET);
            }
        }

        //kirajzolja a tablan levo babukat
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                babu_rajzol(renderer, babuk, sakk_tabla[i][j], i*MERET, j*MERET);
            }
        }
        SDL_RenderPresent(renderer);

        switch (event.type) {
            /* eger kattintas */
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = true;
                    int t_y = event.button.y/100;
                    int t_x = event.button.x/100;
                    //ha mar kattintottunk mar egy karakterre (kivalasztottuk) akkor igaz lesz
                    if(kivalasztva){
                      if((elozox == t_x) && (elozoy == t_y)){
                        alap_hatter(sakk_hatter);
                        kivalasztva=false;
                      }
                      else{
                        if(sakk_hatter[t_x][t_y]==false){
                            sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                            sakk_tabla[elozox][elozoy]=Ures;
                        }
                        alap_hatter(sakk_hatter);
                        kivalasztva=false;
                      }
                    }
                    else{
                      feher_huszar_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      fekete_huszar_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      feher_kiralyno_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      fekete_kiralyno_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      feher_futo_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      fekete_futo_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      feher_bastya_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      fekete_bastya_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      feher_kiraly_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      fekete_kiraly_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      feher_paraszt_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      fekete_paraszt_lep(sakk_tabla, sakk_hatter, t_x, t_y);
                      kivalasztva=true;
                    }
                    rajzoltam = true;
                    elozox = event.button.x/100;
                    elozoy = event.button.y/100;
                }
                break;
            /* egergomb elengedese */
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    click = false;
                }
                break;
            /* ablak bezarasa */
            case SDL_QUIT:
                quit = true;
                break;
        }

        if (rajzoltam)
            SDL_RenderPresent(renderer);
    }

    /* nincs mar ra szukseg: felszabaditjuk a memoriat */
    SDL_DestroyTexture(babuk);
    SDL_DestroyTexture(tabla);
    SDL_DestroyTexture(hatter);


    SDL_Quit();
    return 0;
}
