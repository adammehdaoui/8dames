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

int count_bit_ULI(unsigned long int n){
    int count = 0;
    for(int i=sizeof(unsigned long int)*8 - 1; i>=0; i--){
        if(bit_value_ULI(n, i) == 1){
            count++;
        }
    }
    return count;
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
    MLV_draw_text_with_font(WINDOW_X/2, WINDOW_Y/2 - CELL_SIZE, "Dommage ! Toutes les cases sont attaquées.", font, MLV_COLOR_RED, MLV_TEXT_CENTER);
}

void clear_lose(){
    
}

int queen_on_diago(unsigned long int n, int rank){
    int d1, d2, d3, d4;

    d1 = rank-9;
    d2 = rank-7;
    d3 = rank+9;
    d4 = rank+7;

    while(d1%8 != 0 && d1>0){
        if(bit_value_ULI(n, d1) == 1){
            return 1;
        }
        d1-=9;
    }

    while(d2%8 != 7 && d2>0){
        if(bit_value_ULI(n, d2) == 1){
            return 1;
        }
        d2-=7;
    }

    while(d3%8 != 7 && d3<64){
        if(bit_value_ULI(n, d3) == 1){
            return 1;
        }
        d3+=9;
    }

    while(d4%8 != 0 && d4<64){
        if(bit_value_ULI(n, d4) == 1){
            return 1;
        }
        d4+=7;
    }

    return 0;
}

int queen_on_line(unsigned long int n, int rank){
    int first_rank = (rank/8)*8;
    int last_rank = first_rank + 7; 

    for(int i=first_rank; i<=last_rank; i++){
        if(bit_value_ULI(n, i) == 1 && i != rank){
            return 1;
        }
    }

    return 0;
}

int queen_on_column(unsigned long int n, int rank){
    int first_rank = rank%8;
    int last_rank = first_rank+56;

    for(int i=first_rank; i<=last_rank; i+=8){
        if(bit_value_ULI(n, i) == 1 && i != rank){
            return 1;
        }
    }

    return 0;
}

int queen_is_valid(unsigned long int n, int rank){
    if(queen_on_column(n, rank) == 1 || queen_on_line(n, rank) == 1 || queen_on_diago(n, rank) == 1){
        return 0;
    }
    else{
        return 1;
    }
}

int main(int argc, char *argv[]){
    unsigned long int n = 0;
    int x, y, wx, wy, i, j, rank;
    int lastRank = -1;
    int lose = 0;
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
            i = (int)x/(CELL_SIZE);
            j = (int)y/(CELL_SIZE);

            rank = (j*8)+i;

            set_positive_bit_ULI(&n, rank);

            display_queens(n, img);

            if(queen_is_valid(n, rank) == 0){

                display_lose(font);

                MLV_actualise_window();

                while(lose == 1){
                    MLV_wait_mouse(&x, &y);

                    if(x>WINDOW_X/2 && x<(WINDOW_X/2)+(WINDOW_X/8 + 15) && y>(WINDOW_Y/2) && y<(WINDOW_Y/2)+(CELL_SIZE/2) - 10) {
                        set_negative_bit_ULI(&n, rank);
                        lose = 0;
                    }
                }
            }
        }
    }

    MLV_free_font(font);
    MLV_free_window();

    return EXIT_SUCCESS;
}