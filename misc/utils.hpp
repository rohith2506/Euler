#include <vector>

using namespace std;

template <class T>
void print_vector(vector<T> output) {
    cout << "Printing 1d vector.....\n";
    for(auto element: output) {
        cout << element << "\t";
    }
    cout << endl;
}

template <class T>
void print_2d_vector(vector<vector<T> > output) {
    cout << "printing 2d vector.....";
    for(int i = 0; i < output.size(); i++) {
        for(int j = 0; j < output[i].size(); j++) {
            cout << output[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

