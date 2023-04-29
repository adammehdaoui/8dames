#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <MLV/MLV_all.h>

#define WINDOW_X 1280
#define WINDOW_Y 720
#define NB_CELLS 64
#define CELL_SIZE (WINDOW_Y)/10
#define BOARD_SIZE CELL_SIZE*8

int bit_value_ULI(unsigned long int n, int position){
    unsigned long int tmp = n>>position;
    return tmp & 1UL;
}

void print_ULI(unsigned long int n){
    for(int i=sizeof(unsigned long int)*8 - 1; i>=0; i--){
        fprintf(stdout, "%d", bit_value_ULI(n, i));
    }
    fprintf(stdout, "\n");
}

void set_positive_bit_ULI(unsigned long int *n, int position){
    *n = (*n)|(1UL<<position);
}

void set_negative_bit_ULI(unsigned long int *n, int position){
    *n = (*n)&~(1UL<<position);
}   

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

void display_pawns(unsigned long int n){
}

int main(int argc, char *argv[]){
    unsigned long int n = 0b0;
    int x, y, wx, wy, i, j, rank;
    MLV_Image *img;
    MLV_Font *font;

    MLV_create_window("MEHDAOUI Adam - TP13 - ECHIQUIER", NULL, WINDOW_X, WINDOW_Y);
    img = MLV_load_image("resources/images/queen.png");

    if(img == NULL){
        fprintf(stderr, "Erreur lors du chargement de l'image.\n");
        return 1;
    }

    font = MLV_load_font("resources/fonts/Montserrat.ttf", 20);

    if(font == NULL){
        fprintf(stderr, "Erreur lors du chargement de la police.\n");
        return 1;
    }

    MLV_clear_window(MLV_COLOR_WHITE);
    display_board(font);

    while(1){
        MLV_actualise_window();
        MLV_wait_mouse(&x, &y);

        if(x<=BOARD_SIZE && y<=BOARD_SIZE){
            wx = (x/(CELL_SIZE)*(CELL_SIZE)-(CELL_SIZE)/15);
            wy = (y/(CELL_SIZE)*(CELL_SIZE)-(CELL_SIZE)/15);
            
            i = (int)x/(CELL_SIZE);
            j = (int)y/(CELL_SIZE);

            rank = i + j*8;
            fprintf(stdout, "%d\n", rank);
            set_positive_bit_ULI(&n, 63);
            print_ULI(n);

            MLV_draw_image(img, wx, wy);
        }
    }

    MLV_free_window();

    return 0;
}