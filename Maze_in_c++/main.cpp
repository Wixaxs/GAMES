#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <cstdlib>
#include <ctime>


using namespace std;
// zeby dzialalo
int abywlaczyc=0;
// deklaracja mapy
string map[16][16];
// kordy poczatkowe psotaci
int postacx=7,postacy=7;
// zycko
int zycie=3;
// gameover
int gameover=0;
// menu
string opcjemenu[4];
int wybormenu=1;
void menu();
void podlinkimenu();
void sterowaniemenu();
// deklaracja zmienncyh
void mapa();
void pokazaniemapy();
void movement();
void postac();
void wewmapy();
void inimapy();
// wypisanie mapy
void mapa(){
        // wpsiwanie mapy w tablice //
    for (int i=0;i<16;i++){
        map[0][i]="-";
    }
    for (int i=0;i<16;i++){
        map[15][i]="-";
    }
    for (int i=1;i<15;i++){
        map[i][0]="|";
    }
    for (int i=1;i<15;i++){
        map[i][15]="|";
    }
    for (int i=1;i<15;i++){
        for (int j=1;j<15;j++){
        map[i][j] = " ";
        }
    }
}
// pokazanie mapy
void pokazaniemapy(){
    for (int i=0;i<16;i++){
        for (int j=0;j<16;j++){
        cout << map[i][j];
        // jezeli dotyka sciany //
        if (j==(15)){
            cout << endl;
        }
    }
    }
}

// gostek
void postac(){
    map[postacy][postacx]="&";
}

// wewnatrz kmapy
void wewmapy(){
    // warstwa 1
    map[1][1]="#";
    map[1][2]="#";
    map[1][5]="#";
    map[1][7]="#";
    map[1][9]="#";
    map[1][10]="#";
    map[1][14]="#";
    // warstwa 2
    map[2][2]="#";
    map[2][3]="#";
    map[2][5]="#";
    map[2][7]="#";
    map[2][9]="#";
    map[2][12]="#";
    // warstwa 3
    map[3][2]="#";
    map[3][3]="#";
    // warstwa 4
    map[4][2]="#";
    map[4][3]="#";
    map[4][4]="#";
    map[4][5]="#";
    map[4][6]="#";
    map[4][7]="#";
    map[4][8]="#";
    map[4][9]="#";
    map[4][10]="#";
    map[4][12]="#";
    map[4][14]="#";
    // warstwa 6
    map[6][2]="#";
    map[6][3]="#";
    // warstwa 8
    map[8][1]="#";
    map[8][2]="#";
    map[8][3]="#";
    map[8][4]="#";
    map[8][5]="#";
    map[8][6]="#";
    map[8][7]="#";
    map[8][9]="#";
    map[8][10]="#";
    map[8][11]="#";
    map[8][12]="#";
    map[8][13]="#";
    map[8][14]="#";
    // warstwa 9
    map[9][1]="#";
    map[9][2]="#";
    map[9][3]="#";
    map[9][4]="#";
    map[9][5]="#";
    map[9][6]="#";
    map[9][10]="#";
    map[9][11]="#";
    map[9][12]="#";
    map[9][13]="#";
    map[9][14]="#";
    // warstwa 10
    map[10][1]="#";
    map[10][2]="#";
    map[10][3]="#";
    map[10][4]="#";
    map[10][5]="#";
    map[10][8]="#";
    map[10][14]="#";
    // warstwa 11
    map[11][1]="#";
    map[11][2]="#";
    map[11][3]="#";
    map[11][7]="#";
    map[11][10]="#";
    map[11][12]="#";
    // warstwa 12
    map[12][1]="#";
    map[12][2]="#";
    map[12][6]="#";
    map[12][9]="#";
    map[12][13]="#";
    // warstwa 13
    map[13][1]="#";
    map[13][4]="#";
    map[13][8]="#";
    map[13][11]="#";
    // warstwa 14
    map[14][1]="#";
    map[14][3]="#";
    map[14][6]="#";
    map[14][10]="#";
    map[14][13]="#";
}

// inicjalizacja mapy
void inimapy(){
    mapa();
    wewmapy();
    postac();
}
void pulapka(){
    system("cls");
    cout << "wpadles w pulapke" << endl;
    Sleep(1000);
    postacx=7;
    postacy=7;
}
void movement(char wsad){
    switch (wsad)
    {
    case 'w':
    if(map[postacy-1][postacx]!="#" && map[postacy-1][postacx]!="|" && map[postacy-1][postacx]!="-" ){
                postacy-=1;
    }
        break;
    case 'd':
    if(map[postacy][postacx+1]!="#" && map[postacy][postacx+1]!="|" && map[postacy][postacx+1]!="-"){
                postacx+=1;
    }
    break;
    case 'a':
    if(map[postacy][postacx-1]!="#" && map[postacy][postacx-1]!="|" && map[postacy][postacx-1]!="-"){
                postacx-=1;
    }
    break;
    case 's':
    if(map[postacy+1][postacx]!="#" && map[postacy+1][postacx]!="-" && map[postacy+1][postacx]!="|"){
                postacy+=1;
    }
    break; 
    }
}
void miejsca(){
    if( map[1][4]=="&" || map[1][8]=="&" || map[1][11]=="&" || map[1][12]=="&"  || map[2][2]=="&" || map[14][2]=="&" || map[14][4]=="&" 
    || map[14][5]=="&"  || map[14][9]=="&" || map[14][11]=="&" ||  map[14][14]=="&"){
        zycie-=1;
        pulapka();
    }
    else if( map[14][7]=="&"){
        gameover=1;
    }
    
}
void logikagry(){
    if(zycie==0){
        system("cls");
        cout << "Straciles zycia";
        Sleep(1000);
        gameover=2;
    }
}
void przegrana(){
    if (gameover==2)
    {
        system("cls");
        cout << "przegrales";
        Sleep(1000);
    }
}
void wygrana(){
    if(gameover==1){
    cout << "WYGRALES";
    Sleep(1000);
    }
}
void zycka(){
    cout << endl ;
    for (int i=0;i<zycie;i++){
        cout << " <3" ;
    }
    cout << endl;
}
void gra (){
    while(gameover==0){
    miejsca();
    inimapy();
    pokazaniemapy();
    zycka();
    logikagry();
    przegrana();
    if(gameover!=2){
    movement(getch());
    }
    inimapy();
    system("cls");
    wygrana();
    }
}

void podlinkimenu(char back){
        switch(back)
        {
        case 'b':
        menu();
        break;
        }
}

void sterowaniemenu(char ws){
    switch (ws)
    {
    case 'w':
        wybormenu-=1;
        if(wybormenu==0){wybormenu=3;}
        break;
    
    case 's':
        wybormenu+=1;
        if(wybormenu==4){wybormenu=1;}
        break;
    case 'e':
    switch (wybormenu)
    {
    case 1:
    system("cls");
    cout << "Patryk Wawrzynek" << endl;
    cout << "Nacisnij 'b' aby wrocic";
    podlinkimenu(getch());
    break;
    case 2:
    system("cls");
    cout << "W = do gory | S = w dol | D = w prawo | A = w lewo" << endl;
    cout << "Nacisnij 'b' aby wrocic";
    podlinkimenu(getch());
    break;
    case 3:
    system("cls");
    abywlaczyc+=1;
    gra();
    break;
    }
    }
}
void menu(){
    opcjemenu[1]="  Autorzy projektu";
    opcjemenu[2]="    Sterowanie";
    opcjemenu[3]="       Graj";
    cout << "      The Maze" << endl << endl;
    for (int i=1;i<=3;i++){
        if (wybormenu==i){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED );
        cout <<opcjemenu[i] << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE );
        }
        else {
            cout <<  opcjemenu[i] << endl;
        }
    }
    cout << endl;
    cout << "   Potwierdz 'e'"<< endl;
    cout << "w-do gory || s-w dol" << endl;
}
int main(){
    while(abywlaczyc==0){
    menu();
    sterowaniemenu(getch());
    system("cls");
    }
    return 0;
}
