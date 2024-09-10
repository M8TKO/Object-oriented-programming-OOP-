
/*
Napišite program koji radi rangiranje filmova prema ocjenama publike.
 Naziv filma je ujedno i naziv .txt datoteke. 
 Primjerice, za film s nazivom "Gospodar podataka - Povratak prioritetnog reda" imamo datoteku Gospodar podataka - Povratak prioritetnog reda.txt. 
Svaka datoteka sadrži ocjene publike (barem jednu!) za film s tim nazivom, a svaka ocjena je prirodan broj manji ili jednak 5.
Potrebno je napraviti strukturu film koja sadrži sve navedene podatke o pojedinom filmu (naziv filma i sve ocjene za taj film,
uz ostale podatke za koje smatrate da ih treba pamtiti).
Zatim treba korištenjem prikladnog spremnika (ili adaptera) spremiti podatke o svim filmovima čije nazive odgovarajućih datoteke (bez ekstenzije ".txt") 
program prima kao argumente komandne linije (ne treba provjeravati uspješnost otvaranja pojedine datoteke). Pritom mora vrijediti:

Filmovi u tom spremniku (ili adapteru) sortirani su silazno prema prosječnoj ocjeni gledatelja, 
tako da korisnik može dobiti film s najvećom prosječnom ocjenom u vremenu O(1) te ubaciti podatke o novom filmu u vremenu O(log n).
 Također, nemojte da se pri ubacivanju filma mora puno puta računati prosječna ocjena gledatelja za filmove koji su već u spremniku.
Nakon učitavanja svih podataka,
 ispišite sve podatke o svim filmovima iz korištenog spremnika u silaznom poretku prema prosječnoj ocjeni filma 
 (dakle tako da je film s najvećom prosječnom ocjenom ispisan prvi). U komentar u kodu obrazložite izbor spremnika (ili adaptera) koji ste koristili.
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

/*
    pamtimo i prosjek kako ga ne bismo
    morali stalno racunati
*/
struct film{
    string ime;
    vector<int> ocjene;
    double prosjek;
};

/*
    omogucili smo ispisivanje filma pomocu >>
*/
ostream &operator << (ostream &out, const film &film)
{
   out << "Naziv filma: " << film.ime << endl;

   out << "Ocjene: ";
   for(int i = 0 ; i < film.ocjene.size() ; i++)
        out << film.ocjene[i] << " ";
    out << endl;

    out << "Prosjek: " << film.prosjek << endl;

    return out;
}

/*
    komparator koji usporeduje filmove na temelju 
    prosjeka ocjena
*/
struct Usporedi {
    bool operator()(film prvi, film drugi) {
        return  prvi.prosjek <= drugi.prosjek ;
    }
};

int main(int n, char* nazivi[]){
    /*
        izabrao sam prioritetni red zbog zadovoljavaja
        uvjeta slozenosti
    */
    priority_queue<film,vector<film>,Usporedi> filmovi;
    ifstream dat;
    int ocjena;

    /*
        ostatak koda je sasvim čitljiv :)
    */
    for( auto p = nazivi+1 ; p != nazivi + n ; p++ ){
        dat.open(string(*p) + ".txt");

    	film film({string(*p)});

        film.prosjek = 0;
        while( dat >> ocjena ){
            film.ocjene.push_back(ocjena);
            film.prosjek += ocjena;
        }
        film.prosjek /= film.ocjene.size();
        filmovi.push(film);
        
        dat.close();
    }


    /*
        ispis filmova
    */
    while( !filmovi.empty() ){
        cout << filmovi.top();
        filmovi.pop();
    }

        
    return 0;
}
