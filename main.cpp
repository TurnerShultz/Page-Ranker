// Written by Turner Shultz
#include <iostream>
#include <iomanip>
#include <map>
#include <utility>
#include <vector>
using namespace std;

class AdjacencyList {

private:

    map<string, vector<pair<string,string>>> toFrom;
    map<string, vector<pair<string,string>>> fromTo;
    map<string, int> sizes;
    vector<double> vec;
    vector<double> newVec;

public:

    /* In this function, there are two different map that the urls are inserted into. The user inputs a "from" url and a
    "to" url for each line. This function has two maps: one that inserts the "to" url as the key and the "from' url as
    the value, and one that does the exact opposite. The reasoning for this is explained in the next function. */

    void insert(string &from, string &to) {

        toFrom[to].push_back(make_pair(from, to));

        if (toFrom.find(from) == toFrom.end()) {

            toFrom[from] = {};

        }

        fromTo[from].push_back(make_pair(to, from));

        if (fromTo.find(to) == fromTo.end()) {

            fromTo[to] = {};

        }

    }

    /* The function below uses another map. This map stores each url as a key, and the value for each key is the number
    of outgoing edges that particular url points to. This is used for calculating the PageRanks. */

    void vertSize() {

        int size = 0;

        map<string, vector<pair<string,string>>> :: iterator it;

        for (it = fromTo.begin(); it != fromTo.end(); ++it) {

            for (auto & i : it->second) {

                size++;

            }

            sizes.emplace(it->first, size);
            size = 0;

        }

    };

    /* This function below is the most important one. To start, the "firstRank" is calculated first, which is the
    starting rank for each url, which is 1 divided by the unique number of vertices. The values are then placed into a
    vector, which is the same size as the toFrom map. So all of the values in the vector will start off being the same. */

    void calcRank(int &power) {

        double firstRank = 1.0 / toFrom.size();
        double rank = 0.0;
        int j;
        vec.resize(toFrom.size(), firstRank);
        newVec.resize(toFrom.size(), 0);
        map<string, vector<pair<string, string>>> :: iterator it;

        /* If power iterations = 1, then the values in the vector would not change. They are then placed in a new vector,
        and the function is ended. */

        if (power == 1) {

            newVec = vec;

        }

        // If the number of power iterations is greater than 1, Then a for loop is ran power - 1 times.

        else {

            for (int k = 0; k < power - 1; k++) {

                j = 0;

                for (it = toFrom.begin(); it != toFrom.end(); ++it) {

                    /* Here, the toFrom map is iterated through. As a reminder, the toFrom map stores a url and
                    which urls point to it in a graph. In other words, it stores the incoming vertices for each url.
                    Next, the values are iterated through for each key. This is where the sizes map comes into play.
                    If a value for a key in the toFrom map matches with a key in the sizes map, then the value for
                    that key in the sizes map is extracted and used to calculate the PageRank using the formula below.
                    It multiplies 1/(outgoing edges) by the corresponding position in the vector, and if there is more
                    than one value for a key in the toFrom map, it is iterated through again and adds to the total
                    PageRank. */

                    for (auto &i : it->second) {

                        rank += (1.0 / (sizes.find(i.first)->second)) * vec[distance(sizes.begin(), sizes.find(i.first))];

                    }

                    // The PageRank is then inserted into the new vector at the corresponding position

                    newVec.at(j) = rank;
                    rank = 0.0;
                    j++;

                }

                // The values in newVec are copied into vec to be used again depending on the number of power iterations

                vec = newVec;

            }

        }

    }

    /* The print function then iterates through the sizes map, prints out the url, then prints out the value in newVec
    at the same corresponding position. */

    void print() {

        int i = 0;
        map<string, int> :: iterator it;

        for (it = sizes.begin(); it != sizes.end(); ++it) {

            cout << it -> first << " " << std::fixed << std::setprecision(2) << newVec[i];
            i++;
            cout << endl;

        }

    }

};

int main() {

    /* In main, the number of lines and power iterations are read in, followed by the urls. Then, using an adjacency
    list object, four methods are called to insert the urls into a adjacency list. Then the other methods are used to
    calculate the individual PageRank's for each url. */

    AdjacencyList adj;
    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations;

    for (int i = 0; i < no_of_lines; i++) {

        cin >> from;
        cin >> to;

        adj.insert(from, to);

    }

    adj.vertSize();
    adj.calcRank(power_iterations);
    adj.print();

    return 0;

}
