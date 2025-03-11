#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

int bezwzgledna(int a)
{
    if(a<0)
    {
        return -a;
    }else{
        return a;
    }
}

float okresl_entropie(vector<vector<int>> dane)//określa entrope(poziom rozporwadznia wartości: 0% wartości są rozprowadzone równomiernie, 100% wartości są skoncetrowane w jednym punkcie)
{
    float suma=0;
    float roznicza=0;
    for(int i=0; i<dane.size(); i++)
    {
        suma=suma+dane[i][1]+dane[i][2];
        roznicza=roznicza+bezwzgledna(dane[i][1]-dane[i][2]);
    }
    return(1-(roznicza/suma));
}

bool czy_lisc(vector<vector<int>> dane)
{
    int podstawa=dane[0][9];
    for(int i=1; i<dane.size();i++)
    {
        if(dane[i][9]!=podstawa)
        {
            return false;
        }
    }
    return true;
}

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
        posortowane.push_back({0,0,0});
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
        posortowane[kalkulacje[dane[i][0]]-1][2]=dane[i][2];
        kalkulacje[dane[i][0]]--;
    }
    return posortowane;
}

vector<vector<int>> podziel_typ1(vector<vector<int>> dane, int cel, bool strona)
{
    vector<vector<int>> wynik;
    int podstawa = dane[0][cel];
    if(strona==0)
    {
        for(int i=0; i< dane.size();i++)
        {
            if(dane[i][cel]!=podstawa)
            {
                wynik.push_back(dane[i]);
            }
        }
    }
    if(strona==1)
    {
        for(int i=0; i< dane.size();i++)
        {
            if(dane[i][cel]==podstawa)
            {
                wynik.push_back(dane[i]);
            }
        }
    }
    return wynik;
}

vector<vector<int>> podziel_typ2(vector<vector<int>> dane, int cel, int granica,  bool strona)
{
    vector<vector<int>> wynik;
    if(strona==0)
    {
        for(int i=0; i< dane.size();i++)
        {
            if(dane[i][cel]<=granica)
            {
                wynik.push_back(dane[i]);
            }
        }
    }
    if(strona==1)
    {
        for(int i=0; i< dane.size();i++)
        {
            if(dane[i][cel]>granica)
            {
                wynik.push_back(dane[i]);
            }
        }
    }
    return wynik;
}

vector<vector<int>> podziel_typ3(vector<vector<int>> dane, int cel, int granica,  bool strona)
{
    vector<vector<int>> wynik;
    if(strona==0)
    {
        for(int i=0; i< dane.size();i++)
        {
            if(dane[i][cel]==granica)
            {
                wynik.push_back(dane[i]);
            }
        }
    }
    if(strona==1)
    {
        for(int i=0; i< dane.size();i++)
        {
            if(dane[i][cel]!=granica)
            {
                wynik.push_back(dane[i]);
            }
        }
    }
    return wynik;
}

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

int okresl_miejsce_podzialu_typ2(vector<vector<int>> a)//określa entrope(poziom rozporwadznia wartości: 0% wartości są rozprowadzone równomiernie, 100% wartości są skoncetrowane w jednym punkcie)
{
    vector<vector<int>> dane;
    for(int i=0; i<a.size();i++)
    {
        dane.push_back({a[i][0], a[i][1], a[i][2]});
    }

    if(okresl_entropie(dane)==0)
    {
        
        for(int i=0; i<dane.size()-1;i++)
        {
            
            if((dane[i][1]==0 && dane[i+1][1]!=0)||(dane[i][1]!=0 && dane[i+1][1]==0))
            {
                return dane[i][0];
            }
        }
    }

    
    int suma=0;
    for(int i=0; i<dane.size();i++)
    {
        suma=suma+dane[i][1]+dane[i][2];
    }
    suma++;
    int min_entropia[2]={suma,0};
    int bin[2]={0,0};

    for(int i=0; i<dane.size()-1;i++)
    {
        for(int a=0; a<=i;a++)//przypisanie wartości do lewej strony podziału
        {
            bin[0]=bin[0]+bezwzgledna(dane[a][1]-dane[a][2]);
        }
        for(int a=i+1; a<dane.size();a++)//przypisanie wartości do prawej strony podziału
        {
            bin[1]=bin[1]+bezwzgledna(dane[a][1]-dane[a][2]);
        }
        if(bezwzgledna(bin[0]=bin[1])<min_entropia[0])//sprawdzamy czy suma entropii jest mniejsza
        {
            min_entropia[0]=bezwzgledna(bin[0]-bin[1]);
            min_entropia[1]=dane[i][0];
        }
    }
    return min_entropia[1];
}

int okresl_miejsce_podzialu_typ3(vector<vector<int>> info)
{
    vector<vector<int>> dane;
    for(int i=0; i<info.size();i++)
    {
        dane.push_back({info[i][0], info[i][1], info[i][2]});
    }
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
    float min_entropia[2]={2,0};
    float bin;
    
    for(int i=0; i<dane.size();i++)
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
            min_entropia[1]=dane[i][0];
        }
    }
    return min_entropia[1];
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

float min_entropia(vector<vector<int>> dane, int glowna_zmienna)
{
    float min_entropia[2] = {2,0};
    bool roznorodnosc=0;
    int podstawa;
    for(int i=1; i<dane[0].size()-1;i++)
    {
        roznorodnosc=0;
        podstawa=dane[0][i];
        for(int a=0; a<dane.size();a++)
        {
            if(dane[a][i]!=podstawa)
            {
                roznorodnosc=1;
            }
        }
        if(okresl_entropie(pogrupuj(dane, i, glowna_zmienna))<min_entropia[0]&&i!=8)
        {
            min_entropia[0]=okresl_entropie(pogrupuj(dane, i, glowna_zmienna));
            min_entropia[1]=i;
        }
    }
    return int(min_entropia[1]);
}

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
        if(liczba_iteracji==0)//pierwsza iteracja to nagłówki więc je wykluczam z danych
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
            for(int i=0; i<liczba_atrybutow; i++)//uzupełnianie slownika
            {
                if(i!=glowna_zmienna)
                {
                    bin = wyodrebnij(wiersz, i);//bin przechowuje wartosc danej komór aby zmienszyć ilosć potrzebnych obliczeń
                    if(!(czy_liczba(bin)))
                    {
                        if(czy_duplikat(slownik, bin))//sprawdza czy zawartość komurki jest duplikatem
                        {
                            dane[liczba_iteracji-1][i]=znajdz_duplikat(slownik, bin);//wpisuje id duplikatu
                        }
                        else
                        {
                            dane[liczba_iteracji-1][i]=slownik.size();//wpisuje nowe id
                            slownik.push_back(bin);//wpisuje string do slownik
                        }
                    }else{
                        dane[liczba_iteracji-1][i]=int(zamien_na_liczba(bin));
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
    

    
    //przechowuje typ danych 1-dane binarne(tylko dwa rodzaje) 2-dane liczbowe(liczby) 3-oznaczenia(nie liczby z przynajmiej 3 rodzajami)
    int typ_danych[liczba_atrybutow]={1,1,2,2,2,3,1,1,2,1};
    vector<vector<int>> poziom;//okresla jaki wezeł jest na jakim poziomie
    int poziom_drzewa=0;//okresla poziom drzewa
    int wezel=0;//okresla liczbe wezłów
    int liczba_lisci;
    poziom.push_back({wezel});
    bool jednorodnosc=0;//okresla czy wszystkie wezly na poziomie są lisciami
    int min_e=0;
    int podzial;
    vector<int> pomocniczy;
    
    vector<vector<int>> decyzje;//okresla decyzje drzewka
    vector<int> p_decyzje;//pomocnicza decyzji

    while(!(jednorodnosc))//pentla aż pozostaną tylko liście
    {
        //SPRAWDZANIE CZY NA POZIOMIE DRZEWA ZNAJDUJĄ SIĘ TYLKO LIŚCIE
        liczba_lisci=0;
        for(int i=0; i<poziom[poziom_drzewa].size();i++)//dla wszystkich wezłów na poziomie
        {
            liczba_lisci=liczba_lisci + int(czy_lisc(wezly[poziom[poziom_drzewa][i]]));//zlicza liczbe lisci
        }
        if((poziom[poziom_drzewa].size()-liczba_lisci)==0)//jesli wszystkie węzły to liscie to konczy pentle
        {
            jednorodnosc=1;
        }
        //PODZIAL
            pomocniczy.clear();
            for(int i=0; i<poziom[poziom_drzewa].size();i++)//Dla wszystkich wezłów danego poziomu drzewa
            {
                p_decyzje.clear();
                min_e = min_entropia(wezly[poziom[poziom_drzewa][i]], glowna_zmienna);//Znaduje atrybut z najmiejszą entropią
                switch(typ_danych[min_e])//W zależności od typu atrybutu
                {
                    case 1://dane są binarne
                    if(!(czy_lisc(wezly[poziom[poziom_drzewa][i]])))//wezeł to nie liść
                    {
                        //Przypisuje cześć która nie spełniła warunku (równa jest 0) do wolnego miejsca na poziomie drzewa
                        wezel++;
                        pomocniczy.push_back(wezel);
                        wezly.push_back(podziel_typ1(wezly[poziom[poziom_drzewa][i]], min_e, 0));
                        //Przypisuje cześć która spełniła warunku (równa jest 1) do wolnego miejsca na poziomie drzewa
                        wezel++;
                        pomocniczy.push_back(wezel);
                        wezly.push_back(podziel_typ1(wezly[poziom[poziom_drzewa][i]], min_e, 1));
                        //Zapisuje informacje o podziale do wektora decyzje
                        p_decyzje.push_back(min_e);//atrybut
                        p_decyzje.push_back(typ_danych[min_e]);//typ danych
                        p_decyzje.push_back(0);//podzial
                        p_decyzje.push_back(0);//wartosc
                        p_decyzje.push_back(wezel-1);//adres negatynej odpowiedzi
                        p_decyzje.push_back(wezel);//adres pozytywnych odpowiedzi
                    }else{//wezeł to liść
                        //Zapisuje informacje o liściu do wektora decyzje
                        p_decyzje.push_back(-1);
                        p_decyzje.push_back(0);//typ dancyh
                        p_decyzje.push_back(0);//podzial
                        p_decyzje.push_back(wezly[poziom[poziom_drzewa][i]][0][glowna_zmienna]);//wartosc
                        p_decyzje.push_back(0);
                        p_decyzje.push_back(0);
                    }break;
                
                    case 2://dane są liczbami
                    if(!(czy_lisc(wezly[poziom[poziom_drzewa][i]])))//wezel to nie liść
                    {
                        //okresle miejsce podziału danych
                        podzial = okresl_miejsce_podzialu_typ2(posortuj(pogrupuj(wezly[poziom[poziom_drzewa][i]], min_e, glowna_zmienna)));
                        //Przypisuje część która jest równa bądz mniejsza od miejsca podziału
                        wezel++;
                        pomocniczy.push_back(wezel);
                        wezly.push_back(podziel_typ2(wezly[poziom[poziom_drzewa][i]], min_e, podzial, 0));
                        //Przypisuje część która jest większa od miejsca podziału
                        wezel++;
                        pomocniczy.push_back(wezel);
                        wezly.push_back(podziel_typ2(wezly[poziom[poziom_drzewa][i]], min_e, podzial, 1));
                        //Zapisuje informacje o podziale do wektora decyzje
                        p_decyzje.push_back(min_e);
                        p_decyzje.push_back(typ_danych[min_e]);
                        p_decyzje.push_back(podzial);
                        p_decyzje.push_back(0);//wartosc
                        p_decyzje.push_back(wezel-1);//adres negatynej odpowiedzi
                        p_decyzje.push_back(wezel);//adres pozytywnych odpowiedzi
                    }else{//wezel to liść
                        //Zapisuje informacje o liściu
                        p_decyzje.push_back(-1);
                        p_decyzje.push_back(0);
                        p_decyzje.push_back(0);
                        p_decyzje.push_back(wezly[poziom[poziom_drzewa][i]][0][glowna_zmienna]);//wartosc
                        p_decyzje.push_back(0);
                        p_decyzje.push_back(0);
                    }
                    break;

                    case 3://dane są oznaczeniami
                    if(!(czy_lisc(wezly[poziom[poziom_drzewa][i]])))//węzeł to nie liść
                    {
                        //okresla oznaczenie dla którego dojdzie do podziału
                        podzial=okresl_miejsce_podzialu_typ3(pogrupuj(wezly[poziom[poziom_drzewa][i]], min_e, glowna_zmienna));
                        //Przypisuje część która zamiera okreslone oznacznie
                        wezel++;
                        pomocniczy.push_back(wezel);
                        wezly.push_back(podziel_typ3(wezly[poziom[poziom_drzewa][i]], min_e, podzial, 0));
                        //Przypisuje część która nie zamiera okreslonego oznaczenia
                        wezel++;
                        pomocniczy.push_back(wezel);
                        wezly.push_back(podziel_typ3(wezly[poziom[poziom_drzewa][i]], min_e, podzial, 1));
                        //Zapisuje informacje o podziale
                        p_decyzje.push_back(min_e);
                        p_decyzje.push_back(typ_danych[min_e]);
                        p_decyzje.push_back(podzial);
                        p_decyzje.push_back(0);//wartosc
                        p_decyzje.push_back(wezel-1);//adres negatynej odpowiedzi
                        p_decyzje.push_back(wezel);//adres pozytywnych odpowiedzi
                    }else{
                        //zapisje informacje o liściu
                        p_decyzje.push_back(-1);
                        p_decyzje.push_back(0);
                        p_decyzje.push_back(0);
                        p_decyzje.push_back(wezly[poziom[poziom_drzewa][i]][0][glowna_zmienna]);//wartosc
                        p_decyzje.push_back(0);
                        p_decyzje.push_back(0);
                    }break;
                }
                decyzje.push_back(p_decyzje);//zapisuje informacje o podziałach i liściach
            }
            poziom.push_back(pomocniczy);//zapisuje informacje o zawartości poziomu
            poziom_drzewa++;
    }
    ofstream zapis("decyzje.txt");
    for(int i=0; i<decyzje.size();i++)
    {
        zapis << decyzje[i][0] <<"," << decyzje[i][1] <<","<<decyzje[i][2]<<","<<decyzje[i][3]<<","<<decyzje[i][4]<<","<<decyzje[i][5]<<endl;
    }
    zapis.close();
    //return 0;
    vector<int> pytanie;
    string odpowiedz;
    for(int i=0; i<liczba_atrybutow;i++)
    {
        cout << "podaj " << naglowek[i]<<": ";
        cin >> odpowiedz;
        switch(typ_danych[i])
        {
            case 1:
            for(int a=0; a<slownik.size();a++)
            {
                if(slownik[a]==odpowiedz)
                {
                    pytanie.push_back(a);
                }
            }
            break;
            case 2:
            pytanie.push_back(int(zamien_na_liczba(odpowiedz)));
            break;
            case 3:
            for(int a=0; a<slownik.size();a++)
            {
                if(slownik[a]==odpowiedz)
                {
                    pytanie.push_back(a);
                }
            }
            break;
        }
    }
    cout << endl;
    int wynik;
    
    int i=0;
    while(true)
    {
        if(decyzje[i][0]==-1)
        {
            cout << "Wynik: "<< decyzje[i][3];
            wynik = decyzje[i][3];
            break;
        }else{
            switch(decyzje[i][1])
            {
                case 1:
                    if(pytanie[decyzje[i][0]]>decyzje[i][2])
                    {
                        i=decyzje[i][5];
                    }else{
                        i=decyzje[i][4];
                    }
                    break;
                case 2:
                    if(pytanie[decyzje[i][0]]>decyzje[i][2])
                    {
                        i=decyzje[i][5];
                    }else{
                        i=decyzje[i][4];
                    }
                    break;
                case 3:
                    if(pytanie[decyzje[i][0]]==decyzje[i][2])
                    {
                        i=decyzje[i][5];
                    }else{
                        i=decyzje[i][4];
                    }
                    break;
            }
            
        }
    }
    ofstream answer("wynik.txt");
    answer << wynik;
    answer.close();

    return 0;
}