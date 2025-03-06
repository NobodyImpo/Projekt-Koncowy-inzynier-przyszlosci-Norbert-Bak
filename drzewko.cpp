#include <iostream>
#include <fstream>
using namespace std;

string wyodrebnij(string linia, int cel)
{
    string odpowiedz="";
    int przecinek=1;
    for(int i=0;i<linia.size();i++)
    {
        if(przecinek==cel){
            odpowiedz=odpowiedz + linia[i];
        }
        if(linia[i]==',')
        {
            przecinek++;
        }
        if(przecinek>cel)
        {
            break;
        }

    }
    return odpowiedz;
}

int main(){

    ifstream odczyt("student_performance_dataset.csv");
    string linia;
    while(getline(odczyt, linia)){
        cout << wyodrebnij(linia, 10) << endl;
    }
    return 0;
}
