#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

int n,m,kal;
int plate[100][100];
int xp[20][20];
int yp[20][20];
int xr,yr;
int num_polic[20];

//functions
void getting_detale(void);
void first_places(void);
void map(void);
int put(int z,int x);
int go_to_robber(void);
int see(int a,int b);
void smart_move(int a);
void random_move(int a);
int finish(void);


void getting_detale(void){
    int i;
    printf("write numbers of satr and soton:    ");
    scanf("%d%d",&n,&m);
    printf("\nHow many kalantary do you want?     ");
    scanf("%d",&kal);

    for(i=0;i<kal;i++){
        printf("\nNumbers of polices in %dth kalantary:    ",(i+1));
        scanf("%d",&(num_polic[i]));
    }
}

void first_places(void){
    int i,j;
    //frame
    for(i=0;i<(n+2);i++){
        plate[i][0]=3;
        plate[i][m+1]=3;
    }
    for(j=0;j<(m+2);j++){
        plate[0][j]=3;
        plate[n+1][j]=3;
    }

    //table
    for(i=1;i<=n;i++){
        for(j=1;j<=m;j++){
            plate[i][j]=0;
        }
    }


    for(i=0;i<kal;i++){
        for(j=0;j<num_polic[i];j++){
            do{
                xp[i][j]=((rand()%n)+1);
                yp[i][j]=((rand()%m)+1);
            }while((plate[xp[i][j]][yp[i][j]]!=0)&&(plate[xp[i][j]][yp[i][j]]!=3));
            plate[xp[i][j]][yp[i][j]]=1;
        }
    }


    do{
        xr=((rand()%n)+1);
        yr=((rand()%m)+1);
    }while((plate[xr][yr]!=0)&&(plate[xr][yr]!=3));
    plate[xr][yr]=2;
}

void map(void){
    int z,x;
    printf("\n");
    for(z=1;z<=n;z++){
        printf("|");
        for(x=1;x<=m;x++){
            printf("----|");
        }printf("\n");


        printf("|");
        for(x=1;x<=m;x++){
            if(put(z,x)==0){
                printf(" @@ |");
            }
        }printf("\n");
    }

    printf("|");
    for(x=1;x<=m;x++){
        printf("----|");
    }printf("\n");
}

int put(int z,int x){
    int Q=0;
    int sh,sh1;
    if(finish()==1){
        return 0;
    }

    if((xr==z)&&(yr==x)){
        printf(" RB |");
        Q++;
    }

    for(sh=0;sh<kal;sh++){
        for(sh1=0;sh1<num_polic[sh];sh1++){
            if((xp[sh][sh1]==z)&&(yp[sh][sh1]==x)){
                printf(" P%d |",(sh+1));
                Q++;
            }
        }
    }
    if(Q==0){
        printf("    |");
    }
}

int go_to_robber(void){
    int a,b;
    while(finish()!=1){

        system("cls");
        map();
        Sleep(500);

        for(a=0;a<kal;a++){
            int q=0;

            for(b=0;b<num_polic[a];b++){
                if(see(a,b)==1){
                    smart_move(a);
                    q=1;
                    b=num_polic[a];
                }
            }
            if(q==0){
                random_move(a);
            }
        }

         random_move_robber();
    }
    return 1;
}

int see(int a,int b){
    if((xr<=(xp[a][b]+2))&&(xr>=(xp[a][b]-2))&&(yr<=(yp[a][b]+2))&&(yr>=(yp[a][b]-2))){
        return 1;
    }
    else{
        return 0;
    }
}

void smart_move(int a){
    int sh;

    for(sh=0;sh<num_polic[a];sh++){
        int A=0,B=0;

        if(xr>xp[a][sh]){
            A=1;
        }
        if(xr<xp[a][sh]){
            A=(-1);
        }
        if(yr>yp[a][sh]){
            B=1;
        }
        if(yr<yp[a][sh]){
            B=(-1);
        }

        if((A!=0)&&(B!=0)){
            if((plate[xp[a][sh]+A][yp[a][sh]+B]!=1)&&(plate[xp[a][sh]+A][yp[a][sh]+B]!=3)){
                plate[xp[a][sh]][yp[a][sh]]=0;
                xp[a][sh]+=A;
                yp[a][sh]+=B;
                plate[xp[a][sh]][yp[a][sh]]=1;
            }
            else if((plate[xp[a][sh]][yp[a][sh]+B]!=1)&&(plate[xp[a][sh]][yp[a][sh]+B]!=3)){
                plate[xp[a][sh]][yp[a][sh]]=0;
                yp[a][sh]+=B;
                plate[xp[a][sh]][yp[a][sh]]=1;
            }
            else if((plate[xp[a][sh]+A][yp[a][sh]]!=1)&&(plate[xp[a][sh]+A][yp[a][sh]]!=3)){
                plate[xp[a][sh]][yp[a][sh]]=0;
                xp[a][sh]+=A;
                plate[xp[a][sh]][yp[a][sh]]=1;
            }
        }
        if((B!=0)&&(A==0)){
            if((plate[xp[a][sh]][yp[a][sh]+B]!=1)&&(plate[xp[a][sh]][yp[a][sh]+B]!=3)){
                plate[xp[a][sh]][yp[a][sh]]=0;
                yp[a][sh]+=B;
                plate[xp[a][sh]][yp[a][sh]]=1;
            }
            else if((plate[xp[a][sh]-1][yp[a][sh]+B]!=1)&&(plate[xp[a][sh]-1][yp[a][sh]+B]!=3)){
                plate[xp[a][sh]][yp[a][sh]]=0;
                xp[a][sh]--;
                yp[a][sh]+=B;
                plate[xp[a][sh]][yp[a][sh]]=1;
            }
            else if((plate[xp[a][sh]+1][yp[a][sh]+B]!=1)&&(plate[xp[a][sh]+1][yp[a][sh]+B]!=3)){
                plate[xp[a][sh]][yp[a][sh]]=0;
                xp[a][sh]++;
                yp[a][sh]+=B;
                plate[xp[a][sh]][yp[a][sh]]=1;
            }
        }
        if((A!=0)&&(B==0)){
            if((plate[xp[a][sh]+A][yp[a][sh]]!=1)&&(plate[xp[a][sh]+A][yp[a][sh]]!=3)){
                plate[xp[a][sh]][yp[a][sh]]=0;
                xp[a][sh]+=A;
                plate[xp[a][sh]][yp[a][sh]]=1;
            }
            else if((plate[xp[a][sh]+A][yp[a][sh]-1]!=1)&&(plate[xp[a][sh]+A][yp[a][sh]-1]!=3)){
                plate[xp[a][sh]][yp[a][sh]]=0;
                xp[a][sh]+=A;
                yp[a][sh]--;
                plate[xp[a][sh]][yp[a][sh]]=1;
            }
            else if((plate[xp[a][sh]+A][yp[a][sh]+1]!=1)&&(plate[xp[a][sh]+A][yp[a][sh]+1]!=3)){
                plate[xp[a][sh]][yp[a][sh]]=0;
                xp[a][sh]+=A;
                yp[a][sh]++;
                plate[xp[a][sh]][yp[a][sh]]=1;
            }
        }
    }
}

void random_move(int a){
    int e;
    int aa,bb;

    for(e=0;e<num_polic[a];e++){
        do{
            aa=(rand()%3)-1;
            bb=(rand()%3)-1;
        }while((plate[xp[a][e]+aa][yp[a][e]+bb]==1)||(plate[xp[a][e]+aa][yp[a][e]+bb]==3));
        plate[xp[a][e]][yp[a][e]]=0;
        xp[a][e]+=aa;
        yp[a][e]+=bb;
        plate[xp[a][e]][yp[a][e]]=1;
    }
}

void random_move_robber(void){
    int c,d;
    do{
        c=(rand()%3)-1;
        d=(rand()%3)-1;
    }while(plate[xr+c][yr+d]==3);
    plate[xr][yr]=0;
    xr+=c;
    yr+=d;
    plate[xr][yr]=2;
}

int finish(void){
    int v,b;
    for(v=0;v<kal;v++){
        for(b=0;b<num_polic[v];b++){
            if((xr==xp[v][b])&&(yr==yp[v][b])){
                return 1;
            }
        }
    }
    return 0;
}

int main(){
    srand(time(NULL));

    getting_detale();
    system("cls");
    first_places();
    map();

    if(go_to_robber()==1){
        return 0;
    }

    return 0;
}
