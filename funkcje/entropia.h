#include <iostream>
#include <vector>
#include "liczby.h"
using namespace std;

float okresl_entropie(vector<vector<int>> dane)//określa entrope(poziom rozporwadznia wartości: 0% wartości są rozprowadzone równomiernie, 100% wartości są skoncetrowane w jednym punkcie)
{
    float suma=0;
    int roznicza=0;
    for(int i=0; i<dane.size(); i++)
    {
        suma=suma+dane[i][1]+dane[i][2];
        roznicza=roznicza+bezwzgledna(dane[i][1]-dane[i][2]);
    }
    return(1-(roznicza/suma));
}

float okresl_miejsce_podzialu_typ2(vector<vector<int>> dane)//określa entrope(poziom rozporwadznia wartości: 0% wartości są rozprowadzone równomiernie, 100% wartości są skoncetrowane w jednym punkcie)
{
    vector<vector<int>> posortowane = dane;

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
        bin=okresl_entropie(podzial1)+okresl_entropie(podzial2);
        if(bin<max_entropia)//sprawdzamy czy suma entropii jest największa
        {
            max_entropia=bin;
            granica=(posortowane[i-1][0]+posortowane[i][0])/2;
        }
    }
    return granica;
}
int okresl_miejsce_podzialu_typ3(vector<vector<int>> dane)
{
    for(int i=0; i<dane.size();i++)//czy istnieje określenie o jednorodnych wartościach
    {
        if(dane[i][1]==0 || dane[i][2]==0)
        {
            return dane[i][0];//zwraca index tego okreslenia
        }
    }
    //nie istnie określenie twóje jest jednorodne
    vector<vector<int>> podzial1;//lewa strona podziału
    vector<vector<int>> podzial2;//prawa strona podziału
    float min_entropia[2]={0,0};
    float bin;
    
    for(int i=1; i<dane.size();i++)
    {
        podzial1.clear(); podzial2.clear();
        podzial1.push_back(dane[i]);
        
        for(int a=0; a<dane.size();a++)//przypisanie wartości do prawej strony podziału
        {
            if(a!=i)
            {
                podzial2.push_back(dane[a]);
            }
        }
        bin=okresl_entropie(podzial1)+okresl_entropie(podzial2);
        if(bin<min_entropia[0])//sprawdzamy czy suma entropii jest największa
        {
            min_entropia[0]=bin;
            min_entropia[1]=i;
        }
    }
    return min_entropia[1];
}