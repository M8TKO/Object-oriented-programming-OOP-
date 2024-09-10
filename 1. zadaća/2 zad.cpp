/*
    Napišite funkciju 

bool provjeri(const deque<char> &znakovi)
koja prima referencu na deque znakova te uz korištenje iteratora i obrnutih iteratora provjerava predstavlja li taj niz znakova palindrom,
tj. slova tog niza čitana od početka prema kraju ili obrnuto glase jednako.
Primjerice, "Idu ljudi!" ili "Idu ljeta, pate ljudi".
Funkcija mora vratiti podatak tipa bool koji predstavlja informaciju je li dobiveni podatak palindom ili nije palindrom u gore opisanom smislu.
Zatim napišite funkciju main u kojoj ćete prvo učitati od korisnika pozitivan cijeli broj k.
Nakon toga učitavajte od korisnika znakove (ako učitavate znak po znak, kako se ne bi ignorirale bjeline, prije učitavanja prvog znaka stavite cin << noskipws; ).
Za svakih k uzastopih slova u unesenim znakovima, pomoću upravo napisane funkcije provjerite predstavljaju li oni palindrom. 
Sve takve pronađene palindrome spremite u listu i na kraju ih ispišite na ekran (u redoslijedu u kojem su uneseni). 
Pri ispisu, svaki palindrom mora biti ispisan u zasebnom retku (ako se u nekom javlja znak '\n', tada umjesto tog znaka ispišite znak ' '). 
Također, pri ispisu palindroma, ispišite samo znakove palindroma koji su razmaci ili slova (te nemojte ispisivati bjeline prije prvog slova palindroma, ako takve postoje).
*/

#include <iostream>
#include <list>
#include <deque>
#include <cctype>

using namespace std;

bool provjeri(const deque<char> &znakovi ){

    /*
        trivijalan slucaj :)
    */
    if( znakovi.empty() )
        return true;

    /*
        pozicioniramo se s pripadnim iteratorima na 
        kraj i na pocetak
    */
    deque<char>::const_iterator i1 = znakovi.cbegin();
    deque<char>::const_reverse_iterator i2 = znakovi.crbegin();
    //objasni ovo
    while( 1 ){

        /*
            i1 se krece prema desno dok ne naide na slovo
        */
        while( i1 != znakovi.cend() && !isalpha(*i1) )
            i1++;

        /*
            i2 se krece prema lijevo dok ne naide na slovo
        */
        while( i2 != znakovi.crend() && !isalpha(*i2) )
            i2++;

        /* 
            ukoliko je doslo do krizanja iteratora, imamo palindrom!
            ne mozemo usporedivati iterator i obrnuti iterator pa je potrebno napraviti
            odgovarajucu konverziju pomocu base()
            ---> ovdje je pokriven i slucaj ako u deque nema slova
        */
        if( i1 >= i2.base() - 1 )
            return true;

        /*
            usporedujemo pripadna slova i zanemarujemo ako su velika ili malena
        */
        if( tolower(*i1) != tolower(*i2) )
            return false;
        
        /*
            slova su ispala ista i nastavljamo dalje
        */
        i1++;
        i2++;
    }
}


/*
    funkcija koja ubacuje znakove iz deque u list<string>
*/
void ubaci( const deque<char> &znakovi, list<string> &L ){
        string s;
        for( auto x : znakovi ) 
            s += x;
        L.push_back(s);
}
int main(){

    /*
        ucitavamo broj i cijeli tekst
    */
    int k;
    cin >> k;

    string tekst,linija;
    while( getline(cin,linija) )
        tekst += linija + '\n';

    if( tekst.empty() )
        return 0;

    /*
        pomocu i1 se krecemo kroz tekst, a prvo se pozicioniramo
        na prvo slovo
    */
    string::iterator i1 = tekst.begin();
    deque<char> D;
    list<string> L;

    while( !isalpha(*i1) )
            i1++;

    /*
        u D ubacujemo prvih k slova,
        dalje cemo prvo slovo izbaciti i ubaciti sljedece,
        na taj nacin u D uvijek ostaje k slova
    */
    /*
        u varijabli n pamtimo koliko smo slova ubacili
    */
    int n = 0;
    while( i1 != tekst.end() ){

        if( *i1 == '\n')
            *i1 = ' ';

        if( *i1 == ' ' || isalpha(*i1) ){
            D.push_back(*i1);
            if( isalpha(*i1) )
                n++;
        }

        if( n == k )
            break;

        i1++;
    }

    cout << endl;
    while( i1 != tekst.end() ){

        if( provjeri(D) )
            ubaci(D,L);


        /*
            na pocetku je sigurno slovo pa njega maknemo,
            nadalje, micemo sve znakove s pocetka koji nisu slovo tj. razmake
        */
        D.pop_front();
        while( !isalpha(D.front() ))
            D.pop_front();

        /*
            i1 nastavlja dalje dok ne naide na slovo, 
            razmake isto tako ubacujemo
        */
        i1++;
        while( i1 != tekst.end() && !isalpha(*i1) ){

            if( *i1 == '\n' )
                *i1 = ' ';

            if( *i1 == ' ' )
                D.push_back(*i1);
        
            i1++;
        }

        if( i1 == tekst.end() )
                break;

        /*
            i1 sada pokazuje na slovo pa je tada izasao iz while petlje,
            pa to slovo moramo ubaciti
        */
        D.push_back(*i1);


    }

    for( auto x : L )
        cout << x << endl;

    return 0;
}
