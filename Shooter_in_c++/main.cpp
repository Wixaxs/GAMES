#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <cstdlib>

using namespace std;
int x=17;
string map [100][100];
int pion=x-1,poziom=(x/2)+1;
int zmiennatarczy;
int punkty;
// zmiena dla leveli 
int lvl=1, lvlwybor=0;
// tabela z trudny sredni latwy
string trudnosc[4];
// do czasu 
clock_t startt,stop;
double czas;

void start();
void strzalka();
void tarcza();
void mapa();
void pokazaniemapy();
void wystrzal();
void movement();
void tarczaczas();

void menu (){
    trudnosc[1] = "trudny";
    trudnosc[2] = "sredni";
    trudnosc[3] = "latwy";
}
void pokazaniemenu (){
    cout << "             Wybierz trudnosc" << endl;
    for (int i=1;i<=3;i++){
        if (lvl==i){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED );
        cout << "                  " <<trudnosc[i] << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE );
        }
        else {
            cout << "                  " << trudnosc[i] << endl;
        }
    }
    cout << "              Potwierdz 'e'"<< endl;
    cout << "          w-do gory || s-w dol" << endl;
}
void movementmenu (char level){
    switch(level){
    case 'w':
    lvl -=1;
    // zeby nie zjechal w gore
    if (lvl == 0){lvl=3;}
    break;
    case 's':
    lvl +=1;
    // zeby nie zjechal w dol
    if (lvl == 4){lvl=1;}
    break;
    case 'e':
    lvlwybor+= lvl;
    break;
    }
    system ("cls");
}
void strzalka (){
    // kordy strzalki
    pion=x-1;
    map[pion-1][poziom] = "|";
    map[pion-2][poziom] = "|";
    map[pion-3][poziom] = "^";
}
// nadpisanie strzalki
void strzalka_do_wylotu(){
    // tez strzalka ale nie dziala z pionem
    map[pion-1][poziom] = "|";
    map[pion-2][poziom] = "|";
    map[pion-3][poziom] = "^";
}
void mapa (){
    // wpsiwanie mapy w tablice //
    for (int i=0;i<x;i++){
        map[0][i]="-";
    }
    for (int i=0;i<x;i++){
        map[x-1][i]="-";
    }
    for (int i=1;i<(x-1);i++){
        map [i][0]="|";
    }
    for (int i=1;i<(x-1);i++){
        map [i][x-1]="|";
    }
    for (int i=1;i<(x-1);i++){
        for (int j=1;j<(x-1);j++){
        map [i][j] = " ";
        }
    }
}
void pokazaniemapy(){
    // pokazanie mapy //
    for (int i=0;i<x;i++){
        for (int j=0;j<x;j++){
        cout << map [i][j];
        // jezeli dotyka sciany //
        if (j==(x-1)){
            cout << endl;
        }

        }
    }
    cout << endl <<"Punkty: "<<punkty << endl;
    cout << "a - ruch w lewo || d - ruch w prawo || w - strzal" << endl;
}
void wystrzal (){
    for (int i=0;i<x-5;i++){
    mapa();
    strzalka_do_wylotu();
    tarcza();
    pokazaniemapy();
    sleep(0.3);
    system("cls");
    pion--;
    }

}
void movement (char wsad ){
    switch (wsad){
        case 'w':  
        wystrzal();
        // dodawanie punktu gdy sie stykaja //
        if(map[1][zmiennatarczy]==map[1][poziom]){
        punkty+=1;
        // zmiana tarczy na randomowa 
        tarczaczas();
        }
        pion=x-1;
        poziom=(x/2)+1;     
        break;
        case 'a':
        poziom -= 1;
        // gdy dotyka sciany 
        if (poziom == 0){poziom = x-1;}
        // aby byl clean screena 
        system("cls");
        mapa();
        pokazaniemapy();
        system("cls");
        break;
        case 'd':
        poziom += 1;
        // gdy dotyka sciany 
        if (poziom == x){poziom = 1;}
        // aby byl clean screena 
        system("cls");
        mapa();
        pokazaniemapy();
        system("cls");
        break;
    }
}
void tarcza(){
    if (zmiennatarczy == 0 || zmiennatarczy == x){
        tarczaczas();
    }
    map[1][zmiennatarczy]= "*";
    
}
void start(){
    startt = clock();
    while (punkty!=2){
    mapa();
    strzalka();
    tarcza();
    pokazaniemapy();
    movement(getch());
    }
    stop = clock();
    czas =(double) (stop - startt)/ CLOCKS_PER_SEC;
    system("cls");
    cout << "!!! WYGRALES !!!" << endl << "Autor: Patryk Wawrzynek 2TP" << endl << "Twoj czas to: "<<czas<<endl;
    string zwyciezca;
    cout << "podaj swoj nick" << endl;
    cin >> zwyciezca;
    cout <<"o      o" << endl;
    cout <<"oo    oo" << endl;
    cout <<"ooo  ooo" << endl;
    cout <<"oooooooo" << endl;
    cout <<" oooooo" << endl;
    cout <<"  oooo" << endl;
    cout <<"   oo" << endl;
    cout <<"  oooo" << endl;
    cout <<" oooooo" << endl;
    cout <<"oooooooo" << endl;
    cout <<"["<< zwyciezca<<"]" << endl;

}
void tarczaczas(){
    srand(time(NULL));
    zmiennatarczy = rand()%x;
    
}
int main (){ 
    while (lvlwybor==0){
        menu();
        pokazaniemenu();
        movementmenu(getch());
    }
    if (lvlwybor==1){x+=35;}
    else if (lvlwybor==2){x+=10;}
    start();
    return 0;
}
