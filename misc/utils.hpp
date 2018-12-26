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

// Primality testing using miller-rabin
template <class T>
T power(T x, T y, T p) {
    T res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1) res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}

template <class T>
bool miller_test(T d, T n) {
    T a = 2 + rand() % (n - 4);
    T x = power(a, d, n);
    if (x == 1  || x == n-1) return true;
    while (d != n-1) {
        x = (x * x) % n;
        d *= 2;
        if (x == 1) return false;
        if (x == n-1) return true;
    }
    return false;
}

template <class T>
bool is_prime(T n, int k) {              
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
    T d = n - 1;
    while (d % 2 == 0) 
        d /= 2;
    for (int i = 0; i < k; i++)
        if (!miller_test(d, n))
            return false;
    return true;
}
