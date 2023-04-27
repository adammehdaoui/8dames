#include <stdio.h>
#include <unistd.h>

#include <MLV/MLV_all.h>

#define WINDOW_X 1280
#define WINDOW_Y 720
#define CELL_SIZE (WINDOW_Y)/10

int bit_value_ULI(unsigned long int n, int position){
    unsigned long int tmp = n<<position;
    return tmp & 1;
}

void print_ULI(unsigned long int n){
    for(int i=sizeof(unsigned long int)*8 - 1; i>=0; i--){
        fprintf(stdout, "%ld", n>>i & 1);
    }
    fprintf(stdout, "\n");
}

void set_positive_bit_ULI(unsigned long int *n, int position){
    *n = (*n)|(1<<position);
}

void set_negative_bit_ULI(unsigned long int *n, int position){
    *n = (*n)&~(1<<position);
}   

void display_board(){
    int x=0;
    int y=0;
    int nbCases = 0;

    while(nbCases<64){
        if(nbCases%2==0){
            MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, MLV_rgba(0, 0, 0, 100));
        }
        else{
            MLV_draw_filled_rectangle(x, y, CELL_SIZE, CELL_SIZE, MLV_rgba(0, 0, 0, 200));
        }
        
        nbCases++;      

        if(nbCases%8 == 0 && nbCases !=0){
            x=0;
            y+=CELL_SIZE;
        }
        else{
            x+=CELL_SIZE;
        }
    }
}

int main(int argc, char *argv[]){
    MLV_create_window("MEHDAOUI Adam - TP13 - ECHIQUIER", NULL, WINDOW_X, WINDOW_Y);
    MLV_clear_window(MLV_COLOR_WHITE);
    display_board();
    MLV_actualise_window();
    sleep(10);

    return 0;
}