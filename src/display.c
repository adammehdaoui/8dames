#include <MLV/MLV_all.h>

#include "../include/display.h"
#include "../include/utils.h"

void display_board(MLV_Font *font){
    int x=0;
    int y=0;
    int i;
    int line=0;
    int nbCases=0;

    /*Affichage des cases*/
    while(nbCases<64){
        if(line%2==0){
            if(nbCases%2==0){
                MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, MLV_rgba(0, 0, 0, 25));
            }
            else{
                MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, MLV_rgba(0, 0, 0, 50));
            }

        }
        else{
            if(nbCases%2==0){
                MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, MLV_rgba(0, 0, 0, 50));
            }
            else{
                MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, MLV_rgba(0, 0, 0, 25));
            }
        }
        
        nbCases++;      

        if(nbCases%8 == 0 && nbCases !=0){
            x=0;
            y+=CELL_SIZE;
            line++;
        }
        else{
            x+=CELL_SIZE;
        }
    }

    MLV_draw_line(0, y, CELL_SIZE*8, y, MLV_COLOR_BLACK);
    MLV_draw_line(CELL_SIZE*8, y, CELL_SIZE*8, 0, MLV_COLOR_BLACK);

    /*Affichage des numéros autour du plateau*/
    char text[2];
    
    x = ((CELL_SIZE)*7 + (CELL_SIZE)/2);
    y = (CELL_SIZE)*8;
    for(i=0; i<8; i++){
        sprintf(text, "%d", i);
        MLV_draw_text_with_font(x, y, text, font, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
        x-=(CELL_SIZE);
    }

    x = ((CELL_SIZE)*7 + (CELL_SIZE)+5);
    y = ((CELL_SIZE)*8 - (CELL_SIZE)/2);  
    for(i=0; i<8; i++){
        sprintf(text, "%d", i);
        MLV_draw_text_with_font(x, y, text, font, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
        y-=(CELL_SIZE);
    }

    MLV_draw_line(0, (CELL_SIZE)*9 - (CELL_SIZE)/1.5, (CELL_SIZE)*9 - (CELL_SIZE)/1.5, (CELL_SIZE)*9 - (CELL_SIZE)/1.5, MLV_COLOR_BLACK);
    MLV_draw_line((CELL_SIZE)*9 - (CELL_SIZE)/1.5, (CELL_SIZE)*9 - (CELL_SIZE)/1.5, (CELL_SIZE)*9 - (CELL_SIZE)/1.5, 0, MLV_COLOR_BLACK);
}

void display_queens(unsigned long int n, MLV_Image *img){
    int wx, wy;

    for(int i=sizeof(unsigned long int)*8 - 1; i>=0; i--){
        if(bit_value_ULI(n, i)){ 
            wx = (i%8)*CELL_SIZE - 3;
            wy = (i/8)*CELL_SIZE - 3;

            MLV_draw_image(img, wx, wy);
        }
    }

}

void display_lose(MLV_Font *font){
    MLV_draw_rectangle(WINDOW_X/2, WINDOW_Y/2, WINDOW_X/8 + 15, CELL_SIZE/2 - 10, MLV_COLOR_BLACK);
    MLV_draw_text_with_font(WINDOW_X/2, WINDOW_Y/2, " Annuler le coup ", font, MLV_COLOR_BLACK, MLV_TEXT_CENTER);
    MLV_draw_text_with_font(WINDOW_X/2, WINDOW_Y/2 - CELL_SIZE, " Dommage ! Toutes les cases sont attaquées. ", font, MLV_COLOR_RED, MLV_TEXT_CENTER);
}

void display_win(MLV_Font *font){
    MLV_draw_text_with_font(WINDOW_X/2, WINDOW_Y/2- 25, " Bravo ! Vous avez placé les 8 dames ! ", font, MLV_COLOR_GREEN, MLV_TEXT_CENTER);
}

void clear_lose(int position, int x, int y){
    int r, v, b, a;

    int startX = x - x%(CELL_SIZE);
    int startY = y - y%(CELL_SIZE);

    MLV_get_pixel(startX, startY, &r, &v, &b, &a);
    MLV_draw_filled_rectangle(startX, startY, CELL_SIZE, CELL_SIZE, MLV_rgba(r, v, b, 255));
    MLV_draw_filled_rectangle(WINDOW_X/2, 0, WINDOW_X/2, WINDOW_Y, MLV_COLOR_WHITE);
}
