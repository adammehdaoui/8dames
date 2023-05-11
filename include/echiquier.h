#ifndef __ECHIQUIER__
#define __ECHIQUIER__

int queen_on_diago(unsigned long int n, int rank);
int queen_on_line(unsigned long int n, int rank);
int queen_on_column(unsigned long int n, int rank);
int queen_is_valid(unsigned long int n, int rank);
int game();

#endif