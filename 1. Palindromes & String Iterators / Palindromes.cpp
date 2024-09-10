/*
    Write a function

bool provjeri(const deque<char> &znakovi)
that takes a reference to a deque of characters and, using iterators and reverse iterators, checks if this sequence of characters represents a palindrome, i.e., whether the characters in the sequence read the same forwards and backwards.
For example, "Idu ljudi!" or "Idu ljeta, pate ljudi".
The function must return a boolean value that indicates whether the given sequence is a palindrome as described above.
Then, write a main function in which you first read a positive integer k from the user.
After that, read characters from the user (if reading character by character, to avoid ignoring spaces, before reading the first character, use cin << noskipws;).
For every k consecutive characters in the entered sequence, use the function you wrote to check if they form a palindrome.
All such found palindromes should be stored in a list and printed to the screen in the order they were entered.
When printing, each palindrome must be printed on a separate line (if a newline character '\n' appears in the palindrome, print a space instead).
Also, when printing palindromes, only print characters that are spaces or letters (and do not print any spaces before the first letter of the palindrome, if there are any).
*/

#include <iostream>
#include <list>
#include <deque>
#include <cctype>

using namespace std;

bool provjeri(const deque<char> &znakovi ){

    /*
        trivial case :)
    */
    if( znakovi.empty() )
        return true;

    /*
        position the appropriate iterators 
        at the beginning and the end
    */
    deque<char>::const_iterator i1 = znakovi.cbegin();
    deque<char>::const_reverse_iterator i2 = znakovi.crbegin();
    //explain this
    while( 1 ){

        /*
            i1 moves right until it finds a letter
        */
        while( i1 != znakovi.cend() && !isalpha(*i1) )
            i1++;

        /*
            i2 moves left until it finds a letter
        */
        while( i2 != znakovi.crend() && !isalpha(*i2) )
            i2++;

        /* 
            if the iterators cross paths, we have a palindrome!
            we cannot compare an iterator and a reverse iterator, so we need to 
            convert it using base()
            ---> this also covers the case when there are no letters in the deque
        */
        if( i1 >= i2.base() - 1 )
            return true;

        /*
            compare the corresponding letters, ignoring case
        */
        if( tolower(*i1) != tolower(*i2) )
            return false;
        
        /*
            the letters match, so we continue
        */
        i1++;
        i2++;
    }
}


/*
    function that inserts characters from deque into list<string>
*/
void ubaci( const deque<char> &znakovi, list<string> &L ){
        string s;
        for( auto x : znakovi ) 
            s += x;
        L.push_back(s);
}
int main(){

    /*
        read the number and the entire text
    */
    int k;
    cin >> k;

    string tekst,linija;
    while( getline(cin,linija) )
        tekst += linija + '\n';

    if( tekst.empty() )
        return 0;

    /*
        use i1 to traverse the text, and first position it 
        on the first letter
    */
    string::iterator i1 = tekst.begin();
    deque<char> D;
    list<string> L;

    while( !isalpha(*i1) )
            i1++;

    /*
        insert the first k letters into D,
        moving forward we will remove the first letter and insert the next one,
        this way D will always contain k letters
    */
    /*
        n variable keeps track of how many letters we've inserted
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
            the first character is definitely a letter, so we remove it,
            from now on, we remove all characters from the front that aren't letters, i.e., spaces
        */
        D.pop_front();
        while( !isalpha(D.front() ))
            D.pop_front();

        /*
            i1 continues forward until it finds a letter,
            spaces are also inserted
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
            i1 now points to a letter, so it has exited the while loop,
            we now need to insert that letter
        */
        D.push_back(*i1);


    }

    for( auto x : L )
        cout << x << endl;

    return 0;
}
