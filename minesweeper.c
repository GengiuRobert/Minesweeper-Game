#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void print (int h, int w, char t[h][w])
{

    int i,j;
    char Start_Leg_Col='A',Finish_Leg_Col='A';
    printf("  ");
    for(i=0; i<w; i++)
    {
        if(Start_Leg_Col=='Z')
        {
            Start_Leg_Col='a';
        }
        printf("%c",Start_Leg_Col);
        Start_Leg_Col++;
    }
    printf("\n");
    for(i=0; i<h; i++)
    {
        for(j=0; j<w; j++)
        {
            if(j==0)
            {
                printf("%d ",i+1);
            }
            printf("%c",t[i][j]);
            if(j==w-1)
            {
                printf(" %d",i+1);
            }
        }
        printf("\n");
    }
    printf("  ");
    for(i=0; i<w; i++)
    {
        if(Finish_Leg_Col=='Z')
        {
            Finish_Leg_Col='a';
        }
        printf("%c",Finish_Leg_Col);
        Finish_Leg_Col++;
    }

}

void initializare(char h,char w,char t[h][w])
{
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
            t[i][j]='0';
    }

}


void create(int nr_bombs,char cols[],int rows[],int h, int w, char t[h][w])
{
    int i,j;
    initializare(h,w,t);
    for(i=0; i<nr_bombs; i++)
    {
        t[rows[i]-1][cols[i]-'A']='X';
        if(rows[i]-2>=0)
        {
            if(cols[i]-'A'-1>=0)
            {
                if(t[rows[i]-2][cols[i]-'A'-1]!='X')t[rows[i]-2][cols[i]-'A'-1]++;
            }
            if(t[rows[i]-2][cols[i]-'A']!='X') t[rows[i]-2][cols[i]-'A']++;
            if(cols[i]-'A'+1<w)
            {
                if(t[rows[i]-2][cols[i]-'A'+1]!='X')t[rows[i]-2][cols[i]-'A'+1]++;
            }

        }
        if(cols[i]-'A'-1>=0)
        {
            if(t[rows[i]-1][cols[i]-'A'-1]!='X') t[rows[i]-1][cols[i]-'A'-1] ++;
        }
        if(cols[i]-'A'+1<w)
        {
            if(t[rows[i]-1][cols[i]-'A'+1]!='X')t[rows[i]-1][cols[i]-'A'+1]++;
        }
        if(rows[i]<h)
        {
            if(cols[i]-'A'-1>=0)
            {
                if(t[rows[i]][cols[i]-'A'-1]!='X') t[rows[i]][cols[i]-'A'-1]++;
            }
            if(t[rows[i]][cols[i]-'A']!='X')t[rows[i]][cols[i]-'A']++;
            if(cols[i]-'A'+1<w)
            {
                if(t[rows[i]][cols[i]-'A'+1]!='X')t[rows[i]][cols[i]-'A'+1]++;
            }
        }
    }

    for(i=0; i<h; i++)
    {
        for(j=0; j<w; j++)
            if(t[i][j]=='0') t[i][j]='.';
    }

//    for(i=0; i<h; i++)
//    {
//        for(j=0; j<w; j++)
//        {
//            printf("%c",t[i][j]);
//        }
//        printf("\n");
//    }
}

char** init_state(int h,int w)
{
    char** st=malloc(h*sizeof(char*));
    for(int i=0; i<h; i++)
        *(st+i)=malloc(w*sizeof(char));

    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
            *(*(st+i)+j)='?';
    }
    return st;
//    for(int i=0; i<h; i++)
//    {
//        for(int j=0; j<w; j++)
//            printf("%c",s[i][j]);
//        printf("\n");
//    }
//    printf("\n\n\n");
}

int discover(int i,int j,int h,int w, char t[h][w],char** s)
{
    int k=1;
    if(i<0) return -2;
    if(j<0) return -2;
    if(i>=h) return -2;
    if(j>=w) return -2;
    if(t[i][j]=='X') return -1;
    if( *(*(s+i)+j)=='.') return 0;
    if(isdigit(t[i][j])>0)
    {
        *(*(s+i)+j)='.';
        return 1;
    }
    if(t[i][j]=='.')
    {
        *(*(s+i)+j)='.';

        discover(i-1,j,h,w,t,s);
        discover(i-1,j+1,h,w,t,s);
        discover(i+1,j-1,h,w,t,s);
        discover(i+1,j,h,w,t,s);
        discover(i+1,j+1,h,w,t,s);
        discover(i,j-1,h,w,t,s);
        discover(i,j+1,h,w,t,s);
        discover(i-1,j-1,h,w,t,s);
        return 2;
    }

}

void afisare(int h,int w,char** s)
{
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
            printf("%c",*(*(s+i)+j));
        printf("\n");
    }
}

void mark(int i, int j, int h, int w, char** s)
{
    int ok1=0,ok2=0;
    if(i>=0 && i<h) ok1=1;
    if(j>=0 && j<w) ok2=1;
    if(ok1*ok2==1)
    {
        if(s[i][j]=='?') s[i][j]='!';
        else if(s[i][j]=='!') s[i][j]='?';
    }
}

void player_view(int h, int w, char t[h][w], char** s)
{

    char Start_Leg_Col='A',Finish_Leg_Col='A';
    printf("  ");
    for(int i=0; i<w; i++)
    {
        if(Start_Leg_Col=='Z')
        {
            Start_Leg_Col='a';
        }
        printf("%c",Start_Leg_Col);
        Start_Leg_Col++;
    }
    printf("\n");
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            if(j==0)
            {
                printf("%d ",i+1);
            }
            if(s[i][j]=='.')
                printf("%c",t[i][j]);
            else printf("%c",s[i][j]);
            if(j==w-1)
            {
                printf(" %d",i+1);
            }
        }
        printf("\n");
    }
    printf("  ");
    for(int i=0; i<w; i++)
    {
        if(Finish_Leg_Col=='Z')
        {
            Finish_Leg_Col='a';
        }
        printf("%c",Finish_Leg_Col);
        Finish_Leg_Col++;
    }


}

int finishGame(int h, int w,char t[h][w], char **s)
{
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            if(t[i][j] !='X' && s[i][j] !='.')
            {
                return 0;
            }
        }

    }
    return 1;
}

void dezalocate(int h, char **s){
    for(int i = 0; i < h; i ++){
        free(s[i]);
    }
    free(s);
}



