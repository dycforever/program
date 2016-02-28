package main

import (
	"fmt"
	"reflect"
)

type User struct {
	Name string `field:"username" type:"nvarchar(20)"`
	Age  int    `field:"age" type:"tinyint"`
}
type Admin struct {
	User
	title string
}

func (*User) ToString() { fmt.Println("calling User.ToString()") }
func (Admin) test()     { fmt.Println("calling Admin.test()") }

func showMetheds(t reflect.Type) {
	for i, n := 0, t.NumMethod(); i < n; i++ {
		m := t.Method(i)
		fmt.Println(m.Name)
	}
}

func main() {
	{
		up := new(Admin)
		t := reflect.TypeOf(up)

		if t.Kind() == reflect.Ptr {
			t = t.Elem()
		}
		for i, n := 0, t.NumField(); i < n; i++ {
			f := t.Field(i)
			fmt.Println(f.Name, f.Type)
		}

		var a Admin
		fmt.Println("--- value interface ---")
		showMetheds(reflect.TypeOf(a))
		fmt.Println("--- pointer interface ---")
		showMetheds(reflect.TypeOf(&a))
	}

	fmt.Println("===================")

	{
		var u User
		u.ToString()
		t := reflect.TypeOf(u)
		f, _ := t.FieldByName("Name")
		fmt.Println(f.Tag)
		fmt.Println(f.Tag.Get("field"))
		fmt.Println(f.Tag.Get("type"))
	}

	fmt.Println("===================")

	var (
		Int    = reflect.TypeOf(0)
		String = reflect.TypeOf("")
	)

	{
		c := reflect.ChanOf(reflect.SendDir, String)
		fmt.Println(c)
		m := reflect.MapOf(String, Int)
		fmt.Println(m)
		s := reflect.SliceOf(Int)
		fmt.Println(s)
		t := struct{ Name string }{}
		p := reflect.PtrTo(reflect.TypeOf(t))
		fmt.Println(p)

		tt := reflect.TypeOf(make(chan int)).Elem()
		fmt.Println(tt)
	}

	fmt.Println("===================")

	{
		var u User
		t := reflect.TypeOf(u)
		// 没法直接获取接口类型，好在接口本身是个 struct，创建
		// 一个空指针对象，这样传递给 TypeOf 转换成 interface{}
		// 时就有类型信息了。。
		it := reflect.TypeOf((*fmt.Stringer)(nil)).Elem()
		// 为啥不是 t.Implements(fmt.Stringer)，完全可以由编译器⽣成。
		fmt.Println(t.Implements(it))

		fmt.Println(t.Size(), t.Align())
		f, _ := t.FieldByName("Age")
		fmt.Println(f.Type.FieldAlign())
	}
}
