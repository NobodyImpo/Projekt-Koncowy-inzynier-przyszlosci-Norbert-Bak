#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> pogrupuj(vector<vector<int>> dane, int cel, int glowna_zmienna)
{
    vector<vector<int>> pogrupowane;//przechowuje pogrupowane wartości 0-index 1-wartość
    int juz_pogrupowane = 0;//przechuje informacje czy znaleziono w pogrupowane index
    for(int i=0; i<dane.size(); i++){//iteruje przez wszystkie wiersze dane
        juz_pogrupowane=0;
        for(int b=0; b<pogrupowane.size();b++)//iteruje przez wszystkie wersy pogrupowanie
        {
            if(dane[i][cel]==pogrupowane[b][0])//jeśli index danych znajduje się w pogrupowane
            {
                if(dane[i][glowna_zmienna]==1)//sumuje wartości i zapisu dla odpowiedniego indexu
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
            if(dane[i][glowna_zmienna]==1)//dodaje nowy index do pogrupowane
            {
                pogrupowane.push_back({dane[i][cel], 1, 0}); 
            }else{
                pogrupowane.push_back({dane[i][cel], 0, 1});
            }
        }
    }
    return pogrupowane;
}
vector<vector<int>> posortuj(vector<vector<int>> dane)
{
    int max=dane[0][0];//przechowuje index największej wartości
    for(int i=1; i<dane.size();i++)
    {
        if(dane[i][0]>max)
        {
            max=dane[i][0];
        }
    }
    max++;
    int kalkulacje[max];
    for(int i=0; i<max;i++)
    {
        kalkulacje[i]=0;
    }
    vector<vector<int>> posortowane;
    for(int i=0; i<dane.size();i++)//przypisuje do wektora posortowane wartości
    {
        posortowane.push_back({0,0});
    }
    for(int i=0; i<dane.size();i++)//przypisuje kalkulacją odpowiednie wartości
    {
        kalkulacje[dane[i][0]]++;
    }
    for(int i=1; i<max; i++)
    {
        kalkulacje[i]=kalkulacje[i] + kalkulacje[i-1];
    }
    for(int i=dane.size()-1; i>=0;i--)
    {
        posortowane[kalkulacje[dane[i][0]]-1][0]=dane[i][0];
        posortowane[kalkulacje[dane[i][0]]-1][1]=dane[i][1];
        kalkulacje[dane[i][0]]--;
    }
    
    return posortowane;
}