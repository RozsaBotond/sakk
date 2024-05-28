#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "fv.h"
#include "lepes.h"
#include "mentes.h"
#include "debugmalloc.h"


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(X+200, Y, &window, &renderer);
    SDL_SetWindowTitle(window, "Sakk");

    /* kep betoltese */
    SDL_Texture *babuk = kep_betolt(renderer, "img/babuk.png");
    SDL_Texture *tabla = kep_betolt(renderer, "img/tabla.png");
    SDL_Texture *hatter = kep_betolt(renderer, "img/negyzet.png");
    SDL_Texture *menu_hatter = kep_betolt(renderer, "img/menu_hatter.png");
    SDL_Texture *mentes_gombok = kep_betolt(renderer, "img/mentes_gombok.png");
    SDL_Texture *also_gombok = kep_betolt(renderer, "img/also_gombok.png");

    Babu sakk_tabla[8][8];
    bool sakk_hatter[8][8];
    bool sakk_utesek[8][8];
    ListaElem *lista=NULL;
    ListaElem *lepeget=NULL;

    //sakk_tabla es sakk_hatter alaphelyzetere allitasa
    alap_tabla(sakk_tabla);
    alap_hatter(sakk_hatter);
    lista = Beszur(lista, sakk_tabla);

    /* rajz keszitese */
    tabla_rajzol(renderer, tabla);
    menu_rajzol(renderer, menu_hatter, also_gombok, mentes_gombok);
    SDL_RenderPresent(renderer);



        /* az esemenyvezerelt hurok */
    bool elpassant_s = false;
    bool elpassant_v = false;
    bool rosal_s = false;
    bool rosal_v = false;
    bool quit = false;
    bool click = false;
    bool babu_cserel = false;
    bool szin_cserel = false;
    Hely cserel;
    int elozox = 0;
    int elozoy = 0;
    bool kivalasztva = false;
    bool feher_lep=true;
    bool feher_matt=false;
    bool fekete_matt=false;
    bool patt=false;
    while (!quit) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        bool rajzoltam = false;
        //kirajzolja a tablat
        tabla_rajzol(renderer, tabla);
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
                    if(babu_cserel){
                      if(event.button.x>800&&event.button.y<33){
                        if(szin_cserel){
                            if(event.button.x>840) sakk_tabla[cserel.x][cserel.y]=VVezer;
                            else if(event.button.x<880) sakk_tabla[cserel.x][cserel.y]=VFuto;
                            else if(event.button.x<920) sakk_tabla[cserel.x][cserel.y]=VHuszar;
                            else if(event.button.x<960) sakk_tabla[cserel.x][cserel.y]=VBastya;
                            else if(event.button.x<1000) sakk_tabla[cserel.x][cserel.y]=VGyalog;
                        }
                        else{
                            if(event.button.x>840) sakk_tabla[cserel.x][cserel.y]=SVezer;
                            else if(event.button.x<880) sakk_tabla[cserel.x][cserel.y]=SFuto;
                            else if(event.button.x<920) sakk_tabla[cserel.x][cserel.y]=SHuszar;
                            else if(event.button.x<960) sakk_tabla[cserel.x][cserel.y]=SBastya;
                            else if(event.button.x<1000) sakk_tabla[cserel.x][cserel.y]=SGyalog;
                        }
                      }
                      babu_cserel=false;
                      lista=Beszur(lista, sakk_tabla);
                    }
                    else{
                        if(t_y>7||t_x>7){
                          if(event.button.y>769&&event.button.y<799){
                            if(event.button.x>900){
                              Beolvas();
                            }
                            else{
                              Mentes(lista);
                            }
                          }
                          else if(event.button.y>739){
                            if(event.button.x<867){
                              free(lista);
                              lista=NULL;
                              alap_tabla(sakk_tabla);
                              lista=Beszur(lista, sakk_tabla);
                            }
                            else if(event.button.x<934){
                              if(lepeget->elo!=NULL){
                                lepeget=Kovetkez(lepeget);
                                Lista_masol(sakk_tabla,lepeget->adat);
                              }
                            }
                            else{
                              if(lepeget->kov!=NULL){
                                lepeget=Elozo(lepeget);
                                Lista_masol(sakk_tabla,lepeget->adat);
                              }
                            }
                          }
                        }
                        else{
                          if(feher_lep){
                            Lista_masol(sakk_tabla, lista->adat);
                            //ha mar kattintottunk mar egy karakterre (kivalasztottuk) akkor igaz lesz
                            if(kivalasztva){
                              if((elozox == t_x) && (elozoy == t_y)){
                                alap_hatter(sakk_hatter);
                                kivalasztva=false;
                              }
                              else{
                                if(sakk_hatter[t_x][t_y]==false){
                                    if(elpassant_v){
                                      sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                                      sakk_tabla[elozox][elozoy]=Ures;
                                      sakk_tabla[t_x][elozoy]=Ures;
                                    }
                                    else if(rosal_v){
                                      if(t_x==0&&t_y==0){
                                        sakk_tabla[0][0]=Ures;
                                        sakk_tabla[1][0]=VKiraly;
                                        sakk_tabla[2][0]=VBastya;
                                        sakk_tabla[3][0]=Ures;
                                      }
                                      if(t_x==7&&t_y==0){
                                        sakk_tabla[3][0]=Ures;
                                        sakk_tabla[4][0]=VBastya;
                                        sakk_tabla[5][0]=VKiraly;
                                        sakk_tabla[6][0]=Ures;
                                        sakk_tabla[7][0]=Ures;
                                      }
                                    }
                                    else{
                                      sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                                      sakk_tabla[elozox][elozoy]=Ures;
                                      if(sakk_tabla[t_x][t_y]==VGyalog&&t_y==7){
                                          babu_kivalszt(renderer, babuk, true);
                                          cserel.x=t_x;
                                          cserel.y=t_y;
                                          babu_cserel=true;
                                          szin_cserel=true;
                                      }
                                    }

                                    lista = Beszur(lista, sakk_tabla);
                                    lepeget=lista;
                                    feher_lep=false;
                                }
                                alap_hatter(sakk_hatter);
                                kivalasztva=false;
                              }
                            }
                            else{
                              alap_hatter(sakk_hatter);
                              if(!sakk_feher(sakk_tabla, lista)){
                                if(matt_feher(sakk_tabla, lista)){
                                  patt=true;
                                }
                                else{
                                  kulonleges_lep lep_v = feher_babu_jolepes(sakk_tabla, sakk_hatter, lista, t_x, t_y);
                                  rosal_v=lep_v.rosal;
                                  elpassant_v=lep_v.elpassant;
                                }
                              }
                              else{
                                if(matt_feher(sakk_tabla, lista)){
                                  feher_matt=true;
                                }
                                else{
                                  feher_babu_jolepes(sakk_tabla, sakk_hatter, lista, t_x, t_y);
                                }
                              }
                              kivalasztva=true;
                            }
                          }
                          else{
                            Lista_masol(sakk_tabla, lista->adat);
                            //ha mar kattintottunk mar egy karakterre (kivalasztottuk) akkor igaz lesz
                            if(kivalasztva){
                              if((elozox == t_x) && (elozoy == t_y)){
                                alap_hatter(sakk_hatter);
                                kivalasztva=false;
                              }
                              else{
                                if(sakk_hatter[t_x][t_y]==false){
                                    if(elpassant_s){
                                      sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                                      sakk_tabla[elozox][elozoy]=Ures;
                                      sakk_tabla[t_x][elozoy]=Ures;
                                    }
                                    else if(rosal_s){
                                        if(t_x==0&&t_y==7){
                                          sakk_tabla[0][7]=Ures;
                                          sakk_tabla[1][7]=SKiraly;
                                          sakk_tabla[2][7]=SBastya;
                                          sakk_tabla[3][7]=Ures;
                                        }
                                        if(t_x==7&&t_y==7){
                                          sakk_tabla[3][7]=Ures;
                                          sakk_tabla[4][7]=SBastya;
                                          sakk_tabla[5][7]=SKiraly;
                                          sakk_tabla[6][7]=Ures;
                                          sakk_tabla[7][7]=Ures;
                                        }
                                    }
                                    else{
                                      sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                                      sakk_tabla[elozox][elozoy]=Ures;
                                      if(sakk_tabla[t_x][t_y]==SGyalog&&t_y==0){
                                          babu_kivalszt(renderer, babuk, false);
                                          cserel.x=t_x;
                                          cserel.y=t_y;
                                          babu_cserel=true;
                                          szin_cserel=false;
                                      }
                                    }
                                    lista = Beszur(lista, sakk_tabla);
                                    lepeget=lista;
                                    feher_lep=true;
                                }
                                alap_hatter(sakk_hatter);
                                kivalasztva=false;
                              }
                            }
                            else{
                              alap_hatter(sakk_hatter);
                              if(!sakk_fekete(sakk_tabla, lista)){
                                if(matt_fekete(sakk_tabla, lista)){
                                  patt=true;
                                }
                                else{
                                  kulonleges_lep lep_s =fekete_babu_jolepes(sakk_tabla, sakk_hatter, lista, t_x, t_y);
                                  rosal_s=lep_s.rosal;
                                  elpassant_s=lep_s.elpassant;
                                }
                              }
                              else{
                                if(matt_fekete(sakk_tabla, lista)){
                                  fekete_matt=true;
                                }
                                else{
                                  fekete_babu_jolepes(sakk_tabla, sakk_hatter, lista, t_x, t_y);
                                }
                              }
                              kivalasztva=true;
                            }
                          }

                        }
                        rajzoltam = true;
                        elozox = event.button.x/100;
                        elozoy = event.button.y/100;
                        if(feher_matt){
                          printf("Feher matt\n");
                        }
                        if(fekete_matt){
                          printf("Fekete matt\n");
                        }
                        if(patt){
                          printf("Patt\n");
                        }

                    }
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
    Felszabadit(lista);


    SDL_Quit();
    return 0;
}
