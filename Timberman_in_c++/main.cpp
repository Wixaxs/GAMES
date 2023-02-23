#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>

using namespace std;
// lodyga i strona lewa czy prawa
string lodyga[3];
int strona[2];

// x wielkosc mapy
int x=12;

// mapa glowna 
string map[12][12];
// 1 2 3 4 5 6 7 8 9 10 11

// zeby byl
int k=1;
// punkty
int pkt=0;
//dla zycia drwala
int zycko;
// tabela dla zapisywania stron lodyg
int stronalodygidlausuwania[11];

// kierunki dla map itp
int pion=1,poziom=5,piondrzewo=1;
// kierunki dla drwala
int poziomdrwal=5,piondrwal=11;
// randomowe liczby 
int randstrona,randlodyga;
// 
int l = 5,p =7;
// licznik ruchow drwala
int licznikruchow;
// deklarowanie zmiennych //
void gameover(int zycia);
void mapa();
void drwal();
void drzewo();
void randomoweliczby();
void lodygi();
void pokazaniemapy();
void inimapy();
void movement();
void drwalusuniecie();
void usuwaniedrzewa();
void start();
void napis();
void menu();
void enter();
// koniec //

// MENU //
// aby zaczac //
void enter(char enter){
    switch(enter){
        case 'e':
        k+=1;
        system("cls");
        break;
    }
}

// napis timberman //
 void napis(){
    string napiss[9];
    napiss[0]="TTTTTTTTTTT   III   MMMM              MMMM   BBBBBBBBBB       EEEEEEEEEEE   RRRRRRRRRR       MMM              MMM         AA        NNNN      NNNN";
    napiss[1]="TTTTTTTTTTT   III   MMMMM            MMMMM   BBBB   BBBB      EEEEEEEEEEE   RRR       RRR   MMMMM            MMMMM      AAAAAA      NNNNN     NNNN";
    napiss[2]="TTTTTTTTTTT   III   MMMMMM          MMMMMM   BBB      BBBB    EEE           RR         RR   MMMMMM          MMMMMM    AAA    AAA    NNNNNN    NNNN";
    napiss[3]="   TTTTT      III   MMMMMMM        MMMMMMM   BBBB    BBBBBB   EEE           RRR       RRR   MMMMMMM        MMMMMMM   AAA      AAA   NNNNNNN   NNNN";
    napiss[4]="   TTTTT      III   MMM  MMM      MMM  MMM   BBBBBBBBBBBBB    EEEEEEEEEEE   RRRRRRRRRR      MMMM MMM      MMM MMMM   AAAAAAAAAAAA   NNNN NNN  NNNN";
    napiss[5]="   TTTTT      III   MMM   MMM   MMMM  MMMM   BBBB   BBBBB     EEE           RRR    RRR      MMMM  MMM   MMMM  MMMM   AAAAAAAAAAAA   NNNN  NNN NNNN";
    napiss[6]="   TTTTT      III   MMM    MMM MMM    MMMM   BBB      BBBB    EEE           RRR     RRR     MMMM   MMM MMM    MMMM   AAA      AAA   NNNN    NNNNNN";
    napiss[7]="   TTTTT      III   MMM     MMMMM     MMMM   BBBB    BBBBBB   EEEEEEEEEEE   RRR      RRR    MMMM    MMMMM     MMMM   AAA      AAA   NNNN     NNNNN";
    napiss[8]="   TTTTT      III   MMM      MMM      MMMM   BBBBBBBBBBBBB    EEEEEEEEEEE   RRR       RRR   MMMM     MMM      MMMM   AAA      AAA   NNNN      NNNN";

for(int i=0;i<9;i++){
    cout << napiss[i] << endl;
}
}
void menu(){
    napis();
    cout <<"                                                                      Press e to start";
    enter(getch());
}

// prousznaiie sie //
void movement(char ad){
    switch(ad){
        case 'a':
        pkt+=1;
        if(map[9][5]=="-"){
            gameover(0);
        }
        else{
            gameover(1);
        }
        licznikruchow+=1;
        drwalusuniecie();
        poziomdrwal=5;
        system("cls");
        usuwaniedrzewa();
                drwal();
        pokazaniemapy();
        break;
        case 'd':
        pkt+=1;
        if(map[9][7]=="-"){
            gameover(0);
        }
        else{
            gameover(1);
        }
        licznikruchow+=1;
        drwalusuniecie();
        poziomdrwal=7;
        system("cls");
        usuwaniedrzewa();
        drwal();
        pokazaniemapy();
        break;
    }
}
void usuwaniedrzewa(){
    srand(time(NULL));
    lodyga[0]='-';
    lodyga[1]=" ";
    strona[0]=5;
    strona[1]=7;
    randstrona = rand()%2;
    randlodyga = rand()%2;
    
    if (licznikruchow!=0){
        for (int i=10;i>1;i--){
            map[i][5]=map[i-1][5];
            map[i][7]=map[i-1][7];

        }
    randstrona = rand()%2;
    randlodyga = rand()%2;
    // jezeli lodyga jest po ktroes stornie to aby druga byla pusta
    map[1][strona[randstrona]]=lodyga[randlodyga];
    if(randlodyga==0 && randstrona == 0){
        map[1][7]=" ";
    }
    else if(randlodyga==0 && randstrona == 1){
        map[1][5]=" ";
    }
    }
}
void drwalusuniecie(){
    map[piondrwal-1][poziomdrwal] = " ";
}
void mapa(){
    // wpsiwanie mapy w tablice //
    for (int i=0;i<12;i++){
        map[0][i]="-";
    }
    for (int i=0;i<12;i++){
        map[11][i]="-";
    }
    for (int i=1;i<11;i++){
        map[i][0]="|";
    }
    for (int i=1;i<11;i++){
        map[i][11]="|";
    }
    for (int i=1;i<11;i++){
        for (int j=1;j<11;j++){
        map[i][j] = " ";
        }
    }
}
void pokazaniemapy(){
    // pokazanie mapy //
    for (int i=0;i<12;i++){
        for (int j=0;j<12;j++){
        cout << map[i][j];
        // jezeli dotyka sciany //
        if (j==(11)){
            cout << endl;
        }
    }
    }
    cout << endl <<"Punkty: "<< pkt << endl;
}
void drwal(){
    map[piondrwal-1][poziomdrwal] = "&";
}
void drzewo (){
    for (int i=1;i<11;i++){
    map[i][6] = "H";
    }
}
void lodygi(){

    srand(time(NULL));
    lodyga[0]='-';
    lodyga[1]=" ";
    strona[0]=5;
    strona[1]=7;
    // pierwsze drzewo 
    if(licznikruchow==0){
    for (int i=0;i<11;i++){
    randstrona = rand()%2;
    randlodyga = rand()%2;
    stronalodygidlausuwania[i]=randstrona;
    map[piondrzewo][strona[randstrona]]=lodyga[randlodyga];
    piondrzewo++;
    }
    }
}
void inimapy(){
    mapa();
    drzewo();
    lodygi();
    drwal();
    pokazaniemapy();
}
void start(){
    inimapy();
    while (zycko==0){
    movement(getch());
    }

}
void gameover(int zycia){
    switch (zycia)
    {
    case 0:
    zycko=1;
    break;
    
    case 1:
    zycko=0;
        break;
    }
}
void przegrana(){
    cout << "Przegrales z iloscia punktow: "<< pkt-1;
}
int main()
{
    
    while(k==1){
        menu();
    }
        start();
        system("cls");
        przegrana();

}
