#include <iostream>
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
    for(int i=0; i<=a.size();i++)
    {
        miejsce_kropki=i;
        if(a[i]=='.')
        {

            break;
        }
    }
    for(int i=0; i<miejsce_kropki;i++)
    {
        liczba=liczba+((int(a[i])-48)*pow(10,miejsce_kropki-i-1));
    }
    for(int i=miejsce_kropki+1; i<a.size();i++)
    {
        liczba=liczba+((int(a[i])-48)/pow(10,i-miejsce_kropki));
    }
    return liczba;
}
int bezwzgledna(int a)
{
    if(a<0)
    {
        return -a;
    }else{
        return a;
    }
}