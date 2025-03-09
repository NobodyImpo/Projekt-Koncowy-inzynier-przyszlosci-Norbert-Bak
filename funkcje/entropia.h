#include <iostream>
#include <vector>
#include "liczby.h"
using namespace std;

float okresl_entropie(vector<vector<int>> dane, int cel)//określa entrope(poziom rozporwadznia wartości: 0% wartości są rozprowadzone równomiernie, 100% wartości są skoncetrowane w jednym punkcie)
{
    vector<vector<int>> pogrupowane;//przechowuje pogrupowane wartości 0-index 1-wartość
    int juz_pogrupowane = 0;//przechuje informacje czy znaleziono w pogrupowane index
    for(int i=0; i<dane.size(); i++){//iteruje przez wszystkie wiersze dane
        juz_pogrupowane=0;
        for(int b=0; b<pogrupowane.size();b++)//iteruje przez wszystkie wersy pogrupowanie
        {
            if(dane[i][cel]==pogrupowane[b][0])//jeśli index danych znajduje się w pogrupowane
            {
                pogrupowane[b][1]=pogrupowane[b][1]+dane[i][9];//sumuje wartości i zapisu dla odpowiedniego indexu
                juz_pogrupowane++;
            }   
        }
        if(juz_pogrupowane==0)//jeśli nie znaleziono indexu
        {
            pogrupowane.push_back({dane[i][cel], dane[i][9]});//dodaje nowy index do pogrupowane
        }
    }
    //wszystkie wartości dla atrybutu cel zostały pogrupowane w wektorze pogrupowane
    int max=0;
    int min=0;
    float suma=0;
    
    max=pogrupowane[0][1];
    for(int i=1; i<pogrupowane.size(); i++)//znajduje największą wartość
    {
        if(pogrupowane[i][1]>pogrupowane[i-1][1]){max=pogrupowane[i][1];}
    }
    min=pogrupowane[0][1];
    for(int i=1; i<pogrupowane.size(); i++)//znajduje nam=jmniejszą wartość
    {
        if(pogrupowane[i][1]<pogrupowane[i-1][1]){min=pogrupowane[i][1];}
    }
    for(int i=0; i<pogrupowane.size(); i++)//oblicza sume wartości
    {
        suma=suma+pogrupowane[i][1];
    }
    return 1-((max-min)/suma);//zwraca poziom entropi danych. Wynik wynosi od 0 do 1. Różnica skrajnych wartości dzielonych przez sume wszystkich wartości określa entropie
}

int okresl_miejsce_podzialu_typ1(vector<vector<int>> dane, int cel, int glowna_zmienna)//określa połowe z wiekszą ilością głównej zmiennej
{
    int suma[2] = {0,0};
    int druga_wartosc=0;
    for(int i=0; i<dane.size();i++)
    {
        if(dane[i][cel]==dane[0][cel])
        {
            suma[0]=suma[0]+dane[i][glowna_zmienna];
        }else{
            suma[1]=suma[1]+dane[i][glowna_zmienna];
            druga_wartosc=dane[i][cel];
        }
    }
    if(suma[0]>suma[1])
    {
        return dane[0][cel];
    }else{
        return druga_wartosc;
    }
}

float okresl_miejsce_podzialu_typ2(vector<vector<int>> dane, int cel, vector<string> slownik, int glowna_zmienna)//określa entrope(poziom rozporwadznia wartości: 0% wartości są rozprowadzone równomiernie, 100% wartości są skoncetrowane w jednym punkcie)
{
    vector<vector<int>> pogrupowane;//zawiera pogrupowane wartości
    int juz_pogrupowane = 0;
    for(int i=0; i<dane.size(); i++){//zwykle grupowanie jak wczesniej ale idexy są floatami
        juz_pogrupowane=0;
        for(int b=0; b<pogrupowane.size();b++)
        {
            if(dane[i][cel]==pogrupowane[b][0])
            {
                pogrupowane[b][1]=pogrupowane[b][1]+dane[i][glowna_zmienna];
                juz_pogrupowane++;
            }   
        }
        if(juz_pogrupowane==0)
        {
            pogrupowane.push_back({int(zamien_na_liczba(slownik[dane[i][cel]])), dane[i][glowna_zmienna]});
        }
    }
    bool posortowane=0;
    int blad_sortowania=0;
    int bin[2] = {0,0};
    int iteracja=0;
    while(!(posortowane))//poniewasz opejumemy na drugim typie(liczbach) sortujemy indexy rosnąco
    {
        iteracja++;
        for(int i=0; i<pogrupowane.size()-1; i++)
        {
            if(pogrupowane[i][0]>pogrupowane[i+1][0])
            {
                cout << iteracja <<". "<<pogrupowane[i][0]<<">"<<pogrupowane[i+1][0]<< " - " << blad_sortowania << endl;
                bin[0]=pogrupowane[i+1][0];
                bin[1]=pogrupowane[i+1][1];
                pogrupowane[i+1][0]=pogrupowane[i][0];
                pogrupowane[i+1][1]=pogrupowane[i][1];
                pogrupowane[i][0]=bin[0];
                pogrupowane[i][1]=bin[1];
            }
        }
        blad_sortowania=0;
        for(int i=0; i<pogrupowane.size()-1; i++)
        {
            if(pogrupowane[i][0]>pogrupowane[i+1][0])
            {
                blad_sortowania++;
            }
        }
        if(blad_sortowania<1)
        {
            posortowane=1;
        }
        //cout << "iteracja sortowania: "<<iteracja<<endl;
    }
    cout << "SORTOWANIE SKONCZONE"<<endl;
    float podstawa = pogrupowane[0][1]; 
    for(int i=1; i<pogrupowane.size();i++)//sprawdzamy czy możli jest podzielenie danych na dwa jednorodne zbiory
    {
        if((pogrupowane[i][1]>podstawa && podstawa==0)||(pogrupowane[i][1]<podstawa && podstawa!=0))//jeśli znaleziono granice jednorodności
        {
            return(pogrupowane[i-1][0]+pogrupowane[i][0])/2;//zwraca miejsce granicy
        }
    }
    //granica nie istnieje więc szukamy podziału który utworzy dwa zbiory o maksymalnej entropii
    vector<vector<int>> podzial1;//lewa strona podziału
    vector<vector<int>> podzial2;//prawa strona podziału
    float max_entropia=0;
    float granica;
    for(int i=1; i<pogrupowane.size();i++)
    {
        podzial1.clear(); podzial2.clear();
        for(int a=0; a<i;a++)//przypisanie wartości do lewej strony podziału
        {
            podzial1.push_back({int(pogrupowane[a][0]),int(pogrupowane[a][1])});
        }
        for(int a=i; a<pogrupowane.size();a++)//przypisanie wartości do prawej strony podziału
        {
            podzial2.push_back({int(pogrupowane[a][0]),int(pogrupowane[a][1])});
        }
        bin[0]=okresl_entropie(podzial1, 1)+okresl_entropie(podzial2, 1);
        cout << bin[0] << endl;
        if(bin[0]>max_entropia)//sprawdzamy czy suma entropii jest największa
        {
            max_entropia=bin[0];
            granica=(pogrupowane[i-1][0]+pogrupowane[i][0])/2;
        }
    }
    return granica;
}