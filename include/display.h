#ifndef __DISPLAY__
#define __DISPLAY__

#define WINDOW_X 1280
#define WINDOW_Y 720
#define NB_CELLS 64
#define CELL_SIZE (WINDOW_Y)/10
#define BOARD_SIZE CELL_SIZE*8

void display_board(MLV_Font *font);
void display_queens(unsigned long int n, MLV_Image *img);
void display_lose(MLV_Font *font);
void display_win(MLV_Font *font);
void clear_lose(int position, int x, int y);

#endif