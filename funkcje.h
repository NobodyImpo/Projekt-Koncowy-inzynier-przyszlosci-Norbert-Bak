#include <vector>
#include <math.h>
using namespace std;

bool czy_liczba(string a)
{
    for(int i=0; i<a.size();i++)
    {
        if(!((int(a[i]) >= 48 && int(a[i]) <= 57) || a[i]=='.'))
        {
            return false;
        }
    }
    return true;
}
float zamien_na_liczba(string a)
{
    int miejsce_kropki=0;
    float liczba=0;
    for(int i=0; i<a.size();i++)
    {
        if(a[i]==',')
        {
            miejsce_kropki=i;
            break;
        }
    }
    for(int i=0; i<a.size()-miejsce_kropki;i++)
    {
        liczba=liczba+((int(a[i])-48)*pow(10,a.size()-i));
    }
    for(int i=a.size()-miejsce_kropki; i<a.size();i++)
    {
        liczba=liczba+((int(a[i])-48)/pow(10,a.size()-i));
    }
    return liczba;
}

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

float okresl_entropie(vector<vector<int>> a, int cel)//określa entrope(poziom rozporwadznia wartości: 0% wartości są rozprowadzone równomiernie, 100% wartości są skoncetrowane w jednym punkcie)
{
    vector<vector<int>> pogrupowane;//zawiera pogrupowane wartości
    int juz_pogrupowane = 0;
    for(int i=0; i<a.size(); i++){//iteruje przez wszystkie wersy a
        juz_pogrupowane=0;
        for(int b=0; b<pogrupowane.size();b++)//iteruje przez wszystkie wersy pogrupowanie
        {
            if(a[i][cel]==pogrupowane[b][0])//jeśli wers z a jest do już istniejącej
            {
                pogrupowane[b][1]=pogrupowane[b][1]+a[i][9];//jeśli wiersz w wektora a już się znajduje w pogrupowane to dodaje wartość
                juz_pogrupowane++;
            }   
        }
        if(juz_pogrupowane==0)
        {
            pogrupowane.push_back({a[i][cel], a[i][9]});//jeśli wiersz nie znajduje się w pogrupowane to go dodaje
        }
    }
    int max=0;
    int min=0;
    float suma=0;
    for(int i=0; i<pogrupowane.size(); i++)
    {
        suma=suma+pogrupowane[i][1];
    }
    max=pogrupowane[0][1];
    for(int i=1; i<pogrupowane.size(); i++)
    {
        if(pogrupowane[i][1]>pogrupowane[i-1][1]){max=pogrupowane[i][1];}
    }
    min=pogrupowane[0][1];
    for(int i=1; i<pogrupowane.size(); i++)
    {
        if(pogrupowane[i][1]<pogrupowane[i-1][1]){min=pogrupowane[i][1];}
    }
    return 1-((max-min)/suma);   
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
int okresl_miejsce_podzialu_typ1(vector<vector<int>> dane, int cel, int glowna_zmienna)
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