package main
import "fmt"

func main() {
    var tests, digits int
    fmt.Scan(&tests)
    for test := 0; test < tests; test++ {
        fmt.Scan(&digits)
        threes, fives := 0, 0
        for fives_try := 0; fives_try <= digits; fives_try++ {
            threes_try := digits - fives_try
            if threes_try % 5 == 0 && fives_try % 3 == 0 {
                threes, fives = threes_try, fives_try
            }
        }
        if threes == 0 && fives == 0 {
            fmt.Println(-1)
        } else {
            for f := 0; f < fives; f++ {
                fmt.Print(5)
            }
            for t := 0; t < threes; t++ {
                fmt.Print(3)
            }
            fmt.Println()
        }
    }
}
