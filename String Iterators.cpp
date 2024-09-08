/*
Napišite program koji od korisnika učitava tekst (do EOF). 
Tekst predstavlja tekst matematičkog zadatka u kojem se javljaju podaci o nekim duljinama iskazanima u milimetrima, centimetrima ili decimetrima 
(svaki takav podatak koji promatramo sastoji se od jednog pozitivnog broja, bez predznaka i možda s decimalnom točkom, te pripadne mjerne jedinice).
Pritom se za mjerne jedinice koriste puni nazivi ili oznake mm, cm ili dm. 
Potrebno je preračunati i prikazati te duljine u metrima (uz pripadni puni naziv ili oznaku m, ovisno o tome je li u unesenom tekstu bio puni naziv ili je bila oznaka - vidi primjere!). 
Između mjerne jedinice i pripadnog broja može se nalaziti proizvoljan broj praznina (smatramo da su praznine sljedeći znakovi: ' ', '\t', '\n', '\v', '\f', '\r'). 
Pripazite da razmaci i prelasci u novi red budu očuvani! 
Pretpostavite da u tekstu koji je korisnik unio nema složenih mjernih jedinica (tako se u ulazu, primjerice, ne može javiti tekst "...ima brzinu 5 dm/h.").
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

/*
    zelimo u skup staviti sve mjerne jedinice pa 
    umjesto da pisem rucno sve te rijeci,
    odlucio sam samo padezne nastavke napisati, 
    a same rijeci tvorim u funkiciji napuni()
    gdje na osnovu rijeci stavljam padezne nastavke
    npr. 
    milimet + ara = milimetara
*/
vector<string> padezi = { "ar","ra","ru","re","rom",
                        "ri","ara","rima"};

set<string> mjerne_jed;

void napuni(){
    /*
        u skup mjerne_jed stavljamo sve oblike rijeci mjernih jedinica
    */
    mjerne_jed.insert("mm");
    for( auto x : padezi )
        mjerne_jed.insert("milimet" + x );

    mjerne_jed.insert("cm");
    for( auto x : padezi )
        mjerne_jed.insert("centimet" + x );

    mjerne_jed.insert("dm");
    for( auto x : padezi )
        mjerne_jed.insert("decimet" + x );

}

bool broj(string s){ 
    /* 
        provjeravamo je li s broj
        1. je li sastavljen samo od brojki i tocke
        2. postoji najvise jedna tocka
        3. ta tocka nije na pocetku
        4. ta tocka nije na kraju
    */
    return ( s.find_first_not_of(".0123456789") == string::npos &&
                s.find_first_of(".") == s.find_last_of(".") &&
                s.find_first_of(".") != 0 &&
                s.find_last_of(".") != s.length()-1
                );
}

int f( string& iznos, string& rijec){
    /*
        f-ja koja provjerava je li rijec mjerna jedinica
        ako jest, u varijabli iznos vracamo promijenjeni iznos 
        a preko povratne vrijednosti m vracamo koliko znakova
        moramo obrisati od mjerne jedinice npr.
        milimetar --> metar | brisemo 4 znaka, mili
        dm ---> m | brisemo 1 znak
        ---> iskoristavamo cinjenicu da padezni nastavak ostaje isti
             te da je rijec metar sastavni dio svih traznih mjernih
             jedinica :)

        x ce biti odgovarajuca potencija od 10 s kojom dijelimo
        npr.
        ako prelazimo iz cm u m onda je x = 100
    */
    int m,x;
    auto it = mjerne_jed.find(rijec);

    /*
        trazimo je li rijec mjerna jedinica
    */
    if( it == mjerne_jed.end() )
        return 0;

    /*
        da bismo saznali o kojoj je mjernoj jedinici rijec,
        dovoljno je gledati je li prvo slovo m, c ili d

    */
    switch((*it)[0]) {
        case 'm':
            m = 4;
            x = 1000;
            break;
        case 'c':
            m = 5;
            x = 100;
            break;
        case 'd':
            m = 4;
            x = 10;
            break;
        }

    /*
        slucaj ako je mjerna jedinica sastavljena od
        samo 2 slova
    */
    if( (*it).length() == 2 )
        m = 1;

    /*
        ostatak f-je pretvara u odgovarajuci iznos
    */
    double money = stod(iznos) / x;
    iznos = to_string(money);
    /*
        moguce da je iznos == "5.60000"
        pa ako postoji tocka, micemo sve nule koje su viska
        i pazimo da broj ne zavrsava s tockom
    */
    
    if( iznos.find_first_of(".") != string::npos ){

        iznos = iznos.substr(0, iznos.find_last_of(".123456789")+1);
        if( iznos[iznos.length()-1] == '.' )
            iznos.resize(iznos.length()-1);

    }

    return m;
} 


int main(){
    
    string slova;
    for( int i = 0 ; 'a' + i <= 'z' ; i++)
        slova += 'a' + i;

    napuni();

    /*
        ucitavamo linije sve do EOF, kako getline() stane kada
        dode do '\n' i ne sacuva ga, moramo ga nadodati
    */
    string tekst,linija;
    while( getline(cin,linija) )
        tekst += linija + '\n';


    /*
        pozicioniramo se na prvu brojku
    */
    auto it1 = tekst.find_first_of("0123456789",0);
    decltype(it1) it2,it3;

    /*  
        iz teksta odvajamo rijec po rijec sve dok
        ne dodemo do kraja stringa
    */
    while( it1 != string::npos ){
        
        /*
            -   izmedu it1 i it2 stavljamo broj
            -   it2 ce i npr. "53.242.234......4" shvatiti kao broj
                medutim, kasnije cemo tu mogucnost odbaciti 
                kao valjan unos mjerne jedinice
        */
        it2 = tekst.find_first_not_of(".0123456789",it1+1);

        if( it2 == string::npos )
            break;

        string iznos = tekst.substr(it1,it2-it1);

        
        /*
            provjeravamo jesmo li izolirali broj
        */
        if( broj(iznos) ){
            
            int k = iznos.length();
            /*
                -   sada moramo vidjeti je li sljedeca rijec 
                    mjerna jedinica
                -   it2 pozicioniramo na pocetak sljedece rijeci
            */
            it2 = tekst.find_first_not_of(" \n\t\v\f\r",it2);
            
            if( it2 == string::npos )   
                break;

            /*
                it3 pozicioniramo na kraj sljedece rijeci
            */
            it3 = tekst.find_first_not_of(slova,it2);

            /*
                duljina sljedece rijeci
            */
            int duljina = ( it3 == string::npos ) ? tekst.length() : it3-it2;
            string rijec = tekst.substr(it2,duljina);

            /*
                gledamo je li ta rijec mjerna jedinica,
                u funkciji f je opisano kako funkcija radi
            */
            int m;
            if( m = f(iznos,rijec) ){
                tekst.erase(it2,m);
                tekst.replace(it1, k , iznos);
                
            }
        }
        /*
            idemo na sljedeci broj
        */
        it1 = tekst.find_first_of("0123456789",it1+1);
    }

    cout << tekst;
    return 0;
}
