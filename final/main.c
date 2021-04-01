#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>

//global variables
int n,sh,sh1;
int **block;
int **plate;
int **energyy;
int number,number_1,number_2;
int meno_n,num_cell,num_cell_1,num_cell_2;
int work,work_1,work_2;
int all_energyy=0,all_energyy_1=0,all_energyy_2=0;
int counter=0;counter_1=0;counter_2=0;
enum blocks {ENERGY=1,MITOSIS,FORBIDDEN,NORMAL};

//functions
int meno(void);
void blocks_info(void);
void array_s(void);
char *rand_string(size_t size);
void map(int n);
void put_cells_in_map(int i,int j);
void put_color_in_map(int i,int j);
int work_in_cells(void);
void choose(int a,int b,int c);
void move(int M,int x,int y);
void boost_energy(int M,int x,int y);
void alll_energyy(void);
int split_cell(int M,int x,int y);
void add_cell(int c,int x,int y);
void save(void);
void load(void);
void freee(void);


struct cell{
    int x,y;
    int mitoz;
    char *str;
    struct cell *next;
}*head,*arg;

struct cell_1{
    int x_1,y_1;
    int mitoz_1;
    char *str_1;
    struct cell_1 *next_1;
}*head_1,*arg_1;

struct cell_2{
    int x_2,y_2;
    int mitoz_2;
    char *str_2;
    struct cell_2 *next_2;
}*head_2,*arg_2;

int meno(void){
    printf("                                    WELLCOM");
    printf("\n\n[1]Load\n\n[2]New single player game\n\n[3]New Multiplayer game\n\n[4]Exit\n\n");
    scanf("%d",&meno_n);
    printf("\n");

    if(meno_n==1){
        load();
        return 0;
    }
    if(meno_n==2){
        blocks_info();
        printf("\n\nHow many cells you want to have?  ");
        scanf("%d",&num_cell);
        head=(struct cell *)malloc(sizeof(struct cell));
        arg=head;

        for(sh=0;sh<num_cell;sh++){
            do{
            arg->x=(rand()%n);
            arg->y=(rand()%n);
            }while((plate[arg->x][arg->y]!=0)||(block[arg->x][arg->y]==FORBIDDEN));
            plate[arg->x][arg->y]++;
            arg->str=rand_string(5);
            arg->next=(struct cell *)malloc(sizeof(struct cell));
            arg=arg->next;
        }
        arg=head;
    }
    if(meno_n==3){
        blocks_info();
        printf("\n\n[1] How many cells you want to have?  ");
        scanf("%d",&num_cell_1);

        printf("\n\n[2] How many cells you want to have?  ");
        scanf("%d",&num_cell_2);

        head_1=(struct cell_1 *)malloc(sizeof(struct cell_1));
        arg_1=head_1;
        for(sh=0;sh<num_cell_1;sh++){
            do{
            arg_1->x_1=(rand()%n);
            arg_1->y_1=(rand()%n);
            }while((plate[arg_1->x_1][arg_1->y_1]!=0)||(block[arg_1->x_1][arg_1->y_1]==FORBIDDEN));
            plate[arg_1->x_1][arg_1->y_1]++;
            arg_1->str_1=rand_string(5);
            arg_1->next_1=(struct cell_1 *)malloc(sizeof(struct cell_1));
            arg_1=arg_1->next_1;
        }
        arg_1=head_1;


        head_2=(struct cell_2 *)malloc(sizeof(struct cell_2));
        arg_2=head_2;
        for(sh=0;sh<num_cell_2;sh++){
            do{
            arg_2->x_2=(rand()%n);
            arg_2->y_2=(rand()%n);
            }while((plate[arg_2->x_2][arg_2->y_2]!=0)||(block[arg_2->x_2][arg_2->y_2]==FORBIDDEN));
            plate[arg_2->x_2][arg_2->y_2]++;
            arg_2->str_2=rand_string(5);
            arg_2->next_2=(struct cell_2 *)malloc(sizeof(struct cell_2));
            arg_2=arg_2->next_2;
        }
        arg_2=head_2;
    }
    if(meno_n==4){
        return 4;
    }
}

void blocks_info(void){
    int i,j,k,clike,clike1;
    char c[1];

        FILE *fb;
        char file_name[100];
        printf("Do you want to play random?([1] YES  [2] NO)  ");
        scanf("%d",&clike);

        if(clike==2){
            printf("\nPleas write your file place:  ");
            getchar();
            gets(file_name);
            fb=fopen(file_name,"rb");
        }
        if(clike==1){
            int s,R;
            printf("\nsize of plate?([1] Random  [2] Not Random)  ");
            scanf("%d",&R);
            if(R==1){
                s=(rand()%14)+2;
            }
            else{
                printf("\nwrite the size you want: ");
                scanf("%d",&s);
            }

            char d[1];
            fb=fopen("new_map.bin","wb");
            fwrite(&s,sizeof(int),1,fb);

            for(i=0;i<(s*s);i++){
                k=(rand()%4)+1;
                sprintf(d,"%d",k);
                fwrite(&d,sizeof(char),1,fb);
            }
            fclose(fb);
            fb=fopen("new_map.bin","rb");
        }

        fread(&n,sizeof(int),1,fb);

        array_s();

        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                fread(&c,sizeof(char),1,fb);
                block[i][j]=atoi(c);
            }
        }

        //mitoz blocks
        energyy=(int **)malloc(n*sizeof(int *));
        for(sh=0;sh<n;sh++){
            energyy[sh]=(int *)malloc(n*sizeof(int));
        }
        for(sh=0;sh<n;sh++){
            for(sh1=0;sh1<n;sh1++){
                if(block[sh][sh1]==ENERGY){
                    energyy[sh][sh1]=100;
                }
                else{
                    energyy[sh][sh1]=0;
                }
            }
        }
        fclose(fb);
}

void array_s(void){
    //blocks
    block=(int **)malloc(n*sizeof(int *));
        for(sh=0;sh<n;sh++){
            block[sh]=(int *)malloc(n*sizeof(int));
    }

    //plate
    plate=(int **)malloc(n*sizeof(int *));
    for(sh=0;sh<n;sh++){
        plate[sh]=(int *)malloc(n*sizeof(int));
    }
    for(sh=0;sh<n;sh++){
        for(sh1=0;sh1<n;sh1++){
            plate[sh][sh1]=0;
        }
    }

    //mitoz blocks
    energyy=(int **)malloc(n*sizeof(int *));
    for(sh=0;sh<n;sh++){
        energyy[sh]=(int *)malloc(n*sizeof(int));
    }

    for(sh=0;sh<n;sh++){
        for(sh1=0;sh1<n;sh1++){
            if(block[sh][sh1]==ENERGY){
                energyy[sh][sh1]=100;
            }
            else{
                energyy[sh][sh1]=0;
            }
        }
    }

    if(meno_n==2){
        arg=head;
        for(sh=0;sh<num_cell;sh++){
            arg->mitoz=0;
            arg=arg->next;
        }
        arg=head;
    }
    if(meno_n==3){
        arg_1=head_1;
        for(sh=0;sh<num_cell_1;sh++){
            arg_1->mitoz_1=0;
            arg_1=arg_1->next_1;
        }
        arg_1=head_1;

        arg_2=head_2;
        for(sh=0;sh<num_cell_2;sh++){
            arg_2->mitoz_2=0;
            arg_2=arg_2->next_2;
        }
        arg_2=head_2;
    }
}

char *rand_string(size_t size) {
    char *str = malloc((size + 1) * sizeof(char));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size_t i;
    for (i = 0; i < size; i++){
        int key = rand() % (sizeof(charset) / sizeof(char) - 1);
        str[i] = charset[key];
    }

    str[size] = '\0';
    return str;
}

void map(int n){
    int i,j,k=0;

    for(j=0;j<(n/2)+(n%2);j++){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        printf("|---|   ");
        }printf("\n");

    for(i=0;i<(2*n);i++){

        for(j=0;j<n;j++){

            if((j%2)==k%2){
                printf("|");
                put_color_in_map(i,j);
                put_cells_in_map(i,j);
            }

            else{
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                printf("|---");
            }

        }
        if(j=n-1){
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            printf("|");
        }

        printf("\n");
        k++;
    }

    printf("    ");
    for(j=0;j<n/2;j++){
        printf("|---|   ");
    }
    printf("\nHINT About Blocks:\n\nRed=Forbidden // Green=Boost Energy // Yellow=Split cell // Black=Normal\n");

    if(meno_n==2){
        printf("\nAll energy: %d\n\n",all_energyy);
    }
    if(meno_n==3){
        printf("\nAll energy of player 1: %d        All energy of player 2: %d\n\n",all_energyy_1,all_energyy_2);
    }
}

void put_cells_in_map(int i,int j){
    int counter,q=0;
    if(meno_n==2){
        arg=head;
        for(counter=0;counter<num_cell;counter++){
            if((arg->y==(n-((i+1)/2)-((i+1)%2)))&&(arg->x==j)){
                plate[arg->x][arg->y]=1;
                printf(" X ");
                q++;
                break;
            }
            else{
                arg=arg->next;
            }
        }

        if(q==0){
            printf("   ");
        }

        arg=head;
    }
    if(meno_n==3){

        arg_1=head_1;
        arg_2=head_2;
        for(counter=0;counter<num_cell_1;counter++){
            if((arg_1->y_1==(n-((i+1)/2)-((i+1)%2)))&&(arg_1->x_1==j)){
                plate[arg_1->x_1][arg_1->y_1]=1;
                printf(" X ");
                q++;
                break;
            }
            else{
                arg_1=arg_1->next_1;
            }
        }
        if(q==0){
             for(counter=0;counter<num_cell_2;counter++){
                if((arg_2->y_2==(n-((i+1)/2)-((i+1)%2)))&&(arg_2->x_2==j)){
                    plate[arg_2->x_2][arg_2->y_2]=1;
                    printf(" Y ");
                    q++;
                    break;
                }
                else{
                    arg_2=arg_2->next_2;
                }
            }
        }

        if(q==0){
            printf("   ");
        }

        arg_1=head_1;
        arg_2=head_2;
    }
}

void put_color_in_map(int i,int j){
    if((block[j][(n-((i+1)/2)-((i+1)%2))]==ENERGY)&&(energyy[j][(n-((i+1)/2)-((i+1)%2))]!=0)){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN);
    }
    if(block[j][(n-((i+1)/2)-((i+1)%2))]==MITOSIS){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY);
    }
    if(block[j][(n-((i+1)/2)-((i+1)%2))]==FORBIDDEN){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),BACKGROUND_INTENSITY|BACKGROUND_RED);
    }
    if(block[j][(n-((i+1)/2)-((i+1)%2))]==NORMAL){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    }
}

int work_in_cells(void){
    int q=0;
    if(meno_n==2){
        printf("[1] Move\n[2] Split a cell\n[3] Boost energy\n[4] Save\n[5] Exit\n");
        scanf("%d",&work);

        if(work==5){
            return 5;
        }
        if(work==4){
            save();
            printf("\n\nSAVED!!!!\n\n");
            return 5;
        }
        choose(1,0,0);
        arg=head;
        for(sh=0;sh<number-1;sh++){
            arg=arg->next;
        }

        if(work==1){
            move(0,arg->x,arg->y);
            system("cls");
            arg=head;
            map(n);
        }
        if(work==2){
            if(split_cell(0,arg->x,arg->y)==1){
                q=2;
            }
            system("cls");
            map(n);
            if(q==2){
                printf("\n\nThis is not a splitting block.\n\n");
            }
        }
        if(work==3){
            if(block[arg->x][arg->y]!=ENERGY){
                q=1;
            }
            if(block[arg->x][arg->y]==ENERGY){
                boost_energy(0,arg->x,arg->y);
            }
            system("cls");
            arg=head;
            map(n);
            if(q==1){
                printf("\nThis is not a energy boosting  block.\n\n");
            }
        }
    }
    if(meno_n==3){
        //player 1
        printf("player 1:\n[1] Move\n[2] Split a cell\n[3] Boost energy\n[4] Save\n[5] Exit\n");
        scanf("%d",&work_1);
        if(work_1==5){
            return 5;
        }
        if(work_1==4){
            save();
            printf("\n\nSAVED!!!!\n\n");
            return 5;
        }
        choose(0,1,0);
        arg_1=head_1;
        for(sh=0;sh<number_1-1;sh++){
            arg_1=arg_1->next_1;
        }

        if(work_1==1){
            move(1,arg_1->x_1,arg_1->y_1);
            system("cls");
            arg_1=head_1;
            map(n);
        }
        if(work_1==2){
            if(split_cell(1,arg_1->x_1,arg_1->y_1)==1){
                q=2;
            }
            system("cls");
            map(n);
            if(q==2){
                printf("\n\nThis is not a splitting block.\n\n");
            }
        }
        if(work_1==3){
            if(block[arg_1->x_1][arg_1->y_1]!=ENERGY){
                q=1;
            }
            if(block[arg_1->x_1][arg_1->y_1]==ENERGY){
                boost_energy(1,arg_1->x_1,arg_1->y_1);
            }
            system("cls");
            arg_1=head_1;
            map(n);
            if(q==1){
                printf("\nThis is not a  energy boosting block.\n\n");
            }
        }
        //player 2
        printf("player 2:\n[1] Move\n[2] Split a cell\n[3] Boost energy\n[4] Save\n[5] Exit\n");
        scanf("%d",&work_2);
        if(work_2==5){
            return 5;
        }
        if(work_2==4){
            save();
             printf("\n\nSAVED!!!!\n\n");
            return 5;
        }
        choose(0,0,1);
        arg_2=head_2;
        for(sh=0;sh<number_2-1;sh++){
            arg_2=arg_2->next_2;
        }

        if(work_2==1){
            move(2,arg_2->x_2,arg_2->y_2);
            system("cls");
            arg_2=head_2;
            map(n);
        }
        if(work_2==2){
            int q=0;
            if(split_cell(2,arg_2->x_2,arg_2->y_2)==1){
                q+=2;
            }
            system("cls");
            map(n);
            if(q==2){
                printf("\n\nThis is not a splitting block.\n\n");
            }
        }
        if(work_2==3){
            if(block[arg_2->x_2][arg_2->y_2]!=ENERGY){
                q=3;
            }
            if(block[arg_2->x_2][arg_2->y_2]==ENERGY){
                boost_energy(2,arg_2->x_2,arg_2->y_2);
            }
            system("cls");
            arg_2=head_2;
            map(n);
            if(q==3){
                printf("This is not a energy boosting block.\n\n");
            }
        }
    }
}

void choose(int a,int b,int c){
    if(a!=0){
        if(counter==0){
            arg=head;
            for(sh=0;sh<num_cell;sh++){
                (arg->mitoz)=0;
                arg=arg->next;
            }
            arg=head;
        }
        counter=1;

        printf("Please choose one of your cells:\n");
        arg=head;
        for(sh=1;sh<=num_cell;sh++){
            printf("[%d] %s(%d,%d)(%d)\n",sh,arg->str,arg->x,arg->y,arg->mitoz);
            arg=arg->next;
        }
        arg=head;
        scanf("%d",&number);
    }
    if(b!=0){
        if(counter_1==0){
            arg_1=head_1;
             for(sh=0;sh<num_cell_1;sh++){
                (arg_1->mitoz_1)=0;
                arg_1=arg_1->next_1;
            }
            arg_1=head_1;
        }
        counter_1=1;

        printf("Please choose one of your cells:\n");
        arg_1=head_1;
        for(sh=1;sh<=num_cell_1;sh++){
            printf("[%d] %s(%d,%d)(%d)\n",sh,arg_1->str_1,arg_1->x_1,arg_1->y_1,arg_1->mitoz_1);
            arg_1=arg_1->next_1;
        }
        arg_1=head_1;
        scanf("%d",&number_1);
    }
    if(c!=0){
        if(counter_2==0){
            arg_2=head_2;
            for(sh=0;sh<num_cell_2;sh++){
                arg_2->mitoz_2=0;
                arg_2=arg_2->next_2;
            }
            arg_2=head_2;
        }
        counter_2=1;

        printf("Please choose one of your cells:\n");
        arg_2=head_2;
        for(sh=1;sh<=num_cell_2;sh++){
            printf("[%d] %s(%d,%d)(%d)\n",sh,arg_2->str_2,arg_2->x_2,arg_2->y_2,arg_2->mitoz_2);
            arg_2=arg_2->next_2;
        }
        arg_2=head_2;
        scanf("%d",&number_2);
    }
}

void move(int M,int x,int y){
    int choice;
    printf("[1] North\n[2] South\n[3] North East\n[4] North West\n[5] South East\n[6] South West\n");
    scanf("%d",&choice);

    if(choice==1){
        if(((y+1)<n)&&(block[x][y+1]!=FORBIDDEN)&&(plate[x][y+1]==0)){
            plate[x][y]=0;
            y++;
            plate[x][y]=1;
        }
    }
    if(choice==2){
        if(((y-1)>=0)&&(block[x][y-1]!=FORBIDDEN)&&(plate[x][y-1]==0)){
            plate[x][y]=0;
            y--;
            plate[x][y]=1;
        }
    }
    if(choice==3){
        if(x%2==0){
            if(((x+1)<n)&&((y+1)<n)&&(block[x+1][y+1]!=FORBIDDEN)&&(plate[x+1][y+1]==0)){
                plate[x][y]=0;
                x++;
                y++;
                plate[x][y]=1;
            }
        }
        else{
            if(((x+1)<n)&&(block[x+1][y]!=FORBIDDEN)&&(plate[x+1][y]==0)){
                plate[x][y]=0;
                x++;
                plate[x][y]=1;
            }
            else{
                printf("\nCan not move.\n\n");
            }
        }
    }
    if(choice==4){
         if(x%2==0){
            if(((x-1)>=0)&&((y+1)<n)&&(block[x-1][y+1]!=FORBIDDEN)&&(plate[x-1][y+1]==0)){
                plate[x][y]=0;
                x--;
                y++;
                plate[x][y]=1;
            }
        }
        else{
            if(((x-1)>=0)&&(block[x-1][y]!=FORBIDDEN)&&(plate[x-1][y]==0)){
                plate[x][y]=0;
                x--;
                plate[x][y]=1;
            }
        }
    }
    if(choice==5){
        if(x%2==0){
            if(((x+1)<n)&&(block[x+1][y]!=FORBIDDEN)&&(plate[x+1][y+1]==0)){
                plate[x][y]=0;
                x++;
                plate[x][y]=1;
            }
        }
        else{
            if(((x+1)<n)&&((y-1)>=0)&&(block[x+1][y-1]!=FORBIDDEN)&&(plate[x+1][y-1]==0)){
                plate[x][y]=0;
                x++;
                y--;
                plate[x][y]=1;
            }
        }
    }
    if(choice==6){
         if(x%2==0){
            if(((x-1)>=0)&&(block[x-1][y]!=FORBIDDEN)&&(plate[x-1][y]==0)){
                plate[x][y]=0;
                x--;
                plate[x][y]=1;
            }
        }
        else{
            if(((x-1)>=0)&&((y-1)>=0)&&(block[x-1][y-1]!=FORBIDDEN)&&(plate[x-1][y-1]==0)){
                plate[x][y]=0;
                x--;
                y--;
                plate[x][y]=1;
            }
        }
    }

    if(M==0){
        arg->x=x;
        arg->y=y;
    }
    if(M==1){
        arg_1->x_1=x;
        arg_1->y_1=y;
    }
    if(M==2){
        arg_2->x_2=x;
        arg_2->y_2=y;
    }
}

void boost_energy(int M,int x,int y){
    int scoree=0;
    if(block[x][y]==ENERGY){
        if(energyy[x][y]>=15){
            scoree=15;
            energyy[x][y]-=15;
        }
        else{
            scoree=energyy[x][y];
            energyy[x][y]=0;
        }
    }
    if(M==0){
        (arg->mitoz)+=scoree;
    }
    if(M==1){
        (arg_1->mitoz_1)+=scoree;
    }
    if(M==2){
        (arg_2->mitoz_2)+=scoree;
    }
    alll_energyy();
}

void alll_energyy(void){
    if(meno_n==2){
        all_energyy=0;
        arg=head;
        for(sh=0;sh<num_cell;sh++){
            all_energyy+=arg->mitoz;
            arg=arg->next;
        }
        arg=head;
    }
    if(meno_n==3){
        all_energyy_1=0;
        all_energyy_2=0;
        arg_1=head_1;
        for(sh=0;sh<num_cell_1;sh++){
            all_energyy_1+=arg_1->mitoz_1;
            arg_1=arg_1->next_1;
        }
        arg_1=head_1;

        arg_2=head_2;
        for(sh=0;sh<num_cell_2;sh++){
            all_energyy_2+=arg_2->mitoz_2;
            arg_2=arg_2->next_2;
        }
        arg_2=head_2;
    }

}

int split_cell(int M,int x,int y){
    int z=0,q=0;;
    if(block[x][y]==MITOSIS){
        while((q<1000)&&(z==0)){
            do{
            sh=(rand()%2);
            sh1=(rand()%2);
            }while((sh==0)&&(sh1==0));

            while((x%2==0)&&(sh1==(-1))){
                if((sh==1)||(sh==(-1))){
                    do{
                    sh=(rand()%2);
                    sh1=(rand()%2);
                    }while((sh!=0)||(sh1!=0));
                }
                else{
                    break;
                }
            }
            while((x%2!=0)&&(sh1==1)){
                if((sh==1)||(sh==(-1))){
                    do{
                    sh=(rand()%2);
                    sh1=(rand()%2);
                    }while((sh!=0)||(sh1!=0));
                }
                else{
                    break;
                }
            }

            if((block[x+sh][y+sh1]!=FORBIDDEN)&&(plate[x+sh][y+sh]==0)&&((x+sh)<n)&&((x-sh)>=0)&&((y+sh1)<n)&&((y-sh1)>=0)){
                plate[x+sh][y+sh1]++;
                z=1;
            }
            else{
                q++;
            }
        }

        if((M==0)&&((arg->mitoz)>80)){
            (arg->mitoz)=40;
            add_cell(0,x+sh,y+sh1);
        }
        if((M==1)&&((arg_1->mitoz_1)>80)){
            (arg_1->mitoz_1)=40;
            add_cell(1,x+sh,y+sh1);
        }
        if((M==2)&&((arg_2->mitoz_2)>80)){
            (arg_2->mitoz_2)=40;
            add_cell(2,x+sh,y+sh1);
        }
        alll_energyy();
    }
    else{
        return 1;
    }
}

void add_cell(int c,int x,int y){
    if(c==0){
        arg=head;
        for(sh=0;sh<num_cell-1;sh++){
            arg=arg->next;
        }
        arg->next=(struct cell *)malloc(sizeof(struct cell));
        arg=arg->next;
        (arg->str)=rand_string(5);
        (arg->x)=x;
        (arg->y)=y;
        (arg->mitoz)=40;
        num_cell++;
        arg=head;
    }
    if(c==1){
        arg_1=head_1;
        for(sh=0;sh<num_cell_1-1;sh++){
            arg_1=arg_1->next_1;
        }
        arg_1->next_1=(struct cell_1 *)malloc(sizeof(struct cell_1));
        arg_1=arg_1->next_1;
        (arg_1->str_1)=rand_string(5);
        (arg_1->x_1)=x;
        (arg_1->y_1)=y;
        (arg_1->mitoz_1)=40;
        num_cell_1++;
        arg=head;
    }
    if(c==2){
        arg_2=head_2;
        for(sh=0;sh<num_cell_2-1;sh++){
            arg_2=arg_2->next_2;
        }
        arg_2->next_2=(struct cell_2 *)malloc(sizeof(struct cell_2));
        arg_2=arg_2->next_2;
        (arg_2->str_2)=rand_string(5);
        (arg_2->x_2)=x;
        (arg_2->y_2)=y;
        (arg_2->mitoz_2)=40;
        num_cell_2++;
        arg=head;
    }
}

void save(void){
    //public
    FILE *pub;
    pub=fopen("pub.bin","wb");

    fwrite(&n,sizeof(int),1,pub);
    fwrite(&meno_n,sizeof(int),1,pub);

    for(sh=0;sh<n;sh++){
        for(sh1=0;sh1<n;sh1++){
            fwrite(&block[sh][sh1],sizeof(int),1,pub);
        }
    }

    for(sh=0;sh<n;sh++){
        for(sh1=0;sh1<n;sh1++){
            fwrite(&energyy[sh][sh1],sizeof(int),1,pub);
        }
    }
    fclose(pub);

    if(meno_n==2){
        FILE *single;
        single=fopen("single.bin","wb");

        fwrite(&num_cell,sizeof(int),1,single);

        arg=head;
        for(sh=0;sh<num_cell;sh++){
            fwrite(&arg->x,sizeof(int),1,single);
            fwrite(&arg->y,sizeof(int),1,single);
            fwrite(&arg->mitoz,sizeof(int),1,single);
            fwrite(&arg->str,sizeof(strlen(arg->str)+1),1,single);
            arg=arg->next;
        }
        arg=head;
        fclose(single);
    }
    if(meno_n==3){
        //player 1
        FILE *multi_1;
        multi_1=fopen("multi_1.bin","wb");

        fwrite(&num_cell_1,sizeof(int),1,multi_1);

        arg_1=head_1;
        for(sh=0;sh<num_cell_1;sh++){
            fwrite(&arg_1->x_1,sizeof(int),1,multi_1);
            fwrite(&arg_1->y_1,sizeof(int),1,multi_1);
            fwrite(&arg_1->mitoz_1,sizeof(int),1,multi_1);
            fwrite(&arg_1->str_1,sizeof(strlen(arg_1->str_1)+1),1,multi_1);
            arg_1=arg_1->next_1;
        }
        arg_1=head_1;
        fclose(multi_1);

        //player 2
        FILE *multi_2;
        multi_2=fopen("multi_2.bin","wb");

        fwrite(&num_cell_2,sizeof(int),1,multi_2);

        arg_2=head_2;
        for(sh=0;sh<num_cell_2;sh++){
            fwrite(&arg_2->x_2,sizeof(int),1,multi_2);
            fwrite(&arg_2->y_2,sizeof(int),1,multi_2);
            fwrite(&arg_2->mitoz_2,sizeof(int),1,multi_2);
            fwrite(&arg_2->str_2,sizeof(strlen(arg_2->str_2)+1),1,multi_2);
            arg_2=arg_2->next_2;
        }
        arg_2=head_2;
        fclose(multi_2);
    }

}

void load(void){
    //public
    FILE *pub;
    pub=fopen("pub.bin","rb");

    fread(&n,sizeof(int),1,pub);
    fread(&meno_n,sizeof(int),1,pub);

    //blocks
    block=(int **)malloc(n*sizeof(int *));
        for(sh=0;sh<n;sh++){
            block[sh]=(int *)malloc(n*sizeof(int));
    }

    //plate
    plate=(int **)malloc(n*sizeof(int *));
    for(sh=0;sh<n;sh++){
        plate[sh]=(int *)malloc(n*sizeof(int));
    }
    for(sh=0;sh<n;sh++){
        for(sh1=0;sh1<n;sh1++){
            plate[sh][sh1]=0;
        }
    }

    //mitoz blocks
    energyy=(int **)malloc(n*sizeof(int *));
    for(sh=0;sh<n;sh++){
        energyy[sh]=(int *)malloc(n*sizeof(int));
    }


    for(sh=0;sh<n;sh++){
        for(sh1=0;sh1<n;sh1++){
            fread(&block[sh][sh1],sizeof(int),1,pub);
        }
    }

    for(sh=0;sh<n;sh++){
        for(sh1=0;sh1<n;sh1++){
            fread(&energyy[sh][sh1],sizeof(int),1,pub);
        }
    }
    fclose(pub);

    counter=1;
    counter_1=1;
    counter_2=1;

    if(meno_n==2){
        FILE *single;
        single=fopen("single.bin","rb");

        fread(&num_cell,sizeof(int),1,single);

        head=(struct cell *)malloc(sizeof(struct cell));
        arg=head;
        for(sh=0;sh<num_cell;sh++){
            fread(&arg->x,sizeof(int),1,single);
            fread(&arg->y,sizeof(int),1,single);
            plate[arg->x][arg->y]=1;
            fread(&arg->mitoz,sizeof(int),1,single);
            fread(&arg->str,sizeof(strlen(arg->str)+1),1,single);
            arg->str=rand_string(5);
            arg->next=(struct cell *)malloc(sizeof(struct cell));
            arg=arg->next;
        }
        arg=head;
        fclose(single);
    }
    if(meno_n==3){
        FILE *multi_1;
        multi_1=fopen("multi_1.bin","rb");

        fread(&num_cell_1,sizeof(int),1,multi_1);

        head_1=(struct cell_1 *)malloc(sizeof(struct cell_1));
        arg_1=head_1;
        for(sh=0;sh<num_cell_1;sh++){
            fread(&arg_1->x_1,sizeof(int),1,multi_1);
            fread(&arg_1->y_1,sizeof(int),1,multi_1);
            plate[arg_1->x_1][arg_1->y_1]=1;
            fread(&arg_1->mitoz_1,sizeof(int),1,multi_1);
            fread(&arg_1->str_1,sizeof(strlen(arg_1->str_1)+1),1,multi_1);
            arg_1->str_1=rand_string(5);
            arg_1->next_1=(struct cell_1 *)malloc(sizeof(struct cell_1));
            arg_1=arg_1->next_1;
        }
        arg_1=head_1;
        fclose(multi_1);


        FILE *multi_2;
        multi_2=fopen("multi_2.bin","rb");

        fread(&num_cell_2,sizeof(int),1,multi_2);

        head_2=(struct cell_2 *)malloc(sizeof(struct cell_2));
        arg_2=head_2;
        for(sh=0;sh<num_cell_2;sh++){
            fread(&arg_2->x_2,sizeof(int),1,multi_2);
            fread(&arg_2->y_2,sizeof(int),1,multi_2);
            plate[arg_2->x_2][arg_2->y_2]=1;
            fread(&arg_2->mitoz_2,sizeof(int),1,multi_2);
            fread(&arg_2->str_2,sizeof(strlen(arg_2->str_2)+1),1,multi_2);
            arg_2->str_2=rand_string(5);
            arg_2->next_2=(struct cell_2 *)malloc(sizeof(struct cell_2));
            arg_2=arg_2->next_2;
        }
        arg_2=head_2;
        fclose(multi_2);
    }

    alll_energyy();
}

void freee(void){
    free(block);
    free(plate);
    free(energyy);

    if(meno_n==2){
        arg=head;
        for(sh=0;sh<num_cell-1;sh++){
            arg=arg->next;
            free(head);
            head=arg;
        }
    }
    if(meno_n==3){
         arg_1=head_1;
        for(sh=0;sh<num_cell_1-1;sh++){
            arg_1=arg_1->next_1;
            free(head_1);
            head_1=arg_1;
        }
        arg_2=head_2;
        for(sh=0;sh<num_cell_2;sh++){
            arg_2=arg_2->next_2;
            free(head_2);
            head_2=arg_2;
        }
    }
}

int main(){
    srand(time(NULL));

    if(meno()==4){
        freee();
        return 0;
    }

    system("cls");
    map(n);

    while(1){
        if(work_in_cells()==5){
            freee();
            return 0;
        }
    }
    freee();
    return 0;
}
