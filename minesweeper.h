#ifndef MINESWEEPER_H
#define MINESWEEPER_H
typedef struct
{
    char tip_comanda,coloana;
    int rand;
} comanda_joc;
void print(int h, int w, char t[h][w]);
void create(int nr_bombs, char cols[], int rows[], int h, int w, char t[h][w]);
char** init_state(int h, int w);
int discover(int i,int j,int h,int w,char t[h][w],char** s);
void afisare(int h,int w,char** s);
void mark(int i, int j, int h, int w, char** s);
void player_view(int h, int w, char t[h][w], char** s);
int finishGame(int h, int w,char t[h][w], char **s);
void dezalocate(int h, char **s);
#endif // MINESWEEPER_H



