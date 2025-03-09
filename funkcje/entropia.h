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
                if(dane[i][9]==1)//sumuje wartości i zapisu dla odpowiedniego indexu
                {
                    pogrupowane[b][1]++;
                }else{
                    pogrupowane[b][2]++;
                }
                juz_pogrupowane++;
            }   
        }
        if(juz_pogrupowane==0)//jeśli nie znaleziono indexu
        {
            if(dane[i][9]==1)//dodaje nowy index do pogrupowane
            {
                pogrupowane.push_back({dane[i][cel], 1, 0}); 
            }else{
                pogrupowane.push_back({dane[i][cel], 0, 1});
            }
        }
    }
    float suma=0;
    int roznicza=0;
    for(int i=0; i<pogrupowane.size(); i++)
    {
        suma=suma+pogrupowane[i][1]+pogrupowane[i][2];
        roznicza=roznicza+bezwzgledna(pogrupowane[i][1]-pogrupowane[i][2]);
    }
    return(1-(roznicza/suma));
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
            if(int(zamien_na_liczba(slownik[dane[i][cel]]))==pogrupowane[b][0])
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
    //SORTOWANIE
    int max=pogrupowane[0][0];//przechowuje index największej wartości
    for(int i=1; i<pogrupowane.size();i++)
    {
        if(pogrupowane[i][0]>max)
        {
            max=pogrupowane[i][0];
        }
    }
    max++;
    int kalkulacje[max];
    for(int i=0; i<max;i++)
    {
        kalkulacje[i]=0;
    }
    vector<vector<int>> posortowane;
    for(int i=0; i<pogrupowane.size();i++)//przypisuje do wektora posortowane wartości
    {
        posortowane.push_back({0,0});
    }
    for(int i=0; i<pogrupowane.size();i++)//przypisuje kalkulacją odpowiednie wartości
    {
        kalkulacje[pogrupowane[i][0]]++;
    }
    for(int i=1; i<max; i++)
    {
        kalkulacje[i]=kalkulacje[i] + kalkulacje[i-1];
    }
    for(int i=pogrupowane.size()-1; i>=0;i--)
    {
        posortowane[kalkulacje[pogrupowane[i][0]]-1][0]=pogrupowane[i][0];
        posortowane[kalkulacje[pogrupowane[i][0]]-1][1]=pogrupowane[i][1];
        kalkulacje[pogrupowane[i][0]]--;
    }
    for(int i=0; i<posortowane.size();i++)
    {
        cout<<posortowane[i][0]<<"-"<<posortowane[i][1]<<endl;
    }

    //OKREŚLANIE GRANICY
    float podstawa = posortowane[0][1];
    bool jednorodnosc=0;
    for(int i=1; i<posortowane.size();i++)//sprawdzamy czy możli jest podzielenie danych na dwa jednorodne zbiory
    {
        if((posortowane[i][1]!=0 && podstawa==0)||(posortowane[i][1]==0 && podstawa!=0))//jeśli znaleziono granice jednorodności
        {
            return(posortowane[i-1][0]+posortowane[i][0])/2;//zwraca miejsce granicy
        }
    }
    //granica nie istnieje więc szukamy podziału który utworzy dwa zbiory o maksymalnej entropii
    vector<vector<int>> podzial1;//lewa strona podziału
    vector<vector<int>> podzial2;//prawa strona podziału
    float max_entropia=0;
    float granica;
    float bin;
    
    for(int i=1; i<posortowane.size();i++)
    {
        podzial1.clear(); podzial2.clear();
        for(int a=0; a<i;a++)//przypisanie wartości do lewej strony podziału
        {
            podzial1.push_back({int(posortowane[a][0]),int(posortowane[a][1])});
        }
        for(int a=i; a<posortowane.size();a++)//przypisanie wartości do prawej strony podziału
        {
            podzial2.push_back({int(posortowane[a][0]),int(posortowane[a][1])});
        }
        bin=okresl_entropie(podzial1, 1)+okresl_entropie(podzial2, 1);
        if(bin>max_entropia)//sprawdzamy czy suma entropii jest największa
        {
            max_entropia=bin;
            granica=(posortowane[i-1][0]+posortowane[i][0])/2;
        }
    }
    return granica;
}