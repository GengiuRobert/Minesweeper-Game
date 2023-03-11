#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minesweeper.h"


int main()
{
    int nr_bombs=2;
    char cols[]= {'B','D'};
    int rows[]= {1,3};
    int h=3,w=6;
    char t[h][w];
    char** s=malloc(h*sizeof(char*));
    for(int i=0; i<h; i++)
        *(s+i)=malloc(w*sizeof(char));
    create(nr_bombs,cols,rows,h,w,t);
    print(h,w,t);
    s=init_state(h,w);
    printf("\n\n");


    char str[1001],str1[1001]=" ";
    int ok1=0,ok2=0;
    comanda_joc comenzi[1001];
    while((ok1+ok2)!=1)
    {
        gets(str);
        char *p = str;
        char s1[200]="",c;
        int nrcomenzi=0,lost=0,win=1,z,x;
        ok1=0,ok2=0;
        char* k;
        while(p < str + strlen(str) )
        {
            z= sscanf(p," %c%d",&c,&x);

            if(z==2)
            {
                comenzi[nrcomenzi].tip_comanda='.';
                comenzi[nrcomenzi].rand=x;
                comenzi[nrcomenzi].coloana=c;
                sprintf(s1,"%d",x);
                k=strstr(p,s1);
                (nrcomenzi)++;
            }

            else
            {
                z = sscanf(p," !%c%d",&c,&x);
                if(z == 2)
                {
                    comenzi[nrcomenzi].tip_comanda='!';
                    comenzi[nrcomenzi].rand=x;
                    comenzi[nrcomenzi].coloana=c;
                    sprintf(s1,"%d",x);
                    k=strstr(p,s1);
                    (nrcomenzi)++;
                }
                else
                {
                    break;
                }

            }
            p=k+strlen(s1);

        }
        if(nrcomenzi>=100)
        {
            printf("nr comenzi depasit");
            break;
        }

        int ccol,rrand;
        for(int i=0; i<nrcomenzi; i++)
        {
            if(finishGame(h,w,t,s) == 1)
            {
                break;
            }

            if(comenzi[i].coloana>='A' && comenzi[i].coloana<='Z')
                ccol=((int)comenzi[i].coloana)-65;
            else if(comenzi[i].coloana>='a' && comenzi[i].coloana<='z')
                ccol=((int)comenzi[i].coloana)-97+26;
            rrand=comenzi[i].rand-1;

            if(rrand >= h || ccol >= w || rrand <0 || ccol < 0)
            {
                continue;
            }

            if(comenzi[i].tip_comanda=='!')
                mark(rrand,ccol,h,w,s);
            else if(comenzi[i].tip_comanda=='.')
            {
                if(t[rrand][ccol]=='X')
                {
                    lost=1;
                    break;
                }
                else discover(rrand,ccol,h,w,t,s);
            }

        }
        player_view(h,w,t,s);
        printf("\n\n");

        if(lost==1)
        {
            ok1=1;
            printf("ai incercat sa descoperi o bomba, ai pierdut, ghinion");
        }

        win = finishGame(h,w,t,s);
        if(win==1)
        {
            ok2=1;
            printf("ai castigat,felicitari");
        }

    }

    dezalocate(h,s);
}
