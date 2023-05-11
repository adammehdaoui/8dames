#include <stdio.h>

#include "../include/utils.h"

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
