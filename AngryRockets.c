#include <stdio.h>
#define R_MAX 2147483647 // vsetky generovane cisla su mensie ako R_MAX
static long long unsigned int SEED = 0x1; // seed generatora

void srnd(int seed) {
    SEED = seed;
}

int rnd(int from, int to) {
    SEED = SEED * 16807 % R_MAX;
    return from + (int) SEED % (to - from + 1);
}

int MAX(int a, int b){
    if(a>=b){return a;} else {return b;}
}
void swap(int *a, int *b){
    int tmp = *a;    *a = *b;    *b = tmp;
}

int main() {                            // 17 48 16 0
    int seed,n,m1,m2,i;   int pblock=0,pboost=0,  x;

    scanf("%d %d %d %d",&seed,&n,&m1,&m2);
    if ( seed<=0 || n<10 || n>100 || (m1+m2)>(n/2)) {return 1;}
    srnd(seed);

    int p[n];                                           //inicializacia pola velkosti n prvkov
    for (i=0;i<=(n-1);i++) { p[i]=0;}                   //nastavenie celeho pola na hodnotu 0

    //BLOCKER
    while (pblock!=m1){
        x=rnd(1,(n-1));
        if (p[x]==0){ p[x]=88; pblock=pblock+1;}
    }
    printf("\nBLOCK:");
    for (i=0;i<=(n-1);i++){
        if (p[i]==88){printf("%d ",i);}
    }

    //BOOSTER
    while (pboost!=m2){
        x=rnd(1,(n-1));
        if (p[x]==0){ p[x]=99; pboost=pboost+1; }
    }
    printf("\nBOOST:");
    for (i=0;i<=(n-1);i++){
        if (p[i]==99){printf("%d ",i);}
    }

    int t=0, R1,R2,d=0,HRAC,max;                            //vseobecne premenne vyuzivane v celom programe
    int Ph1=-1,minPoz1,BOOST1=0,BOOST1b=0;                  //premenne vyuzivane pri 1. hracovi
    int Ph2=-1,minPoz2,BOOST2=0,BOOST2b=0;                  //premenne vyuzivane pri 2. hracovi
    while (Ph1<n && Ph2<n){
        if (Ph1==-1){                                       //INICIALIZACIA PRVEHO HRACA
            t=t+1;
            HRAC=1;
            minPoz1=Ph1;
            R1=rnd(1,6);
            R2=rnd(1,6);
            if ((R1+R2)>7){
                d=1+(R1+R2-7)+BOOST1;
                Ph1=Ph1+d;
                p[Ph1]=p[Ph1]+1;
                if(p[Ph1]==99+1) {BOOST1++; p[Ph1]=1;}
                if(p[Ph1]==88+1 && BOOST1==0) {p[Ph1]=1; Ph1=-1; }
                else if(p[Ph1]==88+1 && BOOST1>0) { BOOST1=0; p[Ph1]=0; }
                }}
         else if (Ph1>=0){
             BOOST1b=BOOST1;
            t++;HRAC=1;minPoz1=Ph1;
            R1=rnd(1,6);
            R2=rnd(1,6);
            if((R1==6 && R2==6 && Ph1<Ph2 && Ph1>-1) || (R1==1 && R2==1 && Ph1>Ph2 && Ph2>-1)){
                d=0;swap(&Ph1,&Ph2);
                p[Ph1]=p[Ph1]+1;
                p[Ph2]=p[Ph2]+1;}
            else {
                d=MAX(R1,R2);
                Ph1=minPoz1+d+BOOST1;
                if (Ph1>(n-1)) {printf("\n[%d,%d] [%d,%d] [%d,%d] [%d,%d]",t,HRAC,minPoz1,BOOST1b,R1,R2,Ph1,BOOST1);break;}                               //NOVY DODATOK
                p[Ph1]=p[Ph1]+1;
                if(p[Ph1]==99+1) {BOOST1++; p[Ph1]=1;}
                if(p[Ph1]==88+1 && BOOST1==0) {p[Ph1]=1; Ph1=-1; }
                else if(p[Ph1]==88+1 && BOOST1>0) { BOOST1=0; p[Ph1]=1; }
         }}
         if(Ph1==Ph2){ Ph2=-1; BOOST2b=BOOST2;}                     // UPRAVENA PODMIENKA PRE BOOSTRE
        printf("\n[%d,%d] [%d,%d] [%d,%d] [%d,%d]",t,HRAC,minPoz1,BOOST1b,R1,R2,Ph1,BOOST1);

         //if(Ph1>n){ break; }
        if (Ph2==-1){                                               //INICIALIZACIA DRUHEHO HRACA
            t=t+1;
            HRAC=2;
            minPoz2=Ph2;
            R1=rnd(1,6);
            R2=rnd(1,6);
            if ((R1+R2)>7){
                d=1+(R1+R2-7)+BOOST2;
                Ph2=Ph2+d;
                p[Ph2]=p[Ph2]+1;
                if(p[Ph2]==99+1) { BOOST2++; p[Ph2]=1; }
                if(p[Ph2]==88+1 && BOOST2==0) { p[Ph2]=1; Ph2=-1; }
                else if(p[Ph2]==88+1 && BOOST2>0) { BOOST2=0; p[Ph2]=0; }
            }}
        else if (Ph2>=0){
            BOOST2b=BOOST2;
            t++;HRAC=2;minPoz2=Ph2;
            R1=rnd(1,6);
            R2=rnd(1,6);
            if((R1==6 && R2==6 && Ph2<Ph1 && Ph2>-1) || (R1==1 && R2==1 && Ph2>Ph1 && Ph1>-1)){
                d=0;swap(&Ph2,&Ph1);
                p[Ph2]=p[Ph2]+1;
                p[Ph1]=p[Ph1]+1;}
            else {
                d=MAX(R1,R2);
                Ph2=minPoz2+d+BOOST2;
                if (Ph2>(n-1)) {printf("\n[%d,%d] [%d,%d] [%d,%d] [%d,%d]",t,HRAC,minPoz2,BOOST2b,R1,R2,Ph2,BOOST2); break;}
                p[Ph2]=p[Ph2]+1;
                if(p[Ph2]==99+1) { BOOST2++; p[Ph2]=1; }
                if(p[Ph2]==88+1 && BOOST2==0) { p[Ph2]=1; Ph2=-1; }
                else if(p[Ph2]==88+1 && BOOST2>0) { BOOST2=0; p[Ph2]=1; }
        }}
        if(Ph2==Ph1){ Ph1=-1; BOOST1b=BOOST1;}                  //UPRAVENA PODMIENKA PRE BOOSTRE
        printf("\n[%d,%d] [%d,%d] [%d,%d] [%d,%d]",t,HRAC,minPoz2,BOOST2b,R1,R2,Ph2,BOOST2);
        }

    if(Ph1>=n){ printf("\nWINNER:1");} else { printf("\nWINNER:2");}

    //HOTSPOT
    for (i=0;i<=(n-1);i++){
        if(p[i]>=88 && p[i]<99) {p[i]=p[i]-88;}
        else if (p[i]>=99) {p[i]=p[i]-99;}
    }
    max=p[0];
    for (i=0;i<=(n-1);i++){
        if(p[i]>max) { max = p[i];} else { continue; }
    }
    printf("\nHOTSPOT:%d",max);

    return 0;
}