/*
Find prime squbes using Miller - Rabin Primality test
@Author: Rohith Uppala
*/

#include <iostream>
#include <stdio.h>
#include <set>
#include <vector>
#include <boost/multiprecision/cpp_int.hpp> 
#include <boost/lexical_cast.hpp>
#include "../misc/utils.hpp"

using namespace boost::multiprecision; 
using namespace std;

struct sqube {
    unsigned int p;
    unsigned int q;
    int128_t value;

    sqube(unsigned int p_, unsigned int q_): 
        p(p_), q(q_), value((int128_t)p_ * p_ * q_ * q_ * q_)
    {}

    bool operator<(const sqube& other) const {
        return value < other.value;
    }
};

int128_t boost_product(unsigned long long int A, unsigned long long int B) { 
    int128_t ans = A * B; 
    return ans; 
}

vector<int> generate_primes(int n) {
    vector<bool> prime(n+1, true);
    for(int p=2; p*p <= n; p++) {
        if(prime[p] == true) {
            for(int i=p*p; i<=n; i+=p) {
                prime[i] = false;
            }
        }
    }
    vector<int> prime_numbers;
    for(int p=2; p<=n; p++) {
        if(prime[p]) prime_numbers.push_back(p);
        if(prime_numbers.size() == 1000) return prime_numbers;
    }
    return prime_numbers;
}

vector<int128_t> generate_prime_sqube(vector<int> primes) {
    vector<int128_t> prime_squbes;
    for(int i = 0; i < primes.size(); i++) {
        for(int j = 0; j < primes.size(); j++) {
            if(primes[i] != primes[j]) {
                unsigned long long int p = primes[i] * primes[i];
                unsigned long long int q = primes[j] * primes[j] * primes[j];
                int128_t sqube = boost_product(p, q);
                prime_squbes.push_back(sqube);
            }
        }
    }
    return prime_squbes;
}

bool is_sqube_prime_proof(string sqube) {
    vector<char> numbers = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for(int index = 0; index < sqube.length(); index++) {
        for(int j=0; j<numbers.size(); j++) {
            string new_sqube = "";
            for(int k=0; k<index; k++) 
                new_sqube += sqube[k];
            new_sqube += numbers[j];
            for(int k=index+1; k<sqube.length(); k++) 
                new_sqube += sqube[k];
            int128_t num_sqube = 0;
            for(int k=0; k<new_sqube.length(); k++) {
                num_sqube = (num_sqube * 10) + (int)(new_sqube[k] - '0');
            }
            if(is_prime(num_sqube, 4)) return false;
        }
    }
    return true;
}

int main() {
    set<sqube> squbes = { sqube(3, 2), sqube(2, 3) };
    int cnt = 1;
    while(true) {
        auto current = *(squbes.begin());
        squbes.erase(squbes.begin());
        int128_t num = current.value;
        string num_string = boost::lexical_cast<string>(num);
        if(num_string.find("200") != std::string::npos) {
            if(is_sqube_prime_proof(num_string)) {
                cnt += 1;
                cout << cnt << ") " << num_string << endl;
                if(cnt == 200) break;
            }
        }
        auto next_p = current.p + 1;
        while(next_p == current.q || !is_prime((int128_t)next_p, 4)) next_p += 1;
        squbes.insert(sqube(next_p, current.q));
        auto next_q = current.q + 1;
        while(next_q == current.p || !is_prime((int128_t)next_q, 4)) next_q += 1;
        squbes.insert(sqube(current.p, next_q));
    }
    return 0;
}
