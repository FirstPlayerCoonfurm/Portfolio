package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	var number1, number2 int
	fmt.Scan(&number1)
	fmt.Scan(&number2)

	number1Str := strconv.Itoa(number1)
	number2Str := strconv.Itoa(number2)

	commonDigits := []string{}
	for _, digit := range number1Str {

		if strings.Contains(number2Str, string(digit)) {
			commonDigits = append(commonDigits, string(digit))
		}
	}

	fmt.Println(strings.Join(commonDigits, " "))
}