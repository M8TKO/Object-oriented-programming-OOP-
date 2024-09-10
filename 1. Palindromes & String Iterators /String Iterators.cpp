/*
    Write a program that reads text from the user (until EOF).
    The text represents a mathematical problem that contains data about some lengths expressed in millimeters, centimeters, or decimeters
    (each such piece of data consists of a positive number, without a sign, and possibly with a decimal point, followed by the corresponding unit of measurement).
    Full names or abbreviations mm, cm, or dm are used for the units of measurement.
    It is necessary to convert and display these lengths in meters (with the corresponding full name or abbreviation m, depending on whether the full name or abbreviation was used in the input - see examples!).
    Any number of spaces may appear between the unit of measurement and the corresponding number (spaces are considered to be the following characters: ' ', '\t', '\n', '\v', '\f', '\r').
    Make sure that spaces and line breaks are preserved!
    Assume that the text entered by the user does not contain compound units of measurement (for example, the input cannot contain text like "...has a speed of 5 dm/h.").
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

/*
    We want to place all measurement units in a set, so
    instead of manually writing all the words,
    I decided to write only the case endings,
    and form the words in the function napuni()
    where, based on the root word, we add case endings
    for example,
    milimet + ara = milimetara
*/
vector<string> padezi = { "ar","ra","ru","re","rom",
                        "ri","ara","rima"};

set<string> mjerne_jed;

void napuni(){
    /*
        We add all forms of the measurement units to the set mjerne_jed
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
        Check if s is a number
        1. It consists only of digits and a dot
        2. There is at most one dot
        3. The dot is not at the beginning
        4. The dot is not at the end
    */
    return ( s.find_first_not_of(".0123456789") == string::npos &&
                s.find_first_of(".") == s.find_last_of(".") &&
                s.find_first_of(".") != 0 &&
                s.find_last_of(".") != s.length()-1
                );
}

int f( string& iznos, string& rijec){
    /*
        A function that checks if the word is a unit of measurement.
        If it is, we return the modified value in the variable iznos,
        and through the return value m we return how many characters
        must be deleted from the unit of measurement. For example,
        milimetar --> metar | delete 4 characters, mili
        dm ---> m | delete 1 character.
        ---> We use the fact that the case ending remains the same,
             and that the word metar is part of all the required
             units of measurement :)

        x will be the corresponding power of 10 we divide by.
        For example,
        if we are converting from cm to m, then x = 100.
    */
    int m, x;
    auto it = mjerne_jed.find(rijec);

    /*
        We search if the word is a unit of measurement.
    */
    if( it == mjerne_jed.end() )
        return 0;

    /*
        To find out which unit of measurement it is,
        it's enough to check whether the first letter is m, c, or d.
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
        In the case where the unit of measurement
        consists of only 2 letters.
    */
    if( (*it).length() == 2 )
        m = 1;

    /*
        The rest of the function converts the amount accordingly.
    */
    double money = stod(iznos) / x;
    iznos = to_string(money);
    /*
        The value might be something like "5.60000",
        so if there is a dot, we remove any extra zeroes
        and make sure the number does not end with a dot.
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
        We read lines until EOF. Since getline() stops when it
        encounters '\n' and does not save it, we need to add it back.
    */
    string tekst, linija;
    while( getline(cin, linija) )
        tekst += linija + '\n';

    /*
        We position at the first digit.
    */
    auto it1 = tekst.find_first_of("0123456789", 0);
    decltype(it1) it2, it3;

    /*  
        We separate the text word by word until
        we reach the end of the string.
    */
    while( it1 != string::npos ){
        
        /*
            - Between it1 and it2, we place the number.
            - it2 will even understand something like "53.242.234......4"
              as a number, but later we will discard that
              as a valid unit of measurement input.
        */
        it2 = tekst.find_first_not_of(".0123456789", it1+1);

        if( it2 == string::npos )
            break;

        string iznos = tekst.substr(it1, it2-it1);

        /*
            We check whether we've isolated a number.
        */
        if( broj(iznos) ){
            
            int k = iznos.length();
            /*
                - Now we need to check whether the next word
                  is a unit of measurement.
                - it2 is positioned at the start of the next word.
            */
            it2 = tekst.find_first_not_of(" \n\t\v\f\r", it2);
            
            if( it2 == string::npos )   
                break;

            /*
                it3 is positioned at the end of the next word.
            */
            it3 = tekst.find_first_not_of(slova, it2);

            /*
                Length of the next word.
            */
            int duljina = ( it3 == string::npos ) ? tekst.length() : it3-it2;
            string rijec = tekst.substr(it2, duljina);

            /*
                We check if that word is a unit of measurement.
                In function f, it's explained how it works.
            */
            int m;
            if( m = f(iznos, rijec) ){
                tekst.erase(it2, m);
                tekst.replace(it1, k, iznos);
                
            }
        }
        /*
            Move to the next number.
        */
        it1 = tekst.find_first_of("0123456789", it1+1);
    }

    cout << tekst;
    return 0;
}
```
