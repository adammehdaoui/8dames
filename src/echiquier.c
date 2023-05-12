#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include <MLV/MLV_all.h>

#include "../include/echiquier.h"
#include "../include/display.h"
#include "../include/utils.h"

void set_on_diago(unsigned long int *n, int rank){
    int haut_gauche;
    int haut_droit;
    int bas_gauche;
    int bas_droit;
    int border = 0;

    if(rank%8!=7){
        for(bas_droit=rank+9; bas_droit<64 && border==0; bas_droit+=9){
            set_positive_bit_ULI(n, bas_droit);

            if(bas_droit%8==7){
                border = 1;
            }
        }
    }

    border = 0;

    if(rank%8!=0){
        for(bas_gauche=rank+7; bas_gauche<64 && bas_gauche!=7 && border==0; bas_gauche+=7){
            set_positive_bit_ULI(n, bas_gauche);

            if(bas_gauche%8==0){
                border = 1;
            }
        }
    }

    border=0;

    if(rank%8!=7){
        for(haut_droit=rank-7; haut_droit>=0 && border==0; haut_droit-=7){
            set_positive_bit_ULI(n, haut_droit);

            if(haut_droit%8==7){
                border = 1;
            }
        }
    }

    border=0;

    if(rank%8!=0){
        for(haut_gauche=rank-9; haut_gauche>=0 && border==0; haut_gauche-=9){
            set_positive_bit_ULI(n, haut_gauche);

            if(haut_gauche%8==0){
                border = 1;
            }
        }
    }
}

void set_on_line(unsigned long int *n, int rank){
    int first_rank = (rank/8)*8;
    int last_rank = first_rank + 7; 

    for(int i=first_rank; i<=last_rank; i++){
        if(i!=rank) set_positive_bit_ULI(n ,i);
    }
}

void set_on_column(unsigned long int *n, int rank){
    int first_rank = rank%8;
    int last_rank = first_rank+56;

    for(int i=first_rank; i<=last_rank; i+=8){
        if(i!=rank) set_positive_bit_ULI(n, i);
    }
}

void set_menace(unsigned long int *n, int rank){
    set_positive_bit_ULI(n, rank);
    set_on_diago(n, rank);
    set_on_line(n, rank);
    set_on_column(n, rank);
}

/*int queen_on_diago(unsigned long int n, int rank){
    int haut_gauche = rank-9;
    int haut_droit = rank-7;
    int bas_gauche = rank+7;
    int bas_droit = rank+9;

    while((haut_gauche%8!=0 || haut_gauche == 0) && haut_gauche>=0){
        if(bit_value_ULI(n, haut_gauche) == 1){
            return 1;
        }
        haut_gauche-=9;
    }

    while(haut_droit%8!=0 && haut_droit>=0){
        if(bit_value_ULI(n, haut_droit) == 1){
            return 1;
        }
        haut_droit-=7;
    }

    while(bas_gauche%9!=7 && bas_gauche<64){
        if(bit_value_ULI(n, bas_gauche) == 1){
            return 1;
        }
        bas_gauche+=7;
    }

    while(bas_droit%9!=7 && bas_droit<64){
        if(bit_value_ULI(n, bas_droit) == 1){
            return 1;
        }
        bas_droit+=9;
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
}*/

int game_over(unsigned long int n){
    if(count_bit_ULI(n) == 64){
        return 1;
    }

    return 0;
}

int game(){
    unsigned long int n = 0;
    int x, y, lastX, lastY, i, j, rank;
    int lose = 0;
    int end = 0;
    int queens_on_board;
    MLV_Image *img;
    MLV_Font *font;
    MLV_Music *sound;

    MLV_create_window("MEHDAOUI Adam - TP13 - ECHIQUIER", NULL, WINDOW_X, WINDOW_Y);
    MLV_init_audio();
    img = MLV_load_image("resources/images/queen.png");
    sound = MLV_load_music("resources/sounds/queen.mp3");

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
            MLV_play_music(sound, 1.0, 1);

            i = (int)x/(CELL_SIZE);
            j = (int)y/(CELL_SIZE);

            rank = (j*8)+i;

            display_queen(rank, img);

            if(bit_value_ULI(n, rank) == 1){
                lose = 1;
                lastX = x;
                lastY = y;
                display_rollback(font);
                MLV_actualise_window();

                while(lose == 1){
                    MLV_wait_mouse(&x, &y);

                    if(x>WINDOW_X/2 && x<(WINDOW_X/2)+(WINDOW_X/8 + 15) && y>(WINDOW_Y/2) && y<(WINDOW_Y/2)+(CELL_SIZE/2) - 10) {
                        clear_lose(rank, lastX, lastY);
                        lose = 0;
                    }
                }
            }
            else{
                set_positive_bit_ULI(&n, rank);

                queens_on_board++;

                set_menace(&n, rank);
        
                if(queens_on_board == 8){
                    display_win(font);
                    end = 1;
                    MLV_actualise_window();
                    sleep(5);
                }

                if(game_over(n) == 1){
                    display_lose(font);
                    end = 1;
                    MLV_actualise_window();
                    sleep(5);
                }
            }

            print_ULI(n);
        }
    }

    MLV_free_music(sound);
    MLV_free_font(font);
    MLV_free_image(img);
    MLV_free_window();

    return 0;
}