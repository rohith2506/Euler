/*
This is a classic example of polynomial interpolation using lagrange technique
@Author: Rohith Uppala
*/

#include <iostream>
#include <vector>
#include <cmath>
#include "../misc/utils.hpp"
#define ll long long int

const int MAX_POLYNOMIAL_INDEX = 4;

using namespace std;

ll func(int n) {
    ll value = 0;
    for(int i = 0; i <= 10; i++) {
        if(i % 2 == 1) value -= pow(n, i);
        else value += pow(n, i);
    }
    return value;
}

ll sample_func(int n) { return n * n * n; }


vector<pair<int, ll> > get_sub_polynomial(vector<pair<int, ll> > original_function, int i) {
    vector<pair<int, ll> > result;
    for(int j = 0; j < i; j++) result.push_back(original_function[j]);
    return result;
}

ll get_next_pair_value(vector<pair<int, ll> > sub_polynomial, int xi) {
    double result = 0;
    for(int i = 0; i < sub_polynomial.size(); i++) {
        double term = (double)(sub_polynomial[i].second);
        for(int j = 0; j < sub_polynomial.size(); j++) {
            if(j != i) term = term * (xi - sub_polynomial[j].first) / double(sub_polynomial[i].first - sub_polynomial[j].first);
        }
        result += term;
    }
    return (ll)(result);
}

ll solve() {
    vector<pair<int, ll> > original_function;
    for(int i = 1; i <= 20; i++) {
        original_function.push_back(make_pair(i, func(i)));
    }

    ll result = 1;
    for(int i = 1; i <= 10; i++) {
        vector<pair<int, ll> > sub_polynomial = get_sub_polynomial(original_function, i); 
        for(int j = i+1; j <= 12; j++) {
            ll next_pair_value = get_next_pair_value(sub_polynomial, j);
            if(original_function[j].second != next_pair_value) {
                result += next_pair_value;
                break;
            }
        }
    }

    return result;
}
       
int main() {
    ll fit_result = solve();
    cout << "FIT for BOP: " << fit_result << endl;
    return 0;
}
