package main

import (
	"fmt"
)

func main() {
	a := [5]int{1, 2, 3, 4, 5}
	for i, v := range a { // index、 value 都是从复制品中取出。
		if i == 0 { // 在修改前，我们先修改原数组。
			//			a = a[:3]
			a[2] = 100
		}
		a[i] = v + 100 // 使⽤复制品中取出的 value 修改原数组。
		fmt.Print(i, "->", v, " ")
	}
	fmt.Println("\n", a)

	s := []int{1, 2, 3, 4, 5}
	for i, v := range s { // 复制 struct slice { pointer, len, cap }。
		if i == 0 {
			//			s = s[:3]  // 对 slice 的修改，不会影响 range。
			s[2] = 100 // 对底层数据的修改。
		}
		s[i] = v + 100 // 使⽤复制品中取出的 value 修改原数组。
		fmt.Print(i, "->", v, " ")
	}
	fmt.Println("\n", s)
}
