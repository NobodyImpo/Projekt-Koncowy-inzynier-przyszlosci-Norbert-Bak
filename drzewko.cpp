#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "funkcje/entropia.h"
#include "funkcje/odczyt_danych.h"
using namespace std;

int main(){

    ifstream odczyt("student_performance_dataset.csv");
    string wiersz;

    int liczba_atrybutow=0;//określa liczbe atrybutów w bazie danych
    int glowna_zmienna=9;//wartość dla której wykonujemy analize

    vector<vector<int>> dane;//vector 2d do przechowywania danych z bazy
    vector<string> slownik;//przechowuje stringi z bady danych
    string bin;//przechowuje informacje podreczne
    vector<string> naglowek;//przechowuje nazwy nagłówków
    
    int liczba_iteracji=0;//określa liczbe iteracji poniższego while
    while(getline(odczyt, wiersz)){//odczytanie danych i transport do wektora dane i uzupełnienie słownika
        //pojawił się mi jakiś problem przez który moge użyć while(getline()) wyłącznie raz, wiec musiałem wszystko zmieścić do jednej petli
        if(liczba_iteracji==0)//przewsza iteracja to nagłówki więc je wykluczam z danych
        {
            for(int i=0; i < size(wiersz); i++)
            {
                if(wiersz[i]==','){liczba_atrybutow++;}
            }
            for(int i=0; i < liczba_atrybutow; i++)
            {
                naglowek.push_back(wyodrebnij(wiersz, i));
            }   
        }else{
            dane.push_back({0,0,0,0,0,0,0,0,0,0});//dynamicznie powiekszam dane
            for(int i=0; i<liczba_atrybutow; i++)
            {
                if(i!=glowna_zmienna)
                {
                    bin = wyodrebnij(wiersz, i);//bin przechowuje wartosc danej komór aby zmienszyć ilosć potrzebnych obliczeń
                    if(czy_duplikat(slownik, bin))//sprawdza czy zawartość komurki jest duplikatem
                    {
                        dane[liczba_iteracji-1][i]=znajdz_duplikat(slownik, bin);//wpisuje id duplikatu
                    }
                    else
                    {
                        dane[liczba_iteracji-1][i]=slownik.size();//wpisuje nowe id
                        slownik.push_back(bin);//wpisuje string do slownik
                    }
                }
            }
            if(wyodrebnij(wiersz,glowna_zmienna)=="Pass")
            {
                dane[liczba_iteracji-1][glowna_zmienna]=1;
            }else{
                dane[liczba_iteracji-1][glowna_zmienna]=0;
            }
        }
        liczba_iteracji++;//śledzi dokonane iteracje
    }
    odczyt.close();
    int liczba_wierszy=liczba_iteracji-1;//dla ułatwienia
    vector<vector<vector<int>>> wezly;//przechowuje wezly
    wezly.push_back(dane);

    int typ_danych[liczba_atrybutow];//przechowuje typ danych 1-dane binarne(tylko dwa rodzaje) 2-dane liczbowe(liczby) 3-oznaczenia(nie liczby z przynajmiej 3 rodzajami)
    int liczba_rodzai=0;
    bool nieliczba=0;
    for(int a=0;a<liczba_atrybutow;a++)//okresla typ danych dla atrybutów 
    {
        liczba_rodzai=0;
        nieliczba=0;
        for(int b=0;b<liczba_wierszy;b++)
        {
            for(int c=0;c<slownik.size();c++)
            {
                if(slownik[dane[b][a]]==slownik[c])
                {
                    liczba_rodzai++;
                }
            }
            if(!(czy_liczba(slownik[dane[b][a]])))
            {
                nieliczba=1;
            }
        }
        if(liczba_rodzai==2)
        {
            typ_danych[a]=1;
        }else{
            if(nieliczba==1)
            {
                typ_danych[a]=3;
            }else{
                typ_danych[a]=2;
            }
        }
    }

    cout << okresl_miejsce_podzialu_typ2(wezly[0], 2, slownik, glowna_zmienna);
    
    return 0;
}