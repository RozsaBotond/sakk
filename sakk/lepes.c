#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include "fv.h"

//A feher kiraly lepes iranyait leirja, és azt a sakk_lep et módosítva mutatja meg.
void feher_kiraly_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==0){
      alap_hatter(sakk_lep);

      sakk_lep[x][y]=false;
      if(((x-1)>=0)&&((y+1)<8))       sakk_lep[x-1][y+1]=false;
      if(((x-1)>=0)&&((y-1)>=0))      sakk_lep[x-1][y-1]=false;
      if(((x-1)>=0))                  sakk_lep[x-1][y]=false;
      if(((y-1)>=0))                  sakk_lep[x][y-1]=false;
      if(((y+1)<8))                   sakk_lep[x][y+1]=false;
      if(((x+1)<8))                   sakk_lep[x+1][y]=false;
      if(((x+1)<8)&&((y+1)<8))        sakk_lep[x+1][y+1]=false;
      if(((x+1)<8)&&((y-1)>=0))       sakk_lep[x+1][y-1]=false;
    }
}

//A fekete kiraly lepes iranyait leirja, és azt a sakk_lep et módosítva mutatja meg.
void fekete_kiraly_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==6){
      alap_hatter(sakk_lep);

      sakk_lep[x][y]=false;
      if(((x-1)>=0)&&((y+1)<8))       sakk_lep[x-1][y+1]=false;
      if(((x-1)>=0)&&((y-1)>=0))      sakk_lep[x-1][y-1]=false;
      if(((x-1)>=0))                  sakk_lep[x-1][y]=false;
      if(((y-1)>=0))                  sakk_lep[x][y-1]=false;
      if(((y+1)<8))                   sakk_lep[x][y+1]=false;
      if(((x+1)<8))                   sakk_lep[x+1][y]=false;
      if(((x+1)<8)&&((y+1)<8))        sakk_lep[x+1][y+1]=false;
      if(((x+1)<8)&&((y-1)>=0))       sakk_lep[x+1][y-1]=false;
    }
}


//A feher gyalogos lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void feher_paraszt_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==5){
      alap_hatter(sakk_lep);
      sakk_lep[x][y]=false;
      if((y+1)<8)
        sakk_lep[x][y+1]=false;
    }
}
//A fekete gyalogos lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void fekete_paraszt_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==11){
      alap_hatter(sakk_lep);
      sakk_lep[x][y]=false;
      if((y-1)>=0)
        sakk_lep[x][y-1]=false;
    }
}

//A fekete bastya lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void feher_bastya_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==4){
      alap_hatter(sakk_lep);
      sakk_lep[0][y]=false;
      sakk_lep[1][y]=false;
      sakk_lep[2][y]=false;
      sakk_lep[3][y]=false;
      sakk_lep[4][y]=false;
      sakk_lep[5][y]=false;
      sakk_lep[6][y]=false;
      sakk_lep[7][y]=false;
      sakk_lep[x][0]=false;
      sakk_lep[x][1]=false;
      sakk_lep[x][2]=false;
      sakk_lep[x][3]=false;
      sakk_lep[x][4]=false;
      sakk_lep[x][5]=false;
      sakk_lep[x][6]=false;
      sakk_lep[x][7]=false;
    }
}

//A feher bastya lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void fekete_bastya_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==10){
      alap_hatter(sakk_lep);
      sakk_lep[0][y]=false;
      sakk_lep[1][y]=false;
      sakk_lep[2][y]=false;
      sakk_lep[3][y]=false;
      sakk_lep[4][y]=false;
      sakk_lep[5][y]=false;
      sakk_lep[6][y]=false;
      sakk_lep[7][y]=false;
      sakk_lep[x][0]=false;
      sakk_lep[x][1]=false;
      sakk_lep[x][2]=false;
      sakk_lep[x][3]=false;
      sakk_lep[x][4]=false;
      sakk_lep[x][5]=false;
      sakk_lep[x][6]=false;
      sakk_lep[x][7]=false;
    }
}

//A feher kiralyno lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void feher_kiralyno_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==1){
      alap_hatter(sakk_lep);

      sakk_lep[0][y]=false;
      sakk_lep[1][y]=false;
      sakk_lep[2][y]=false;
      sakk_lep[3][y]=false;
      sakk_lep[4][y]=false;
      sakk_lep[5][y]=false;
      sakk_lep[6][y]=false;
      sakk_lep[7][y]=false;
      sakk_lep[x][0]=false;
      sakk_lep[x][1]=false;
      sakk_lep[x][2]=false;
      sakk_lep[x][3]=false;
      sakk_lep[x][4]=false;
      sakk_lep[x][5]=false;
      sakk_lep[x][6]=false;
      sakk_lep[x][7]=false;

      int eredeti_x = x;
      int eredeti_y = y;
      while((x<8)&&(y<8)){
        sakk_lep[x][y]=false;
        x++;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x<8)&&(y>-1)){
        sakk_lep[x][y]=false;
        x++;
        y--;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y<8)){
        sakk_lep[x][y]=false;
        x--;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y>-1)){
        sakk_lep[x][y]=false;
        x--;
        y--;
      }
    }
}

//A fekete kiralyno lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void fekete_kiralyno_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==7){
      alap_hatter(sakk_lep);

      sakk_lep[0][y]=false;
      sakk_lep[1][y]=false;
      sakk_lep[2][y]=false;
      sakk_lep[3][y]=false;
      sakk_lep[4][y]=false;
      sakk_lep[5][y]=false;
      sakk_lep[6][y]=false;
      sakk_lep[7][y]=false;
      sakk_lep[x][0]=false;
      sakk_lep[x][1]=false;
      sakk_lep[x][2]=false;
      sakk_lep[x][3]=false;
      sakk_lep[x][4]=false;
      sakk_lep[x][5]=false;
      sakk_lep[x][6]=false;
      sakk_lep[x][7]=false;

      int eredeti_x = x;
      int eredeti_y = y;
      while((x<8)&&(y<8)){
        sakk_lep[x][y]=false;
        x++;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x<8)&&(y>-1)){
        sakk_lep[x][y]=false;
        x++;
        y--;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y<8)){
        sakk_lep[x][y]=false;
        x--;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y>-1)){
        sakk_lep[x][y]=false;
        x--;
        y--;
      }
    }
}

//A fekete futo lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void fekete_futo_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==8){
      alap_hatter(sakk_lep);
      int eredeti_x = x;
      int eredeti_y = y;
      while((x<8)&&(y<8)){
        sakk_lep[x][y]=false;
        x++;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x<8)&&(y>-1)){
        sakk_lep[x][y]=false;
        x++;
        y--;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y<8)){
        sakk_lep[x][y]=false;
        x--;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y>-1)){
        sakk_lep[x][y]=false;
        x--;
        y--;
      }
    }
}

//A feher futo lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void feher_futo_lep (Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
    if(sakk_tabla[x][y]==2){
      alap_hatter(sakk_lep);
      int eredeti_x = x;
      int eredeti_y = y;
      while((x<8)&&(y<8)){
        sakk_lep[x][y]=false;
        x++;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x<8)&&(y>-1)){
        sakk_lep[x][y]=false;
        x++;
        y--;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y<8)){
        sakk_lep[x][y]=false;
        x--;
        y++;
      }
      x = eredeti_x;
      y = eredeti_y;
      while((x>-1)&&(y>-1)){
        sakk_lep[x][y]=false;
        x--;
        y--;
      }
    }
}

//A feher huszar lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void feher_huszar_lep(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
  if(sakk_tabla[x][y]==3){
    alap_hatter(sakk_lep);
    if(((x+1)<8)&&((y+2)<8))sakk_lep[x+1][y+2]=false;
    if(((x-1)>=0)&&((y+2)<8))sakk_lep[x-1][y+2]=false;
    if(((x+2)<8)&&((y+1)<8))sakk_lep[x+2][y+1]=false;
    if(((x+2)<8)&&((y-1)>=0))sakk_lep[x+2][y-1]=false;
    if(((x+1)<8)&&((y-2)>=0))sakk_lep[x+1][y-2]=false;
    if(((x-1)>=0)&&((y-2)>=0))sakk_lep[x-1][y-2]=false;
    if(((x-2)>=0)&&((y+1)<8))sakk_lep[x-2][y+1]=false;
    if(((x-2)>=0)&&((y-1)>=0))sakk_lep[x-2][y-1]=false;
  }
}

//A fekete huszar lepes lehetosegeit irj le, és azt a sakk_lep et módosítva mutatja meg.
void fekete_huszar_lep(Babu sakk_tabla[8][8], bool sakk_lep[8][8], int x, int y){
  if(sakk_tabla[x][y]==9){
    alap_hatter(sakk_lep);
    if(((x+1)<8)&&((y+2)<8))sakk_lep[x+1][y+2]=false;
    if(((x-1)>=0)&&((y+2)<8))sakk_lep[x-1][y+2]=false;
    if(((x+2)<8)&&((y+1)<8))sakk_lep[x+2][y+1]=false;
    if(((x+2)<8)&&((y-1)>=0))sakk_lep[x+2][y-1]=false;
    if(((x+1)<8)&&((y-2)>=0))sakk_lep[x+1][y-2]=false;
    if(((x-1)>=0)&&((y-2)>=0))sakk_lep[x-1][y-2]=false;
    if(((x-2)>=0)&&((y+1)<8))sakk_lep[x-2][y+1]=false;
    if(((x-2)>=0)&&((y-1)>=0))sakk_lep[x-2][y-1]=false;
  }
}
