/*
Write a program that ranks movies based on audience ratings.
The name of the movie is also the name of the .txt file.
For example, for the movie titled "Lord of the Data - Return of the Priority Queue," the corresponding file would be "Lord of the Data - Return of the Priority Queue.txt."
Each file contains audience ratings (at least one!) for the movie with that title, and each rating is a natural number less than or equal to 5.
It is necessary to create a structure `film` that contains all the mentioned data about a particular movie (movie title and all ratings for that movie,
along with other data you think should be stored).
Then, using an appropriate container (or adapter), store the data about all the movies whose names match the corresponding files (excluding the ".txt" extension),
which the program receives as command line arguments (there is no need to check whether the file was opened successfully). The following must apply:

The movies in that container (or adapter) are sorted in descending order based on the average audience rating, 
so that the user can get the movie with the highest average rating in O(1) time and insert a new movie's data in O(log n) time.
Additionally, make sure that when inserting a movie, you do not have to recalculate the average audience rating for movies already in the container.
After loading all the data, print all the data about all movies from the used container in descending order by the movie's average rating
(so that the movie with the highest average rating is printed first). In the code comments, explain the choice of container (or adapter) you used.
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

/*
    We store the average rating so that we don't have to
    recalculate it constantly.
*/
struct film{
    string name;
    vector<int> ratings;
    double average;
};

/*
    Enabled printing of movie details using >>
*/
ostream &operator << (ostream &out, const film &movie)
{
   out << "Movie title: " << movie.name << endl;

   out << "Ratings: ";
   for(int i = 0 ; i < movie.ratings.size() ; i++)
        out << movie.ratings[i] << " ";
    out << endl;

    out << "Average rating: " << movie.average << endl;

    return out;
}

/*
    Comparator that compares movies based on
    their average ratings.
*/
struct Compare {
    bool operator()(film first, film second) {
        return first.average <= second.average;
    }
};

int main(int n, char* names[]){
    /*
        I chose a priority queue to satisfy the 
        complexity requirements.
    */
    priority_queue<film, vector<film>, Compare> movies;
    ifstream file;
    int rating;

    /*
        The rest of the code is perfectly readable :)
    */
    for( auto p = names + 1 ; p != names + n ; p++ ){
        file.open(string(*p) + ".txt");

    	film movie({string(*p)});

        movie.average = 0;
        while( file >> rating ){
            movie.ratings.push_back(rating);
            movie.average += rating;
        }
        movie.average /= movie.ratings.size();
        movies.push(movie);
        
        file.close();
    }

    /*
        Printing the movies
    */
    while( !movies.empty() ){
        cout << movies.top();
        movies.pop();
    }

    return 0;
}
