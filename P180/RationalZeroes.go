package main;

import (
    "fmt"
    "math/big"
    "encoding/json"
    "math"
)

func all_possible_values(order int) []*big.Rat {
    values := make([]*big.Rat, 0, 1500)
    for a := 1; a <= order; a++ {
        for b := a+1; b <= order; b++ {
            values = append(values, big.NewRat(int64(a), int64(b)))
        }
    }
    return values
}

func power(a *big.Rat, exponent int) *big.Rat {
    result := big.NewRat(1, 1)
    if exponent < 0 {
        inverse := big.NewRat(1, 1)
        inverse.Inv(a)
        a = inverse
        exponent = int(math.Abs(float64(exponent)))
    }
    for i := 1; i <= exponent; i++ {
        result.Mul(result, a)
    }
    return result
}

func solve(order, n int) *big.Rat {
    result := make([]*big.Rat, 0, 2000)
    seen := make(map[string]bool)

    all_possible_x, all_possible_y, all_possible_z := all_possible_values(order), all_possible_values(order), all_possible_values(order)

    for i := -2; i <= n; i++ {
        if i == 0 { continue }
        x_and_y := make(map[string]*big.Rat)
        for _, x := range all_possible_x {
            for _, y := range all_possible_y {
                xn, yn := power(x, i), power(y, i)
                xn_and_yn := xn.Add(xn, yn)
                out, err := json.Marshal(xn_and_yn)
                if err != nil { panic(err) }
                result := big.NewRat(0, 1)
                result.Add(result, x)
                result.Add(result, y)
                x_and_y[string(out)] = result
            }
        }

        for _, z := range all_possible_z {
            zn := power(z, i)
            out2, err2 := json.Marshal(zn)
            if err2 != nil { panic(err2) }
            val, ok := x_and_y[string(out2)]
            if ok {
                t := big.NewRat(0, 1)
                t.Add(t, val)
                t.Add(t, z)
                out3, err3 := json.Marshal(t)
                if err3 != nil { panic(err3) }
                _, ok2 := seen[string(out3)]
                if !ok2 {
                    result = append(result, t)
                    seen[string(out3)] = true
                }
            }
        }
    }

    final_value := big.NewRat(0, 1)
    for _, n := range result {
        final_value.Add(final_value, n)
    }
    return final_value
}

func main() {
    order, n := 35, 2
    result := solve(order, n)
    fmt.Printf("Result: %v", result)
}
