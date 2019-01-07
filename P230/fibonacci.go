/*
Instead of computing fibonacci of strings, we construct fibonacci with digits and then use 
this information to solve the problem using fib(n-1) + fib(n-2) logic

@Author: Rohith Uppala
*/


package main

import (
    "fmt"
)

func getFibonacciNumbers() []uint64 {
    var fibonacci = make([]uint64, 0)
    fibonacci = append(fibonacci, 0)
    fibonacci = append(fibonacci, 100)
    var i = 2
    for fibonacci[i - 1] < (1 << 63) {
        fibonacci = append(fibonacci, fibonacci[i - 1] + fibonacci[i - 2])
        i = i + 1
    }
    return fibonacci
}

func getRightIndex(fibonacci []uint64, A string, B string, index uint64) int {
    var current = 1
    for index >= fibonacci[current] { current = current + 1 }
    for true {
        if current == 1 { return int(A[index]) - '0' }
        if current == 2 { return int(B[index]) - '0' }
        var mid = fibonacci[current - 2]
        if index < mid {
            current = current - 2
        } else {
            index = index - mid
            current = current - 1
        }
    }
    return 0
}

func power(a int, b int) uint64 {
    var result uint64 = 1
    for n := 1; n <= b; n++ { result = result * uint64(a) }
    return result
}

func main() {
    var A = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
    var B = "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"

    var fibonacci = getFibonacciNumbers()
    fmt.Println(fibonacci)
    var value uint64 = 0

    for n := 17; n >= 0; n-- {
        var index uint64 = (127 + 19 * uint64(n))
        for seven := 1; seven <= n; seven++ {
            index = index * 7
        }
        index = index - 1
        var current = getRightIndex(fibonacci, A, B, index)
        value = value + (power(10, n) * uint64(current))
    }

    fmt.Printf("result for problem 230: %v\n", value)
}
