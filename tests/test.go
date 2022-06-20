package main

var a int
var b float64

func bar(str string) (int, string) {
	return 5, "kek"
}

func foo(a int) (int, string) {
	a = 5
	b := "aa"
	c, d := bar(b)
	for a := 0; a < 5; a++ {
		if a == 3 {
			return c, d
		} else {
			continue
		}
	}
	return c, d
}

func main() {
	a = 10
	b := "str"
	var c []int
	if a < 5 {
		return
	}
	foo(a)
}
