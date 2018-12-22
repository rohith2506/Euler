/*
Dynamic Programming Problem
f(days) = f(#no late or no absent) + f(#only absent) + f(#only late)

@Author: Rohith Uppala
*/


package main

import (
    "fmt"
)

func solve(days int, absent int, late int) int {
    if absent == 3 { return 0 }
    if late > 1 { return 0 }
    if days == 0 { return 1 }
    var result int
    result = solve(days - 1, 0, late)
    result += solve(days - 1, absent + 1, late)
    result += solve(days - 1, 0, late + 1)
    return result
}

func main() {
    days := 30
    result := solve(days, 0, 0)
    fmt.Printf("result: %v\n", result)
}
