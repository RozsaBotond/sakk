#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include "fv.h"
#include "mentes.h"
#include "lepes.h"

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
    if(sakk_tabla[x][y]==0){
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
      if(sakk_tabla[0][0]==VBastya&&sakk_tabla[1][0]==Ures&&sakk_tabla[2][0]==Ures&&Babu_elmozdult(lista, sakk_tabla, x, y)&&Babu_elmozdult(lista, sakk_tabla, 0, 0)){
        sakk_lep[0][0]=false;
        rosal=true;
      }
      if(sakk_tabla[7][0]==VBastya&&sakk_tabla[6][0]==Ures&&sakk_tabla[5][0]==Ures&&sakk_tabla[4][0]==Ures&&Babu_elmozdult(lista, sakk_tabla, x, y)&&Babu_elmozdult(lista, sakk_tabla, 7, 0)){
        sakk_lep[7][0]=false;
        rosal=true;
      }
    }
    return rosal;
}

//A fekete kiraly lepes iranyait leirja, és azt a sakk_lep et módosítva mutatja meg.
bool fekete_kiraly_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls){
    bool rosal=false;
    if(sakk_tabla[x][y]==6){
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

//A feher gyalogos utes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
bool feher_paraszt_ut (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls){
    if(sakk_tabla[x][y]==5){
      if((y+1)<8){
        jelol_csak_feher(sakk_tabla, sakk_lep, x+1, y+1);
        jelol_csak_feher(sakk_tabla, sakk_lep, x-1, y+1);
      }
    }
    return false;
}
//A fekete gyalogos utes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
bool fekete_paraszt_ut (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls){
    if(sakk_tabla[x][y]==11){
      if((y+1)<8){
        jelol_csak_fekete(sakk_tabla, sakk_lep, x+1, y+1);
        jelol_csak_fekete(sakk_tabla, sakk_lep, x-1, y+1);
      }
    }
    return false;
}
//A feher gyalogos lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
bool feher_paraszt_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls){
    if(sakk_tabla[x][y]==5){
      sakk_lep[x][y]=false;
      if((y+1)<8){
        if(y==1){
            jelol_ures(sakk_tabla, sakk_lep, x, y+2);
        }
        jelol_ures(sakk_tabla, sakk_lep, x, y+1);
        jelol_csak_feher(sakk_tabla, sakk_lep, x+1, y+1);
        jelol_csak_feher(sakk_tabla, sakk_lep, x-1, y+1);
        if(sakk_tabla[x+1][y]==11){
            ListaElem* lista = Elozo(ls);
            if(lista!=NULL){
              if(lista->adat[x+1][6]==11){
                  sakk_lep[x+1][y+1]=false;
                  return true;
              }
            }
        }
        if(sakk_tabla[x-1][y]==11){
            ListaElem* lista = Elozo(ls);
            if(lista!=NULL){
              if(lista->adat[x-1][6]==11){
                  sakk_lep[x-1][y+1]=false;
                  return true;
              }
            }
        }
      }
    }
    return false;
}
//A fekete gyalogos lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
bool fekete_paraszt_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y, ListaElem* ls){
    if(sakk_tabla[x][y]==11){
      sakk_lep[x][y]=false;
      if((y-1)>=0){
        if(y==6){
            jelol_ures(sakk_tabla, sakk_lep, x, y-2);
        }
        jelol_ures(sakk_tabla, sakk_lep, x, y-1);
        jelol_csak_fekete(sakk_tabla, sakk_lep, x+1, y-1);
        jelol_csak_fekete(sakk_tabla, sakk_lep, x-1, y-1);
        if(sakk_tabla[x+1][y]==5){
            ListaElem* lista = Elozo(ls);
            if(lista!=NULL){
              if(lista->adat[x+1][1]==5){
                  sakk_lep[x+1][y-1]=false;
                  return true;
              }
            }
        }
        if(sakk_tabla[x-1][y]==5){
            ListaElem* lista = Elozo(ls);
            if(lista!=NULL){
              if(lista->adat[x-1][1]==5){
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

//feher utesi mezo
void feher_utes_mezo(Babu sakk_tabla[8][8], bool sakk_lep[8][8]){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      feher_huszar_lep(sakk_tabla, sakk_lep, i, j);
      feher_kiralyno_lep(sakk_tabla, sakk_lep, i, j);
      feher_futo_lep(sakk_tabla, sakk_lep, i, j);
      feher_bastya_lep(sakk_tabla, sakk_lep, i, j);
      feher_kiraly_lep(sakk_tabla, sakk_lep, i, j, NULL);
      feher_paraszt_lep(sakk_tabla, sakk_lep, i, j, NULL);
    }
  }
}

//fekete utesi mezo
void fekete_utes_mezo(Babu sakk_tabla[8][8], bool sakk_lep[8][8]){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      fekete_huszar_lep(sakk_tabla, sakk_lep, i, j);
      fekete_kiralyno_lep(sakk_tabla, sakk_lep, i, j);
      fekete_futo_lep(sakk_tabla, sakk_lep, i, j);
      fekete_bastya_lep(sakk_tabla, sakk_lep, i, j);
      fekete_kiraly_lep(sakk_tabla, sakk_lep, i, j, NULL);
      fekete_paraszt_lep(sakk_tabla, sakk_lep, i, j, NULL);
    }
  }
}

typedef struct{
  int x;
  int y;
} Hely;

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

//osszehasonlit es a jo lepeseket
void kiraly_jolepes(bool kiraly_lep[8][8], bool sakk_lep[8][8]){
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if(kiraly_lep[i][j]==false&&sakk_lep[i][j]==true){
        kiraly_lep[i][j]=false;
      }
      else{
        kiraly_lep[i][j]=true;
      }
    }
  }
}

//sakk
bool sakk_feher(Babu sakk_tabla[8][8], bool sakk_lep[8][8]){
  fekete_utes_mezo(sakk_tabla, sakk_lep);
  Hely hol = feher_kiraly_terulete(sakk_tabla);
  if(sakk_lep[hol.x][hol.y]==false){
    alap_hatter(sakk_lep);
    return true;
  }
  alap_hatter(sakk_lep);
  return false;
}

//sakk
bool sakk_fekete(Babu sakk_tabla[8][8], bool sakk_lep[8][8]){
  feher_utes_mezo(sakk_tabla, sakk_lep);
  Hely hol = fekete_kiraly_terulete(sakk_tabla);
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

//osszes babu mento lepesit irja ki a jo lepesbe
void feher_babu_jolepes(Babu sakk_tabla[8][8], bool jolepes[8][8], ListaElem* lista, int i, int j){
        bool sakk_lep[8][8];
        alap_hatter(jolepes);
        alap_hatter(sakk_lep);
        feher_huszar_lep(sakk_tabla, sakk_lep, i, j);
        feher_kiralyno_lep(sakk_tabla, sakk_lep, i, j);
        feher_futo_lep(sakk_tabla, sakk_lep, i, j);
        feher_bastya_lep(sakk_tabla, sakk_lep, i, j);
        feher_kiraly_lep(sakk_tabla, sakk_lep, i, j, lista);
        bool elpassant_v=feher_paraszt_lep(sakk_tabla, sakk_lep, i, j, lista);
        int elozox=i;
        int elozoy=j;
        for (int t_x = 0; t_x < 8; t_x++) {
          for (int t_y = 0; t_y < 8; t_y++) {
            if(sakk_lep[t_x][t_y]==false){
                if (elpassant_v){
                  sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                  sakk_tabla[elozox][elozoy]=Ures;
                  sakk_tabla[t_x][elozoy]=Ures;
                }
                else{
                  sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                  sakk_tabla[elozox][elozoy]=Ures;
                }
                bool sakk_hatter[8][8];
                hatter_masol(sakk_hatter, sakk_lep);

                if(sakk_feher(sakk_tabla, sakk_hatter)==false){
                    jolepes[t_x][t_y]=false;
                }

                Lista_masol(sakk_tabla, lista->adat);
            }
          }
        }
}


//osszes babu mento lepesit irja ki a jo lepesbe
void fekete_babu_jolepes(Babu sakk_tabla[8][8], bool jolepes[8][8], ListaElem* lista, int i, int j){
        bool sakk_lep[8][8];
        alap_hatter(jolepes);
        alap_hatter(sakk_lep);
        fekete_huszar_lep(sakk_tabla, sakk_lep, i, j);
        fekete_kiralyno_lep(sakk_tabla, sakk_lep, i, j);
        fekete_futo_lep(sakk_tabla, sakk_lep, i, j);
        fekete_bastya_lep(sakk_tabla, sakk_lep, i, j);
        fekete_kiraly_lep(sakk_tabla, sakk_lep, i, j, lista);
        bool elpassant_s=feher_paraszt_lep(sakk_tabla, sakk_lep, i, j, lista);
        int elozox=i;
        int elozoy=j;
        for (int t_x = 0; t_x < 8; t_x++) {
          for (int t_y = 0; t_y < 8; t_y++) {
            if(sakk_lep[t_x][t_y]==false){
                if (elpassant_s){
                  sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                  sakk_tabla[elozox][elozoy]=Ures;
                  sakk_tabla[t_x][elozoy]=Ures;
                }
                else{
                  sakk_tabla[t_x][t_y]=sakk_tabla[elozox][elozoy];
                  sakk_tabla[elozox][elozoy]=Ures;
                }
                bool sakk_hatter[8][8];
                hatter_masol(sakk_hatter, sakk_lep);

                if(sakk_fekete(sakk_tabla, sakk_hatter)==false){
                    jolepes[t_x][t_y]=false;
                }

                Lista_masol(sakk_tabla, lista->adat);
            }
          }
        }
}

bool matt_fekete(Babu sakk_tabla[8][8], ListaElem* lista){
        ListaElem* ls = lista;
        bool jolepes[8][8];
        alap_hatter(jolepes);
        for (int t_x = 0; t_x < 8; t_x++) {
          for (int t_y = 0; t_y < 8; t_y++) {
            fekete_babu_jolepes(sakk_tabla, jolepes, ls, t_y, t_y);
            for (int x = 0; x < 8; x++) {
              for (int y = 0; y < 8; y++) {
                if (jolepes[x][y]==false)
                  return false;
              }
            }
          }
        }
        return true;
}


bool matt_feher(Babu sakk_tabla[8][8], ListaElem* lista){
        ListaElem* ls = lista;
        bool jolepes[8][8];
        alap_hatter(jolepes);
        for (int t_x = 0; t_x < 8; t_x++) {
          for (int t_y = 0; t_y < 8; t_y++) {
            feher_babu_jolepes(sakk_tabla, jolepes, ls, t_y, t_y);
            for (int x = 0; x < 8; x++) {
              for (int y = 0; y < 8; y++) {
                if (jolepes[x][y]==false)
                  return false;
              }
            }
          }
        }
        return true;
}
