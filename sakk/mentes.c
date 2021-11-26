#include "mentes.h"
#include <stdlib.h>
#include <stdio.h>
#include "fv.h"

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

char babu_pgn(Babu babu){
  if(babu==VBastya||babu==SBastya) return 'R';
  else if(babu==VFuto||babu==SFuto) return 'B';
  else if(babu==VHuszar||babu==SHuszar) return 'N';
  else if(babu==VKiraly||babu==SKiraly) return 'K';
  else if(babu==VVezer||babu==SVezer) return 'Q';
  else return ' ';
}

char int_char(int x){
  if(x=0) return 'a';
  else if(x=1) return 'b';
  else if(x=2) return 'c';
  else if(x=3) return 'd';
  else if(x=4) return 'e';
  else if(x=5) return 'f';
  else if(x=6) return 'g';
  else if(x=7) return 'h';
  else return ' ';
}

void Mentes(ListaElem* ls){
  ListaElem* lista=ls;
  while(lista->kov!=NULL){
    lista=lista->kov;
  }
  ListaElem* lista_e=lista->elo;
  if(lista_e!=NULL){
    while(lista_e->elo!=NULL){
      for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
          if((lista_e->adat[x][y]!=lista->adat[x][y])&&(lista_e->adat[x][y]!=Ures)){
            char lep1[3];
            lep1[0]=babu_pgn(lista_e->adat[x][y]);
            lep1[1]=int_char(x);
            lep1[2]=y;
            lep1[3]='\0';
            printf("%s\n", lep1);
          }
        }
      }
      lista=lista->elo;
      lista_e=lista_e->elo;
    }
  }
}
