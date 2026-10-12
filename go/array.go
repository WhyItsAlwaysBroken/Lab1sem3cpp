package main

import "fmt"

type MyArray struct {
	data     []string
	capacity int
}

func NewMyArray(capacity int) *MyArray {
	return &MyArray{data: make([]string, 0, capacity), capacity: capacity}
}

func (a *MyArray) Insert(index int, elem string) {
	if index < 0 || index > len(a.data) {
		fmt.Println("Out of range")
		return
	}
	if len(a.data) >= a.capacity {
		fmt.Println("Overflow")
		return
	}
	a.data = append(a.data, "")
	copy(a.data[index+1:], a.data[index:])
	a.data[index] = elem
}

func (a *MyArray) PushBack(elem string) {
	if len(a.data) >= a.capacity {
		fmt.Println("Overflow")
		return
	}
	a.data = append(a.data, elem)
}

func (a *MyArray) Get(index int) string {
	if index < 0 || index >= len(a.data) {
		fmt.Println("Out of range")
		return ""
	}
	return a.data[index]
}

func (a *MyArray) PopIndex(index int) string {
	if index < 0 || index >= len(a.data) {
		fmt.Println("Out of range")
		return ""
	}
	removed := a.data[index]
	a.data = append(a.data[:index], a.data[index+1:]...)
	return removed
}

func (a *MyArray) Set(index int, elem string) string {
	if index < 0 || index >= len(a.data) {
		fmt.Println("Out of range")
		return ""
	}
	a.data[index] = elem
	return elem
}

func (a *MyArray) Length() int { return len(a.data) }

func (a *MyArray) ToSlice() []string { return append([]string(nil), a.data...) }
