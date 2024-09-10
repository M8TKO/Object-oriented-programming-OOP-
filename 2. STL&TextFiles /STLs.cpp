/*
The file prodaja.txt contains data about sold tickets from a bus company. For each ticket, the following data is recorded in the file (each on a separate line!):

- starting location,
- destination,
- price (a number representing the amount in EUR),
- ticket type (e.g., one-way),
- departure date and time (in the format mm:hh dd.MM.yyyy).

After the data for each ticket, there may be "empty" lines in the file, specifically lines that contain only whitespace (whitespace includes ' ', '\f', '\n', '\r', '\t', '\v') - ignore such lines.

Define a structure for relations that stores data about a single relation, specifically:

- starting location for that relation,
- destination for that relation.

Using an unordered multi-map container with at least 10 buckets, load the ticket data from the file prodaja.txt so that for each line, we have the ticket data stored for that line. Finally, print all loaded data by bucket, first printing the bucket number and then all data from that bucket - each line must be in the format:

(starting location, destination) -> x EUR, type, date and time

Do not print data about empty buckets. When defining your own hash function, briefly explain in a comment in your code the choice of that hash function.
*/


/*
    Container we will use to store:
    - price
    - date
    - time  |
               |
               v
*/
typedef tuple<string,string,string> info;

/*
    Our hash function - created analogously to
                         the hash function from the exercise
*/
size_t relacija_h(const relacija &R){
    return  hash<string>()(R.start) ^
            hash<string>()(R.end);
}

/*
    Define operator == so we can
    define the required unordered container
*/
bool operator == (const relacija &R1, const relacija &R2)
{
  return (R1.start == R2.start) && (R1.end == R2.end);
}

/*
    Function that removes \r characters from
    the container
    remove() is a function from <algorithm>
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
            Check if we have read an empty line
        */
        if(  s.find_first_not_of(" \f\n\r\t\v") == string::npos )
            continue;

        /*
            Read data from the file and insert it
            into the multimap
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

    // Print all elements
    for(int i = 0 ; i < M.bucket_count() ; i++){
        if( !M.bucket_size(i) )
            continue;

        cout << "Elements in bucket " << i << ":" << endl;
        for( auto it = M.begin(i) ; it != M.end(i) ; it++ )
            cout << "\t(" << it->first.start << "," << it->first.end 
            << ") -> " << get<0>(it->second) << " EUR, " 
            << get<1>(it->second) << ", "
            << get<2>(it->second) << endl;
        
    }

    dat.close();
    return 0; 
}
