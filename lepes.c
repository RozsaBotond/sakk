#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include "fv.h"
#include "mentes.h"
#include "lepes.h"
#include "debugmalloc.h"

//sarga kockat jeloli ha üres a tabla kapott
bool jelol_ures(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y) {
  if(sakk_tabla[x][y]==Ures){
    sakk_lep[x][y]=false;
    return true;
  }
  return false;
}
bool jelol_feher(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y) {
  if((sakk_tabla[x][y]==Ures)||(sakk_tabla[x][y]==SKiraly)||(sakk_tabla[x][y]==SVezer)||(sakk_tabla[x][y]==SFuto)||(sakk_tabla[x][y]==SHuszar)||(sakk_tabla[x][y]==SBastya)||(sakk_tabla[x][y]==SGyalog)){
    sakk_lep[x][y]=false;
    return true;
  }
  return false;
}
bool jelol_fekete(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y) {
  if((sakk_tabla[x][y]==Ures)||(sakk_tabla[x][y]==VKiraly)||(sakk_tabla[x][y]==VVezer)||(sakk_tabla[x][y]==VFuto)||(sakk_tabla[x][y]==VHuszar)||(sakk_tabla[x][y]==VBastya)||(sakk_tabla[x][y]==VGyalog)){
    sakk_lep[x][y]=false;
    return true;
  }
  return false;
}
bool jelol_csak_feher(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y) {
  if((sakk_tabla[x][y]==SKiraly)||(sakk_tabla[x][y]==SVezer)||(sakk_tabla[x][y]==SFuto)||(sakk_tabla[x][y]==SHuszar)||(sakk_tabla[x][y]==SBastya)||(sakk_tabla[x][y]==SGyalog)){
    sakk_lep[x][y]=false;
    return true;
  }
  return false;
}
bool jelol_csak_fekete(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y) {
  if((sakk_tabla[x][y]==VKiraly)||(sakk_tabla[x][y]==VVezer)||(sakk_tabla[x][y]==VFuto)||(sakk_tabla[x][y]==VHuszar)||(sakk_tabla[x][y]==VBastya)||(sakk_tabla[x][y]==VGyalog)){
    sakk_lep[x][y]=false;
    return true;
  }
  return false;
}

//A feher kiraly lepes iranyait leirja, és azt a sakk_lep et módosítva mutatja meg.
bool feher_kiraly_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls){
    bool rosal=false;
    if(sakk_tabla[x][y]==VKiraly){
      sakk_lep[x][y]=false;
      if(((x-1)>=0)&&((y+1)<8))       jelol_feher(sakk_tabla, sakk_lep, x-1, y+1);
      if(((x-1)>=0)&&((y-1)>=0))      jelol_feher(sakk_tabla, sakk_lep, x-1, y-1);
      if(((x-1)>=0))                  jelol_feher(sakk_tabla, sakk_lep, x-1, y);
      if(((y-1)>=0))                  jelol_feher(sakk_tabla, sakk_lep, x, y-1);
      if(((y+1)<8))                   jelol_feher(sakk_tabla, sakk_lep, x, y+1);
      if(((x+1)<8))                   jelol_feher(sakk_tabla, sakk_lep, x+1, y);
      if(((x+1)<8)&&((y+1)<8))        jelol_feher(sakk_tabla, sakk_lep, x+1, y+1);
      if(((x+1)<8)&&((y-1)>=0))       jelol_feher(sakk_tabla, sakk_lep, x+1, y-1);
      ListaElem* lista = ls;
      if(lista!=NULL){
        if(sakk_tabla[0][0]==VBastya&&sakk_tabla[1][0]==Ures&&sakk_tabla[2][0]==Ures&&Babu_elmozdult(lista, sakk_tabla, x, y)&&Babu_elmozdult(lista, sakk_tabla, 0, 0)){
          sakk_lep[0][0]=false;
          rosal=true;
        }
        if(sakk_tabla[7][0]==VBastya&&sakk_tabla[6][0]==Ures&&sakk_tabla[5][0]==Ures&&sakk_tabla[4][0]==Ures&&Babu_elmozdult(lista, sakk_tabla, x, y)&&Babu_elmozdult(lista, sakk_tabla, 7, 0)){
          sakk_lep[7][0]=false;
          rosal=true;
        }
      }
    }
    return rosal;
}

//A fekete kiraly lepes iranyait leirja, és azt a sakk_lep et módosítva mutatja meg.
bool fekete_kiraly_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls){
    bool rosal=false;
    if(sakk_tabla[x][y]==SKiraly){
      sakk_lep[x][y]=false;
      if(((x-1)>=0)&&((y+1)<8))       jelol_fekete(sakk_tabla, sakk_lep, x-1, y+1);
      if(((x-1)>=0)&&((y-1)>=0))      jelol_fekete(sakk_tabla, sakk_lep, x-1, y-1);
      if(((x-1)>=0))                  jelol_fekete(sakk_tabla, sakk_lep, x-1, y);
      if(((y-1)>=0))                  jelol_fekete(sakk_tabla, sakk_lep, x, y-1);
      if(((y+1)<8))                   jelol_fekete(sakk_tabla, sakk_lep, x, y+1);
      if(((x+1)<8))                   jelol_fekete(sakk_tabla, sakk_lep, x+1, y);
      if(((x+1)<8)&&((y+1)<8))        jelol_fekete(sakk_tabla, sakk_lep, x+1, y+1);
      if(((x+1)<8)&&((y-1)>=0))       jelol_fekete(sakk_tabla, sakk_lep, x+1, y-1);
      ListaElem* lista = ls;
        if(sakk_tabla[0][7]==SBastya&&sakk_tabla[1][7]==Ures&&sakk_tabla[2][7]==Ures&&Babu_elmozdult(lista, sakk_tabla, x, y)&&Babu_elmozdult(lista, sakk_tabla, 0, 7)){
          sakk_lep[0][7]=false;
          rosal=true;
        }
        if(sakk_tabla[7][7]==SBastya&&sakk_tabla[6][7]==Ures&&sakk_tabla[5][7]==Ures&&sakk_tabla[4][7]==Ures&&Babu_elmozdult(lista, sakk_tabla, x, y)&&Babu_elmozdult(lista, sakk_tabla, 7, 7)){
          sakk_lep[7][7]=false;
          rosal=true;
        }
    }
    return rosal;
}
//A feher gyalogos lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
bool feher_paraszt_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls){
    if(sakk_tabla[x][y]==VGyalog){
      sakk_lep[x][y]=false;
      if((y+1)<8){
        if(y==1&&sakk_tabla[x][2]==Ures&&sakk_tabla[x][3]==Ures){
            jelol_ures(sakk_tabla, sakk_lep, x, y+2);
        }
        jelol_ures(sakk_tabla, sakk_lep, x, y+1);
        jelol_csak_feher(sakk_tabla, sakk_lep, x+1, y+1);
        jelol_csak_feher(sakk_tabla, sakk_lep, x-1, y+1);
        if(sakk_tabla[x+1][y]==SGyalog){
            ListaElem* lista = Elozo(ls);
            if(lista!=NULL){
              if(lista->adat[x+1][6]==SGyalog){
                  sakk_lep[x+1][y+1]=false;
                  return true;
              }
            }
        }
        if(sakk_tabla[x-1][y]==SGyalog){
            ListaElem* lista = Elozo(ls);
            if(lista!=NULL){
              if(lista->adat[x-1][6]==SGyalog){
                  sakk_lep[x-1][y+1]=false;
                  return true;
              }
            }
        }
      }
    }
    return false;
}

//feher parszt utesi
void feher_paraszt_ut (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==VGyalog){
        jelol_csak_feher(sakk_tabla, sakk_lep, x+1, y+1);
        jelol_csak_feher(sakk_tabla, sakk_lep, x-1, y+1);
    }
}

//fekete parszt utesi
void fekete_paraszt_ut (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==SGyalog){
        jelol_csak_fekete(sakk_tabla, sakk_lep, x+1, y-1);
        jelol_csak_fekete(sakk_tabla, sakk_lep, x-1, y-1);
    }
}

//A fekete gyalogos lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
bool fekete_paraszt_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls){
    if(sakk_tabla[x][y]==SGyalog){
      sakk_lep[x][y]=false;
      if((y-1)>=0){
        if(y==6&&sakk_tabla[x][5]==Ures&&sakk_tabla[x][4]==Ures){
            jelol_ures(sakk_tabla, sakk_lep, x, y-2);
        }
        jelol_ures(sakk_tabla, sakk_lep, x, y-1);
        jelol_csak_fekete(sakk_tabla, sakk_lep, x+1, y-1);
        jelol_csak_fekete(sakk_tabla, sakk_lep, x-1, y-1);
        if(sakk_tabla[x+1][y]==VGyalog){
            ListaElem* lista = Elozo(ls);
            if(lista!=NULL){
              if(lista->adat[x+1][1]==VGyalog){
                  sakk_lep[x+1][y-1]=false;
                  return true;
              }
            }
        }
        if(sakk_tabla[x-1][y]==VGyalog){
            ListaElem* lista = Elozo(ls);
            if(lista!=NULL){
              if(lista->adat[x-1][1]==VGyalog){
                  sakk_lep[x-1][y-1]=false;
                  return true;
              }
            }
        }
      }
    }
    return false;
}

//A feher bastya lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void feher_bastya_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==4){
      bool elozo;
      sakk_lep[x][y]=false;
      for(int i = y-1; i >=0; i--){
        if(i==y-1)
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, i)&&jelol_fekete(sakk_tabla, sakk_lep, x, i);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, i)&&!jelol_fekete(sakk_tabla, sakk_lep, x, i)){
              elozo = false;
              sakk_lep[x][i]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, i);
        }
      }
      for(int i = y+1; i <8; i++){
        if(i==y+1)
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, i)&&jelol_fekete(sakk_tabla, sakk_lep, x, i);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, i)&&!jelol_fekete(sakk_tabla, sakk_lep, x, i)){
              elozo = false;
              sakk_lep[x][i]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, i);
        }
      }
      for(int i = x-1; i >=0; i--){
        if(i==x-1)
          elozo = jelol_feher(sakk_tabla, sakk_lep, i, y)&&jelol_fekete(sakk_tabla, sakk_lep, i, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, i, y)&&!jelol_fekete(sakk_tabla, sakk_lep, i, y)){
              elozo = false;
              sakk_lep[i][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, i, y);
        }
      }
      for(int i = x+1; i <8; i++){
        if(i==x+1)
          elozo = jelol_feher(sakk_tabla, sakk_lep, i, y)&&jelol_fekete(sakk_tabla, sakk_lep, i, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, i, y)&&!jelol_fekete(sakk_tabla, sakk_lep, i, y)){
              elozo = false;
              sakk_lep[i][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, i, y);
        }
      }
    }
}

//A fekete bastya lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void fekete_bastya_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==10){
      bool elozo;
      sakk_lep[x][y]=false;
      for(int i = y-1; i >=0; i--){
        if(i==y-1)
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, i)&&jelol_feher(sakk_tabla, sakk_lep, x, i);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, i)&&!jelol_feher(sakk_tabla, sakk_lep, x, i)){
              elozo = false;
              sakk_lep[x][i]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, i);
        }
      }
      for(int i = y+1; i <8; i++){
        if(i==y+1)
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, i)&&jelol_feher(sakk_tabla, sakk_lep, x, i);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, i)&&!jelol_feher(sakk_tabla, sakk_lep, x, i)){
              elozo = false;
              sakk_lep[x][i]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, i);
        }
      }
      for(int i = x-1; i >=0; i--){
        if(i==x-1)
          elozo = jelol_fekete(sakk_tabla, sakk_lep, i, y)&&jelol_feher(sakk_tabla, sakk_lep, i, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, i, y)&&!jelol_feher(sakk_tabla, sakk_lep, i, y)){
              elozo = false;
              sakk_lep[i][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, i, y);
        }
      }
      for(int i = x+1; i <8; i++){
        if(i==x+1)
          elozo = jelol_fekete(sakk_tabla, sakk_lep, i, y)&&jelol_feher(sakk_tabla, sakk_lep, i, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, i, y)&&!jelol_feher(sakk_tabla, sakk_lep, i, y)){
              elozo = false;
              sakk_lep[i][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, i, y);
        }
      }
    }
}

//A feher kiralyno lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void feher_kiralyno_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==1){
      sakk_lep[x][y]=false;
      bool elozo;
      int eredeti_x = x;
      int eredeti_y = y;
      for(int i = y-1; i >=0; i--){
        if(i==y-1)
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, i)&&jelol_fekete(sakk_tabla, sakk_lep, x, i);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, i)&&!jelol_fekete(sakk_tabla, sakk_lep, x, i)){
              elozo = false;
              sakk_lep[x][i]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, i);
        }
      }
      for(int i = y+1; i <8; i++){
        if(i==y+1)
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, i)&&jelol_fekete(sakk_tabla, sakk_lep, x, i);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, i)&&!jelol_fekete(sakk_tabla, sakk_lep, x, i)){
              elozo = false;
              sakk_lep[x][i]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, i);
        }
      }
      for(int i = x-1; i >=0; i--){
        if(i==x-1)
          elozo = jelol_feher(sakk_tabla, sakk_lep, i, y)&&jelol_fekete(sakk_tabla, sakk_lep, i, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, i, y)&&!jelol_fekete(sakk_tabla, sakk_lep, i, y)){
              elozo = false;
              sakk_lep[i][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, i, y);
        }
      }
      for(int i = x+1; i <8; i++){
        if(i==x+1)
          elozo = jelol_feher(sakk_tabla, sakk_lep, i, y)&&jelol_fekete(sakk_tabla, sakk_lep, i, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, i, y)&&!jelol_fekete(sakk_tabla, sakk_lep, i, y)){
              elozo = false;
              sakk_lep[i][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, i, y);
        }
      }
      while((x<8)&&(y<8)){
        if((x==eredeti_x+1)&&(y==eredeti_y+1))
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, y)&&jelol_fekete(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, y)&&!jelol_fekete(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, y);
        }
        x++;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x<8)&&(y>-1)){
        if((x==eredeti_x+1)&&(y==eredeti_y-1))
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, y)&&jelol_fekete(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, y)&&!jelol_fekete(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, y);
        }
        x++;
        y--;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y<8)){
        if((x==eredeti_x-1)&&(y==eredeti_y+1))
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, y)&&jelol_fekete(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, y)&&!jelol_fekete(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, y);
        }
        x--;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y>-1)){
        if((x==eredeti_x-1)&&(y==eredeti_y-1))
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, y)&&jelol_fekete(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, y)&&!jelol_fekete(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, y);
        }
        x--;
        y--;
      }
    }
}

//A fekete kiralyno lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void fekete_kiralyno_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==7){
      sakk_lep[x][y]=false;
      bool elozo;
      int eredeti_x = x;
      int eredeti_y = y;
      for(int i = y-1; i >=0; i--){
        if(i==y-1)
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, i)&&jelol_feher(sakk_tabla, sakk_lep, x, i);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, i)&&!jelol_feher(sakk_tabla, sakk_lep, x, i)){
              elozo = false;
              sakk_lep[x][i]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, i);
        }
      }
      for(int i = y+1; i <8; i++){
        if(i==y+1)
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, i)&&jelol_feher(sakk_tabla, sakk_lep, x, i);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, i)&&!jelol_feher(sakk_tabla, sakk_lep, x, i)){
              elozo = false;
              sakk_lep[x][i]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, i);
        }
      }
      for(int i = x-1; i >=0; i--){
        if(i==x-1)
          elozo = jelol_fekete(sakk_tabla, sakk_lep, i, y)&&jelol_feher(sakk_tabla, sakk_lep, i, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, i, y)&&!jelol_feher(sakk_tabla, sakk_lep, i, y)){
              elozo = false;
              sakk_lep[i][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, i, y);
        }
      }
      for(int i = x+1; i <8; i++){
        if(i==x+1)
          elozo = jelol_fekete(sakk_tabla, sakk_lep, i, y)&&jelol_feher(sakk_tabla, sakk_lep, i, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, i, y)&&!jelol_feher(sakk_tabla, sakk_lep, i, y)){
              elozo = false;
              sakk_lep[i][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, i, y);
        }
      }
      while((x<8)&&(y<8)){
        if((x==eredeti_x+1)&&(y==eredeti_y+1))
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y)&&jelol_feher(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, y)&&!jelol_feher(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y);
        }
        x++;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x<8)&&(y>-1)){
        if((x==eredeti_x+1)&&(y==eredeti_y-1))
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y)&&jelol_feher(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, y)&&!jelol_feher(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y);
        }
        x++;
        y--;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y<8)){
        if((x==eredeti_x-1)&&(y==eredeti_y+1))
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y)&&jelol_feher(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, y)&&!jelol_feher(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y);
        }
        x--;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y>-1)){
        if((x==eredeti_x-1)&&(y==eredeti_y-1))
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y)&&jelol_feher(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, y)&&!jelol_feher(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y);
        }
        x--;
        y--;
      }
    }
}
//A fekete futo lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void fekete_futo_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==8){
      sakk_lep[x][y]=false;
      bool elozo;
      int eredeti_x = x;
      int eredeti_y = y;
      while((x<8)&&(y<8)){
        if((x==eredeti_x+1)&&(y==eredeti_y+1))
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y)&&jelol_feher(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, y)&&!jelol_feher(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y);
        }
        x++;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x<8)&&(y>-1)){
        if((x==eredeti_x+1)&&(y==eredeti_y-1))
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y)&&jelol_feher(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, y)&&!jelol_feher(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y);
        }
        x++;
        y--;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y<8)){
        if((x==eredeti_x-1)&&(y==eredeti_y+1))
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y)&&jelol_feher(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, y)&&!jelol_feher(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y);
        }
        x--;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y>-1)){
        if((x==eredeti_x-1)&&(y==eredeti_y-1))
          elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y)&&jelol_feher(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_fekete(sakk_tabla, sakk_lep, x, y)&&!jelol_feher(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_fekete(sakk_tabla, sakk_lep, x, y);
        }
        x--;
        y--;
      }
    }
}

//A feher futo lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void feher_futo_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==2){
      sakk_lep[x][y]=false;
      bool elozo;
      int eredeti_x = x;
      int eredeti_y = y;
      while((x<8)&&(y<8)){
        if((x==eredeti_x+1)&&(y==eredeti_y+1))
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, y)&&jelol_fekete(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, y)&&!jelol_fekete(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, y);
        }
        x++;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x<8)&&(y>-1)){
        if((x==eredeti_x+1)&&(y==eredeti_y-1))
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, y)&&!jelol_fekete(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, y);
        }
        x++;
        y--;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y<8)){
        if((x==eredeti_x-1)&&(y==eredeti_y+1))
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, y)&&!jelol_fekete(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, y);
        }
        x--;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y>-1)){
        if((x==eredeti_x-1)&&(y==eredeti_y-1))
          elozo = jelol_feher(sakk_tabla, sakk_lep, x, y)&&jelol_fekete(sakk_tabla, sakk_lep, x, y);
        else{
          if(elozo&&jelol_feher(sakk_tabla, sakk_lep, x, y)&&!jelol_fekete(sakk_tabla, sakk_lep, x, y)){
              elozo = false;
              sakk_lep[x][y]=false;
          }
          else if(elozo)
            elozo = jelol_feher(sakk_tabla, sakk_lep, x, y);
        }
        x--;
        y--;
      }
    }
}

//A feher huszar lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void feher_huszar_lep(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
  if(sakk_tabla[x][y]==3){
    sakk_lep[x][y]=false;
    if(((x+1)<8)&&((y+2)<8))  jelol_feher(sakk_tabla, sakk_lep, x+1, y+2);
    if(((x-1)>=0)&&((y+2)<8)) jelol_feher(sakk_tabla, sakk_lep, x-1, y+2);
    if(((x+2)<8)&&((y+1)<8))  jelol_feher(sakk_tabla, sakk_lep, x+2, y+1);
    if(((x+2)<8)&&((y-1)>=0)) jelol_feher(sakk_tabla, sakk_lep, x+2, y-1);
    if(((x+1)<8)&&((y-2)>=0)) jelol_feher(sakk_tabla, sakk_lep, x+1, y-2);
    if(((x-1)>=0)&&((y-2)>=0))jelol_feher(sakk_tabla, sakk_lep, x-1, y-2);
    if(((x-2)>=0)&&((y+1)<8)) jelol_feher(sakk_tabla, sakk_lep, x-2, y+1);
    if(((x-2)>=0)&&((y-1)>=0))jelol_feher(sakk_tabla, sakk_lep, x-2, y-1);
  }
}

//A fekete huszar lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void fekete_huszar_lep(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
  if(sakk_tabla[x][y]==9){
    sakk_lep[x][y]=false;
    if(((x+1)<8)&&((y+2)<8))  jelol_fekete(sakk_tabla, sakk_lep, x+1, y+2);
    if(((x-1)>=0)&&((y+2)<8)) jelol_fekete(sakk_tabla, sakk_lep, x-1, y+2);
    if(((x+2)<8)&&((y+1)<8))  jelol_fekete(sakk_tabla, sakk_lep, x+2, y+1);
    if(((x+2)<8)&&((y-1)>=0)) jelol_fekete(sakk_tabla, sakk_lep, x+2, y-1);
    if(((x+1)<8)&&((y-2)>=0)) jelol_fekete(sakk_tabla, sakk_lep, x+1, y-2);
    if(((x-1)>=0)&&((y-2)>=0))jelol_fekete(sakk_tabla, sakk_lep, x-1, y-2);
    if(((x-2)>=0)&&((y+1)<8)) jelol_fekete(sakk_tabla, sakk_lep, x-2, y+1);
    if(((x-2)>=0)&&((y-1)>=0))jelol_fekete(sakk_tabla, sakk_lep, x-2, y-1);
  }
}

//feher lepesi mezo
kulonleges_lep feher_lepes_mezo(Babu sakk_tabla[8][8], bool sakk_lep[8][8], ListaElem* lista, int i, int j){
      kulonleges_lep lep;
      feher_huszar_lep(sakk_tabla, sakk_lep, i, j);
      feher_kiralyno_lep(sakk_tabla, sakk_lep, i, j);
      feher_futo_lep(sakk_tabla, sakk_lep, i, j);
      feher_bastya_lep(sakk_tabla, sakk_lep, i, j);
      lep.rosal = feher_kiraly_lep(sakk_tabla, sakk_lep, i, j, lista);
      lep.elpassant = feher_paraszt_lep(sakk_tabla, sakk_lep, i, j, lista);
}

//feher utesi mezo
void feher_utes_mezo(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int i, int j){
      feher_huszar_lep(sakk_tabla, sakk_lep, i, j);
      feher_kiralyno_lep(sakk_tabla, sakk_lep, i, j);
      feher_futo_lep(sakk_tabla, sakk_lep, i, j);
      feher_bastya_lep(sakk_tabla, sakk_lep, i, j);
      feher_kiraly_lep(sakk_tabla, sakk_lep, i, j, NULL);
      feher_paraszt_ut(sakk_tabla, sakk_lep, i, j);
}
//fekete utesi mezo
kulonleges_lep fekete_lepes_mezo(Babu sakk_tabla[8][8], bool sakk_lep[8][8], ListaElem* lista, int i, int j){
      kulonleges_lep lep;
      fekete_huszar_lep(sakk_tabla, sakk_lep, i, j);
      fekete_kiralyno_lep(sakk_tabla, sakk_lep, i, j);
      fekete_futo_lep(sakk_tabla, sakk_lep, i, j);
      fekete_bastya_lep(sakk_tabla, sakk_lep, i, j);
      fekete_kiraly_lep(sakk_tabla, sakk_lep, i, j, lista);
      lep.rosal = fekete_kiraly_lep(sakk_tabla, sakk_lep, i, j, lista);
      lep.elpassant = fekete_paraszt_lep(sakk_tabla, sakk_lep, i, j, lista);
}
//feher utesi mezo
void fekete_utes_mezo(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int i, int j){
      fekete_huszar_lep(sakk_tabla, sakk_lep, i, j);
      fekete_kiralyno_lep(sakk_tabla, sakk_lep, i, j);
      fekete_futo_lep(sakk_tabla, sakk_lep, i, j);
      fekete_bastya_lep(sakk_tabla, sakk_lep, i, j);
      fekete_kiraly_lep(sakk_tabla, sakk_lep, i, j, NULL);
      fekete_paraszt_ut(sakk_tabla, sakk_lep, i, j);
}

//feher kiraly lepesi teruletei
Hely feher_kiraly_terulete(Babu sakk_tabla[8][8]){
  Hely hol;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if(sakk_tabla[i][j]==VKiraly){
          hol.x=i;
          hol.y=j;
      }
    }
  }

  return hol;
}

//fekete kiraly lepesi teruletei
Hely fekete_kiraly_terulete(Babu sakk_tabla[8][8]){
  Hely hol;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if(sakk_tabla[i][j]==SKiraly){
          hol.x=i;
          hol.y=j;
      }
    }
  }

  return hol;
}

bool sakk_feher(Babu sakk_tabla[8][8], ListaElem* lista){
  bool sakk_lep[8][8];
  alap_hatter(sakk_lep);
  Hely hol = feher_kiraly_terulete(sakk_tabla);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      fekete_utes_mezo(sakk_tabla, sakk_lep, i , j);
    }
  }
  if(sakk_lep[hol.x][hol.y]==false){
    alap_hatter(sakk_lep);
    return true;
  }
  alap_hatter(sakk_lep);
  return false;
}

//sakk
bool sakk_fekete(Babu sakk_tabla[8][8], ListaElem* lista){
  bool sakk_lep[8][8];
  alap_hatter(sakk_lep);
  Hely hol = fekete_kiraly_terulete(sakk_tabla);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      feher_utes_mezo(sakk_tabla, sakk_lep, i , j);
    }
  }
  if(sakk_lep[hol.x][hol.y]==false){
    alap_hatter(sakk_lep);
    return true;
  }
  alap_hatter(sakk_lep);
  return false;
}

void hatter_masol(bool adat[8][8], bool masolando[8][8]){
    for(int x = 0; x < 8; x++){
      for(int y = 0; y < 8; y++){
        adat[x][y]=masolando[x][y];
      }
    }
}

bool hatter_metszet(bool adat[8][8], bool masolando[8][8]){
    for(int x = 0; x < 8; x++){
      for(int y = 0; y < 8; y++){
        if(adat[x][y]==masolando[x][y]){
          return false;
        }
      }
    }
    return true;
}

//osszes babu mento lepesit irja ki a jo lepesbe
kulonleges_lep feher_babu_jolepes(Babu sakk_tabla[8][8], bool jolepes[8][8], ListaElem* lista, int i, int j){
        bool sakk=sakk_feher(sakk_tabla, NULL);
        kulonleges_lep vissza_ad;
        vissza_ad.elpassant=false;
        vissza_ad.rosal=false;
        bool sakk_lep[8][8];
        alap_hatter(jolepes);
        alap_hatter(sakk_lep);
        kulonleges_lep lep=feher_lepes_mezo(sakk_tabla, sakk_lep, lista, i , j);
        int elozox=i;
        int elozoy=j;
        for (int t_x = 0; t_x < 8; t_x++) {
          for (int t_y = 0; t_y < 8; t_y++) {
            if(sakk_lep[t_x][t_y]==false){
                if (lep.elpassant){
                  vissza_ad.elpassant=true;
                  sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                  sakk_tabla[elozox][elozoy]=Ures;
                  sakk_tabla[t_x][elozoy]=Ures;
                }
                else if((!sakk&&lep.rosal&&!sakk_lep[3][7]&&!sakk_lep[2][7]&&!sakk_lep[1][7])||(!sakk&&lep.rosal&&!sakk_lep[3][7]&&!sakk_lep[4][7]&&!sakk_lep[5][7])){
                  vissza_ad.rosal=true;
                  vissza_ad.elpassant=false;
                }
                else{
                  sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                  sakk_tabla[elozox][elozoy]=Ures;
                }

                if(!sakk_feher(sakk_tabla, NULL)){
                  jolepes[t_x][t_y]=false;
                }

                hatter_metszet(jolepes, sakk_lep);

                Lista_masol(sakk_tabla, lista->adat);
            }
          }
        }
        return vissza_ad;
}


//osszes babu mento lepesit irja ki a jo lepesbe
kulonleges_lep fekete_babu_jolepes(Babu sakk_tabla[8][8], bool jolepes[8][8], ListaElem* lista, int i, int j){
        bool sakk=sakk_fekete(sakk_tabla, NULL);
        kulonleges_lep vissza_ad;
        vissza_ad.elpassant=false;
        vissza_ad.rosal=false;

        bool sakk_lep[8][8];
        alap_hatter(jolepes);
        alap_hatter(sakk_lep);
        kulonleges_lep lep=fekete_lepes_mezo(sakk_tabla, sakk_lep, lista, i ,j);
        int elozox=i;
        int elozoy=j;
        for (int t_x = 0; t_x < 8; t_x++) {
          for (int t_y = 0; t_y < 8; t_y++) {
            if(sakk_lep[t_x][t_y]==false){
                if (lep.elpassant){
                  vissza_ad.elpassant=false;
                  sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                  sakk_tabla[elozox][elozoy]=Ures;
                  sakk_tabla[t_x][elozoy]=Ures;
                }
                else if((!sakk&&lep.rosal&&!sakk_lep[3][7]&&!sakk_lep[2][7]&&!sakk_lep[1][7])||(!sakk&&lep.rosal&&!sakk_lep[3][7]&&!sakk_lep[4][7]&&!sakk_lep[5][7])){
                  vissza_ad.rosal=true;
                  vissza_ad.elpassant=false;

                }
                else{
                  sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                  sakk_tabla[elozox][elozoy]=Ures;
                }

                if(!sakk_fekete(sakk_tabla, NULL)){
                  jolepes[t_x][t_y]=false;
                }

                hatter_metszet(jolepes, sakk_lep);
                Lista_masol(sakk_tabla, lista->adat);
            }
          }
        }
        return vissza_ad;
}

bool matt_fekete(Babu sakk_tabla[8][8], ListaElem* lista){
        ListaElem* ls = lista;
        bool jolepes[8][8];
        for(int i = 0; i < 8; i++) {
          for(int j = 0; j < 8; j++) {
            feher_babu_jolepes(sakk_tabla, jolepes, ls, i, j);
            for(int x = 0; x < 8; x++) {
              for(int y = 0; y < 8; y++) {
                if(!jolepes[x][y]){
                  return false;
                }
              }
            }
          }
        }
        return true;
}


bool matt_feher(Babu sakk_tabla[8][8], ListaElem* lista){
        ListaElem* ls = lista;
        bool jolepes[8][8];
        for(int i = 0; i < 8; i++) {
          for(int j = 0; j < 8; j++) {
            feher_babu_jolepes(sakk_tabla, jolepes, ls, i, j);
            for(int x = 0; x < 8; x++) {
              for(int y = 0; y < 8; y++) {
                if(!jolepes[x][y]){
                  return false;
                }
              }
            }
          }
        }
        return true;
  }
