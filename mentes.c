#include "mentes.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include "fv.h"
#include "lepes.h"
#include <regex.h>

void Lista_masol(Babu adat[8][8], Babu masolando[8][8]){
    for(int x = 0; x < 8; x++){
      for(int y = 0; y < 8; y++){
        adat[x][y]=masolando[x][y];
      }
    }
}

bool Lista_hasonlit(Babu adat[8][8], Babu masolando[8][8]){
    for(int x = 0; x < 8; x++){
      for(int y = 0; y < 8; y++){
        if(adat[x][y]!=masolando[x][y]){
          return false;
        }
      }
    }
    return true;
}

ListaElem* Beszur(ListaElem* lista, Babu adat[8][8]){
  ListaElem* uj = (ListaElem*) malloc(sizeof(ListaElem));
  Lista_masol(uj->adat, adat);
  uj -> kov = lista;
  uj -> elo = NULL;
  if(lista!=NULL)
    lista -> elo = uj;
  lista = uj;
  return lista;
}

ListaElem* Beszur_vege(ListaElem* lista, Babu adat[8][8]){
    if(lista==NULL){
      lista = Beszur(lista, adat);
      return lista;
    }

    ListaElem *e = lista->kov;
    ListaElem *h = lista;

    if(e==NULL){
      ListaElem* uj = (ListaElem*) malloc(sizeof(ListaElem));
      uj -> kov = e;
      uj -> elo = h;
      Lista_masol(uj->adat, adat);
      h -> kov = uj;
      return lista;
    }


    while(e->kov!=NULL){
      h=h->kov;
      e=e->kov;
    }
    ListaElem* uj = (ListaElem*) malloc(sizeof(ListaElem));
    uj -> kov = NULL;
    Lista_masol(uj->adat, adat);
    e -> kov = uj;
    uj -> elo = e;
    return lista;
}

int Meret_szamol(ListaElem* lista){
    int m = 0;
    ListaElem* p = lista;
    while(p!=NULL){
      p = p->kov;
      m++;
    }
    return m;
}



void Felszabadit(ListaElem* lista){
    if(lista!=NULL){
        ListaElem* h = lista;
        ListaElem* e = lista->kov;
        while(e!=NULL){
          free(h);
          h=e;
          e=e->kov;
        }
    }
}

ListaElem* Keres(ListaElem* ls, Babu adat[8][8]){
    ListaElem* lista = ls;
    while(!Lista_hasonlit(lista->adat, adat)&&(lista->kov!=NULL)){
        lista=lista->kov;
    }
    return lista;
}

bool Babu_elmozdult(ListaElem* ls, Babu adat[8][8], int x, int y){
    ListaElem* lista = ls;
    while((lista!=NULL)){
        if(lista->adat[x][y]!=adat[x][y]){
          return false;
        }
        lista=lista->kov;
    }
    return true;
}

ListaElem* Elozo(ListaElem* ls){
  if(ls!=NULL){
    ListaElem* lista = ls;
    return lista->kov;
  }
  return NULL;
}
ListaElem* Kovetkez(ListaElem* ls){
  if(ls!=NULL){
    ListaElem* lista = ls;
    return lista->elo;
  }
  return NULL;
}

char babu_pgn(Babu babu){
  if(babu==VBastya||babu==SBastya) return 'R';
  else if(babu==VFuto||babu==SFuto) return 'B';
  else if(babu==VHuszar||babu==SHuszar) return 'N';
  else if(babu==VKiraly||babu==SKiraly) return 'K';
  else if(babu==VVezer||babu==SVezer) return 'Q';
  else return ' ';
}

char int_char(int x){
  if(x==0) return 'a';
  else if(x==1) return 'b';
  else if(x==2) return 'c';
  else if(x==3) return 'd';
  else if(x==4) return 'e';
  else if(x==5) return 'f';
  else if(x==6) return 'g';
  else if(x==7) return 'h';
  else return ' ';
}

bool ki_mentes(char* irando){
    char* hely="./mentes/mentett.pgn";
    if (remove(hely) != 0) {
      return false;
    }
    FILE *f=fopen(hely, "a");
    if(f==NULL)
      return false;
    fprintf(f, "%s ", irando);
    fclose(f);
    return true;

}

void Mentes(ListaElem* ls){
  bool rosal=false;
  bool f_lep=true;
  int lepes=1;
  ListaElem* lista=ls;
  while(lista->kov!=NULL){
    lista=lista->kov;
  }
  if(lista->elo!=NULL){
    ListaElem* lista_e=lista->elo;
    while(lista_e!=NULL){
      for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
          bool mindegy[8][8];
          if(f_lep){
            if(lista_e->adat[x][y]==VKiraly&&lista_e->adat[1][0]==VKiraly){
              char buff[25]="";
              sprintf(buff, "%d. 0-0", lepes);

              ki_mentes(buff);
              lepes++;
              f_lep=false;
              rosal=true;
            }
            else if(lista_e->adat[x][y]==VKiraly&&lista_e->adat[5][0]==VKiraly){
              char buff[25]="";
              sprintf(buff, "%d. 0-0-0", lepes);

              ki_mentes(buff);
              lepes++;
              f_lep=false;
              rosal=true;
            }
            else if((lista_e->adat[x][y]!=lista->adat[x][y])&&jelol_csak_feher(lista_e->adat, mindegy, x, y)){
              if(!rosal){
                char buff[25]="";
                if(lista->adat[x][y]!=Ures){
                  sprintf(buff, "%d. %c%c%d", lepes, babu_pgn(lista_e->adat[x][y]), int_char(x), y);
                }
                else{
                  sprintf(buff, "%d. %c%c%d", lepes, babu_pgn(lista_e->adat[x][y]), int_char(x), y);
                }
                printf("%s ", buff);

                ki_mentes(buff);
                lepes++;
                f_lep=false;
                rosal=false;
              }
              else if(lista_e->adat[x][y]==VBastya||lista_e->adat[x][y]==VKiraly){
                char buff[25]="";
                if(lista->adat[x][y]!=Ures){
                  sprintf(buff, "%d. %c%c%d", lepes, babu_pgn(lista_e->adat[x][y]), int_char(x), y);
                }
                else{
                  sprintf(buff, "%d. %c%c%d", lepes, babu_pgn(lista_e->adat[x][y]), int_char(x), y);
                }
                printf("%s ", buff);

                ki_mentes(buff);
                lepes++;
                f_lep=false;
                rosal=false;
              }
            }
          }
          else{
            if(lista_e->adat[x][y]==SKiraly&&lista_e->adat[5][7]==SKiraly){
              ki_mentes("0-0");
              f_lep=true;
              rosal=true;
            }
            else if(lista_e->adat[x][y]==SKiraly&&lista_e->adat[1][7]==SKiraly){
              ki_mentes("0-0-0");
              f_lep=true;
              rosal=true;
            }
            else if((lista_e->adat[x][y]!=lista->adat[x][y])&&jelol_csak_fekete(lista_e->adat, mindegy, x, y)){
              if(!rosal){
                char buff[25]="";
                sprintf(buff, "%c%c%d", babu_pgn(lista_e->adat[x][y]), int_char(x), y);
                printf("%s\n", buff);

                ki_mentes(buff);
                f_lep=true;
                rosal=false;
              }
              else if(lista_e->adat[x][y]==SBastya||lista_e->adat[x][y]==SKiraly){
                char buff[25]="";
                sprintf(buff, "%c%c%d", babu_pgn(lista_e->adat[x][y]), int_char(x), y);
                printf("%s\n", buff);

                ki_mentes(buff);
                f_lep=true;
                rosal=false;
              }
            }
          }
        }
      }
      lista=lista->elo;
      lista_e=lista_e->elo;
  }

  }
}

void Beolvas(void){
  char* hely="./beolvas/beolvasando.pgn";
  FILE *f = fopen(hely, "r");
  if(f==NULL){
    printf("Nincs vagy nem jol van megadva a beolvasando fajl\n");
    printf("beolvasando.pgn neven mentse el a beolvas mappaba\n");
  }
  char * sor = NULL;
  size_t hossz = 500;

      while ((getline(&sor, &hossz, f)!=EOF)) {
          if (sor[0]!='[') {
            printf("%s", sor);
          }
      }
  fclose(f);
}
