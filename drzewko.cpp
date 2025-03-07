#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string wyodrebnij(string linia, int cel)
{
    string odpowiedz="";
    int przecinek=1;
    for(int i=0;i<linia.size();i++)
    {
        if(linia[i]==','){przecinek++;}
        if(przecinek==cel && linia[i]!=','){odpowiedz=odpowiedz + linia[i];}
        if(przecinek>cel){break;}
    }
    return odpowiedz;
}

float okresl_entropie(int a[], int size)
{
    int max=0;
    int min=0;
    float suma=0;
    for(int i=0; i<size; i++)
    {
        suma=suma+a[i];
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

int liczba_wpisuw=0;
int liczba_atrybutuw=1;
int main(){

    ifstream odczyt("student_performance_dataset.csv");
    string linia;
    
    while(getline(odczyt, linia)){
        cout << linia <<endl;
    }
    cout << endl << endl << endl;
    while(getline(odczyt, linia)){
        cout << linia <<endl;
    }
    liczba_atrybutuw=9;
    liczba_wpisuw--;
    //normalizacja
    int dane[liczba_atrybutuw][liczba_wpisuw][1];
    string pomocnicza_tablica[liczba_wpisuw];
    int b=0;
    int duplikat=0;
    for(int i=0; i<liczba_atrybutuw; i++)
    {
        for(int a=0; a<liczba_wpisuw; a++)
        {
            pomocnicza_tablica[a]="";
        }
        b=0;
        while(getline(odczyt, linia)){
            duplikat=0;
            
            for(int c=0; c<b;c++)
            {
                if(wyodrebnij(linia, i)==pomocnicza_tablica[c])
                {
                    cout << wyodrebnij(linia, i) <<endl;
                    if(wyodrebnij(linia, 10)=="Pass"){dane[i][c][0]=dane[i][c][0]+1;}
                    duplikat=1;
                }
            }
            if(duplikat==0)
            {
                cout<<wyodrebnij(linia, i)<<endl;
                pomocnicza_tablica[b]=wyodrebnij(linia, i);
                if(wyodrebnij(linia, 10)=="Pass"){dane[i][b][0]=dane[i][b][0]+1;};
                b++;
            }
            
        }
    }
    odczyt.close();

    return 0;
}
