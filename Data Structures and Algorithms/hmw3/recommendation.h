#include <string>

using namespace std;

class RecommendationSystem{
public:
    // constructor
    RecommendationSystem(int** userMovieRatingsMatrix_in, int** userShowRatingsMatrix_in);

    // class functions
    void recommendMovies(int userId, int numRecommendations, int* recommendedMovies) const;
    void recommendShows(int userId, int numRecommendations, int* recommendedShows) const;


private:
    // class pointers
    int** userMovieRatingsMatrix;
    int** userShowRatingsMatrix;
};