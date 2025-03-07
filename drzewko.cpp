#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

string wyodrebnij(string linia, int cel)//funkcja wyodrebnia konkretną komór z wiersza
{
    string odpowiedz="";
    int przecinek=0;
    for(int i=0;i<linia.size();i++)
    {
        if(linia[i]==','){przecinek++;}
        if(przecinek==cel && linia[i]!=','){odpowiedz=odpowiedz + linia[i];}
        if(przecinek>cel){break;}
    }
    return odpowiedz;
}

float okresl_entropie(vector<vector<int>> a)
{
    int max=0;
    int min=0;
    float suma=0;
    for(int i=0; i<size; i++)
    {
        suma=suma+a[i][9];
    }
    max=a[0];
    for(int i=1; i<size; i++)
    {
        if(a[i]>a[i-1]){max=a[i];}
    }
    min=a[0];
    for(int i=1; i<size; i++)
    {
        if(a[i]<a[i-1]){min=a[i];}
    }
    return (max-min)/suma;   
}

bool czy_duplikat(vector<string> a, string cel)//sprawdza czy wartosc jest duplikatem
{
    for(int i=0; i < a.size();i++)
    {
        if(a[i]==cel)
        {
            return true;
        }
    }
    return false;
}
int znajdz_duplikat(vector<string> a, string cel)//znajduje pozycje duplikatu
{
    for(int i=0; i < a.size();i++)
    {
        if(a[i]==cel)
        {
            return i;
        }
    }
    return -1;
}

int main(){

    ifstream odczyt("student_performance_dataset.csv");
    string wiersz;

    int liczba_atrybutow=1;//określa liczbe atrybutów w bazie danych

    vector<vector<int>> dane;//vector 2d do przechowywania danych z bazy
    vector<string> slownik;//przechowuje stringi z bady danych
    string bin;//przechowuje informacje podreczne
    
    int liczba_iteracji=0;//określa liczbe iteracji poniższego while
    while(getline(odczyt, wiersz)){//odczytanie danych i transport do wektora dane i uzupełnienie słownika
        if(liczba_iteracji==0)//przewsza iteracja to nagłówki więc je wykluczam z danych
        {
            for(int i=0; i < size(wiersz); i++)
            {
                if(wiersz[i]==','){liczba_atrybutow++;}
            }
            string naglowek[liczba_atrybutow];//przechowuje nazwy nagłówków
            for(int i=0; i < liczba_atrybutow; i++)
            {
                naglowek[i]=wyodrebnij(wiersz, i);
            }   
        }else{
            dane.push_back({0,0,0,0,0,0,0,0,0,0});//dynamicznie powiekszam dane
            for(int i=0; i<liczba_atrybutow; i++)
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
        liczba_iteracji++;//śledzi dokonane iteracje
    }
    odczyt.close();
    int liczba_wierszy=liczba_iteracji-1;//dla ułatwienia

    

    return 0;
}
