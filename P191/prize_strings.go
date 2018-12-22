/*
This will work for n <= 10 because of edge conditions. We need to have a different approach
@Author: Rohith Uppala
*/

package main

import (
    "fmt"
    "math/big"
)

func get_number_of_consecutive_absents(n int) *big.Int {
    result := big.NewInt(0)
    for l:= 3; l <= n; l++ {
        value := power(2, n - l)
        result = Add(result, Mul(big.NewInt(int64(n - l + 1)), value))
    }
    return result
}

func get_number_of_more_than_two_late_occasions(n int) *big.Int {
    result := big.NewInt(0)
    for k := 2; k <= n; k++ {
        val := ncr(n, k)
        result = Add(result, Mul(val, power(2, n - k)))
    }
    return result
}

func ncr(n, k int) *big.Int {
    n_fact := factorial(n)
    nminusk_fact := factorial(n - k)
    k_fact := factorial(k)
    return Div(n_fact, Mul(nminusk_fact, k_fact))
}

func Add(x, y *big.Int) *big.Int {
    return new(big.Int).Add(x, y)
}

func Mul(x, y *big.Int) *big.Int {
    return big.NewInt(1).Mul(x, y)
}

func Div(x, y *big.Int) *big.Int {
    return new(big.Int).Quo(x, y)
}

func Sub(x, y *big.Int) *big.Int {
    return new(big.Int).Sub(x, y)
}

func power(x, y int) *big.Int {
    return new(big.Int).Exp(big.NewInt(int64(x)), big.NewInt(int64(y)), nil)
}

func factorial(n int) *big.Int {
    result := big.NewInt(1)
    for counter := 2 ; counter <= n; counter++ {
        result = Mul(result, big.NewInt(int64(counter)))
    }
    return result
}

func main() {
    num_positions := 4
    first_result := get_number_of_consecutive_absents(num_positions)
    second_result := get_number_of_more_than_two_late_occasions(num_positions)
    result := Sub(power(3, num_positions), Add(first_result, second_result))
    fmt.Printf("Result: %v\n", result)
}
