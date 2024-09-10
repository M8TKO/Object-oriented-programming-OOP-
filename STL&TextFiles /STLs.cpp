/*
Datoteka prodaja.txt sadrži podatke o prodanim kartama jedne autobusne tvrtke. Za svaku kartu upisani su u tu datoteku sljedeći podaci (svaki u posebnom retku!):

naziv polazišta,
 naziv odredišta,
cijena (broj koji predstavlja iznos u EUR),
tip karte (npr. jednosmjerna),
datum i vrijeme polaska (oblika mm:hh dd.MM.yyyy).
U datoteci nakon podataka za pojedinu kartu mogu postojati ,,prazni'' retci, preciznije, retci koji sadrže samo bjeline (bjeline su ' ', '\f', '\n', '\r', '\t', '\v') - takve retke zanemarite.

Definirajte strukturu relacija koja pamti podatke o jednoj relaciji i to:

naziv polazišta za tu relaciju,
 naziv odredišta za tu relaciju.
Korištenjem neuređenog višestrukog preslikavanja - preciznije, unordered_multimap spremnika uz minimalno 10 pretinaca, učitajte podatke o kartama iz datoteke prodaja.txt tako da za svaku liniju imamo spremljene podatke o kartama za tu liniju. Naposlijetku, ispišite na ekran sve učitane podatke po pretincima, na način da se prvo ispiše broj pretinca te zatim svi podaci iz tog pretinca - svaki redak mora biti u formatu:

(polazište, odredište) -> x EUR, tip, datum i vrijeme
Nemojte ispisivati podatke o praznim pretincima. Pri definiranju vlastite hash-funkcije, kratko obrazložite u komentar u svom kodu odabir te hash-funkcije.
*/



#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <tuple>
#include <utility>
#include <algorithm>

using namespace std;

/*
    spremnik u koji cemo spremati:  
    - cijenu
    - datum
    - vrijeme  |
               |
               v
*/
typedef tuple<string,string,string> info;

struct relacija{
    string start,end;
};

/*
    Nasa hash funkcija - napravljena analogno kao
                         hash funkcija s vjezbi
*/
size_t relacija_h(const relacija &R){
    return  hash<string>()(R.start) ^
            hash<string>()(R.end);
}

/*
    definiramo operator == tako da mozemo
    definirati potrebni neuređeni spremnik
*/
bool operator == (const relacija &R1, const relacija &R2)
{
  return (R1.start == R2.start) && (R1.end == R2.end);
}

/*
    funckija koja mice znakove \r iz 
    spremnika
    remove() je funkcija iz <algorithm>
*/
void ocisti(relacija &R, info &I){

    remove(R.start.begin(), R.start.end(), '\r');
    remove(R.end.begin(), R.end.end(), '\r');

    remove(get<0>(I).begin(), get<0>(I).end(), '\r');
    remove(get<1>(I).begin(), get<1>(I).end(), '\r');
    remove(get<2>(I).begin(), get<2>(I).end(), '\r');
}

int main() {

    unordered_multimap<relacija,info,
        decltype(relacija_h)*> M(10,relacija_h);
    ifstream dat;
    string s;
    dat.open("prodaja.txt");

    while( getline(dat,s) ){

        /*
            provjera ako smo ucitali prazan redak
        */
        if(  s.find_first_not_of(" \f\n\r\t\v") == string::npos )
            continue;

        /*
            ucitavamo podatke iz datoteke i ubacujemo ih 
            u multimap
        */
        relacija R;
        R.start = s;
        getline(dat,s);
        R.end = s;

        info I;
        getline(dat,s);
        get<0>(I) = s;
        getline(dat,s);
        get<1>(I) = s;
        getline(dat,s);
        get<2>(I) = s;

        ocisti(R,I); 
        M.insert({R,I});
    }

    //ispis svih elemenata
    for(int i = 0 ; i < M.bucket_count() ; i++){
        if( !M.bucket_size(i) )
            continue;

        cout << "Elementi u pretincu " << i << ":" << endl;
        for( auto it = M.begin(i) ; it != M.end(i) ; it++ )
            cout << "\t(" << it->first.start << "," << it->first.end 
            << ") -> " << get<0>(it->second) << " EUR, " 
            << get<1>(it->second) << ", "
            << get<2>(it->second) << endl;
        
    }

    dat.close();
    return 0; 
}
