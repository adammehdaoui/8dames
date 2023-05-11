#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include <MLV/MLV_all.h>

#include "../include/echiquier.h"
#include "../include/display.h"
#include "../include/utils.h"

int queen_on_diago(unsigned long int n, int rank){
    int d1, d2, d3, d4;

    d1 = rank-9;
    d2 = rank-7;
    d3 = rank+9;
    d4 = rank+7;

    while(d1%8 != 0 && d1>0){
        if(bit_value_ULI(n, d1) == 1){
            fprintf(stderr, "1111111111111");
            return 1;
        }
        d1-=9;
    }

    while(d2%8 != 0 && d2>0){
        if(bit_value_ULI(n, d2) == 1){
            fprintf(stderr, "222222222222");
            return 1;
        }
        d2-=7;
    }

    while(d3%8 != 7 && d3<64){
        if(bit_value_ULI(n, d3) == 1){
            fprintf(stderr, "33333333333");
            return 1;
        }
        d3+=9;
    }

    while(d4%8 != 7 && d4<64){
        if(bit_value_ULI(n, d4) == 1){
            fprintf(stderr, "44444444444");
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
        fprintf(stdout, "La reine en %d est en echec.\n", rank);
        fprintf(stderr, queen_on_column(n, rank) == 1 ? "La reine est en echec sur sa colonne.\n" : "");
        fprintf(stderr, queen_on_line(n, rank) == 1 ? "La reine est en echec sur sa ligne.\n" : "");
        fprintf(stderr, queen_on_diago(n, rank) == 1 ? "La reine est en echec sur sa diagonale.\n" : "");
        return 0;
    }
    else{
        return 1;
    }
}

int game(){
    unsigned long int n = 0;
    int x, y, lastX, lastY, i, j, rank;
    int lose = 0;
    int end = 0;
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

    while(!end){
        MLV_actualise_window();
        MLV_wait_mouse(&x, &y);

        if(x<=BOARD_SIZE && y<=BOARD_SIZE){
            i = (int)x/(CELL_SIZE);
            j = (int)y/(CELL_SIZE);

            rank = (j*8)+i;

            set_positive_bit_ULI(&n, rank);

            display_queens(n, img);

            if(queen_is_valid(n, rank) == 0){
                lose = 1;
                lastX = x;
                lastY = y;
                display_lose(font);
                MLV_actualise_window();

                while(lose == 1){
                    MLV_wait_mouse(&x, &y);

                    if(x>WINDOW_X/2 && x<(WINDOW_X/2)+(WINDOW_X/8 + 15) && y>(WINDOW_Y/2) && y<(WINDOW_Y/2)+(CELL_SIZE/2) - 10) {
                        clear_lose(rank, lastX, lastY);
                        set_negative_bit_ULI(&n, rank);
                        lose = 0;
                    }
                }
            }
        
            if(count_bit_ULI(n) == 8){
                display_win(font);
                end = 1;
                MLV_actualise_window();
                sleep(5);
            }

        }
    }

    MLV_free_font(font);
    MLV_free_window();

    return 0;
}