/*
A company involved in the production and distribution of ice cream visited cities and
recorded the ratings that random passers-by gave to their new ice cream.
The collected data is stored in the file ulaz.txt in such a way that each line of that file contains the name of the city (which does not contain the ':' character), a colon ':', 
the total number of ratings received in that city, and then all the ratings received (all numbers listed are separated by a space).

The measurement data for one city is stored in the Mjerenje class.
In this class, we store the name of the city to which the data relates, the number of ratings received in that city, and all the ratings received.
The class has one constructor that loads the measurement data for one city from a line of an already opened file for reading,
a method dodaj that increases all stored ratings by a certain amount of type iznos 
(e.g., by 1; note that in the example accompanying the task, iznos is actually an int), and a method ispis that prints the data of the given class 
(the name of the city and all ratings for that city separated by spaces) to the given ostream object. The described methods return a type Mjerenje& so they can be chained.

In addition to the aforementioned methods, the Mjerenje class has full copy control: 
a copy constructor, copy assignment operator, move constructor, move assignment operator, and destructor.

The class must behave like a pointer, i.e., when copying, there should be no unnecessary copying of resources 
(i.e., all the ratings received for the given city).
Furthermore, each instance of the Mjerenje class has a unique id (which is assigned when the instance is constructed, and the assigned id values are: 0, 1, 2, etc.).
The ispis method must (for the instance on which the method is called) print the id of the corresponding instance.

Your task is to implement all the necessary methods 
(the aforementioned methods, copy control, etc.) in the file implementacija.cpp (create and submit only that file!) 
so that, when compiled with the accompanying files for this task (which are the files Mjerenje.h, main.cpp, and ulaz.txt), the following output is produced after compilation with:

g++ implementacija.cpp main.cpp -std=c++11 -o prog
the following output is expected:

Zagreb(id = 0): 2 5 6 3 1 4 5 2 1 4 5 1 2 5 4 5 8 7 6 9 5 4 1 2 3 6 5 4 7 8 6 5 4 1 2 3 6 9 8 5 4 1 2 3 6 9 8 5 4 1

Slavonski Brod(id = 1): 5 4 6 9 8 5 4 2 1 3 6 5 8 4 5 6 9 8 7 5 6 4 7 5 2 1 3 6 5 8 4 2 3 6 5 8 7 4 5 9

Split(id = 2): 4 5 2 1 4 5 1 2 6 7 8 9 6 5 4 7 8 9 6 5 4 1 2 3 6 5 8 9 7 8 5 4 1 2 3 6 5 8 9 6 4 2 1 4 5 6 3 2 1 4

Slavonski Brod(id = 2): 5 4 6 9 8 5 4 2 1 3 6 5 8 4 5 6 9 8 7 5 6 4 7 5 2 1 3 6 5 8 4 2 3 6 5 8 7 4 5 9

Zagreb(id = 4): 2 5 6 3 1 4 5 2 1 4 5 1 2 5 4 5 8 7 6 9 5 4 1 2 3 6 5 4 7 8 6 5 4 1 2 3 6 9 8 5 4 1 2 3 6 9 8 5 4 1

Slavonski Brod(id = 1): 6 5 7 10 9 6 5 3 2 4 7 6 9 5 6 7 10 9 8 6 7 5 8 6 3 2 4 7 6 9 5 3 4 7 6 9 8 5 6 10

Then, add a message to each method that prints to clog (you'll notice in the main function from the main.cpp file that it's redirected to a new file log.txt) which method (constructor, destructor, etc.) was called and the id of the instance whose method was called.
*/

#include<string>
#include<fstream>
#include"Mjerenje.h"

using namespace std;

int Mjerenje::brojac = 0;

Mjerenje::Mjerenje(ifstream &i){
    
    id = brojac++;
    clog << "Constructor call - loading from file (id = "
         << id << ")" << endl;

    getline(i, naziv, ':');
    i >> br_mjerenja;
    mjerenja = new int[br_mjerenja];
    for(int j = 0; j < br_mjerenja ; j++)
        i >> mjerenja[j];

    br_ref = new int;
    *br_ref = 1;

    /*
        Now we are at the end of the line in the file, so
        we need to move to the next line so that the name of the next
        city does not start with '\n'
        (it would also be read because our getline() in line 17
        reads up to ':' and not to a newline)
    */
    string s; getline(i, s);
}

Mjerenje::Mjerenje(const Mjerenje& M) {

    id = brojac++;
    clog << "Copy constructor call (id = " 
         << id << ")" << endl;

    naziv = M.naziv;
    br_mjerenja = M.br_mjerenja;
    mjerenja = M.mjerenja;
    br_ref = M.br_ref;
    (*br_ref)++;
}

Mjerenje& Mjerenje::operator=(const Mjerenje& M){

    clog << "Copy assignment operator call (id = " 
         << id << ")" << endl;

    (*(M.br_ref))++;

    (*br_ref)--;
    if (!br_ref){
        delete[] mjerenja;
        delete br_ref;
    }

    naziv = M.naziv;
    br_mjerenja = M.br_mjerenja;
    mjerenja = M.mjerenja;
    br_ref = M.br_ref;

    return *this;
}

Mjerenje::Mjerenje(Mjerenje&& M) noexcept {

    id = brojac++;
    clog << "Move constructor call (id = " 
         << id << ")" << endl;

    naziv = M.naziv;
    br_mjerenja = M.br_mjerenja;
    mjerenja = M.mjerenja;
    br_ref = M.br_ref;
    
    M.mjerenja = M.br_ref = nullptr;
}

Mjerenje& Mjerenje::operator=(Mjerenje&& M) noexcept {

    clog << "Move assignment operator call (id = " 
         << id << ")" << endl;
    
    if (this == &M)
        return *this;

    (*br_ref)--;
    if (!br_ref){
        delete[] mjerenja;
        delete br_ref;
    }

    naziv = M.naziv;
    br_mjerenja = M.br_mjerenja;
    mjerenja = M.mjerenja;
    br_ref = M.br_ref;
    
    M.mjerenja = M.br_ref = nullptr;
    return *this;
}

Mjerenje::~Mjerenje(){

    clog << "Destructor call (id = " 
         << id << ")" << endl;

    (*br_ref)--;
    if (!br_ref){
        delete[] mjerenja;
        delete br_ref;
    }
}

Mjerenje& Mjerenje::dodaj(Mjerenje::iznos x) {

    clog << "Function dodaj call (id = " 
         << id << ")" << endl;

    for(int i = 0 ; i < br_mjerenja ; i++ )
        mjerenja[i] += x;
    return *this;
}

Mjerenje& Mjerenje::ispis(ostream &o){

    clog << "Function ispis call (id = " << id << ")" << endl;

    o << naziv << "(id = " << id << "): ";

    for (int i = 0; i < br_mjerenja; i++)
        o << mjerenja[i] << " ";
    o << endl;

    return *this;
}
