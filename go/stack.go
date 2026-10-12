package main

import "fmt"

// Stack — стек фиксированной ёмкости.
type Stack struct {
	data     []string
	capacity int
}

func NewStack(capacity int) *Stack {
	return &Stack{data: make([]string, 0, capacity), capacity: capacity}
}

func (s *Stack) Push(elem string) {
	if len(s.data) == s.capacity {
		fmt.Println("Stack Overflow")
		return
	}
	s.data = append(s.data, elem)
}

func (s *Stack) Pop() string {
	if len(s.data) == 0 {
		fmt.Println("Stack Underflow")
		return ""
	}
	v := s.data[len(s.data)-1]
	s.data = s.data[:len(s.data)-1]
	return v
}

func (s *Stack) Top() string {
	if len(s.data) == 0 {
		fmt.Println("Stack Underflow")
		return ""
	}
	return s.data[len(s.data)-1]
}

// Print печатает элементы от вершины к основанию, по одному в строке.
func (s *Stack) Print() {
	if len(s.data) == 0 {
		fmt.Println("Stack Underflow")
	}
	for i := len(s.data) - 1; i >= 0; i-- {
		fmt.Println(s.data[i])
	}
}

func (s *Stack) IsEmpty() bool { return len(s.data) == 0 }

func (s *Stack) ToSlice() []string { return append([]string(nil), s.data...) }
