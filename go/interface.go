package main

import (
	"fmt"
	"reflect"
	"unsafe"
)

func PrintInfo(v interface{}) {
	fmt.Printf("%T: %v\n", v, v)
}

type Tester struct {
	s interface {
		String() string
	}
}
type User struct {
	id   int
	name string
}

func (self *User) String() string {
	return fmt.Sprintf("user %d, %s", self.id, self.name)
}
func main() {
	// print interface's info
	PrintInfo(1)
	PrintInfo("hello")

	t := Tester{&User{1, "Tom"}}
	fmt.Println(t.s.String())

	fmt.Println("========== 1 =========")

	// 接口的数据指针是只读的
	u := User{1, "Tom"}
	var vi, pi interface{} = u, &u
	// vi.(User).name = "Jack" // Error: cannot assign to vi.(User).name
	pi.(*User).name = "Jack"
	fmt.Printf("%v\n", vi.(User))
	fmt.Printf("%v\n", pi.(*User))

	fmt.Println("========== 2 =========")

	// 接口本质上就是两个指针，分别是类型指针和数据指针
	var a interface{} = nil         // tab = nil, data = nil
	var b interface{} = (*int)(nil) // tab 包含 *int 类型信息, data = nil
	type iface struct {
		itab, data uintptr
	}
	ia := *(*iface)(unsafe.Pointer(&a))
	ib := *(*iface)(unsafe.Pointer(&b))
	fmt.Println(a == nil, ia)
	fmt.Println(b == nil, ib, reflect.ValueOf(b).IsNil())

	fmt.Println("========== 3 =========")

	// 判断对象是否实现了某一接口
	var o interface{} = &User{1, "Tom"}
	if i, ok := o.(fmt.Stringer); ok { // ok-idiom
		fmt.Println(i)
	}
	ou := o.(*User)
	// ou := o.(User) // panic: interface is *main.User, not main.User
	fmt.Println(ou)
}
