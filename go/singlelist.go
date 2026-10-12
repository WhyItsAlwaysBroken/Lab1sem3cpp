package main

import "fmt"

type Node struct {
	data string
	next *Node
}

// SingleList — односвязный список (хранит только голову).
type SingleList struct {
	head *Node
}

func (l *SingleList) PushFront(data string) {
	l.head = &Node{data: data, next: l.head}
}

func (l *SingleList) PushBack(data string) {
	n := &Node{data: data}
	if l.head == nil {
		l.head = n
		return
	}
	cur := l.head
	for cur.next != nil {
		cur = cur.next
	}
	cur.next = n
}

func (l *SingleList) InsertBefore(target, data string) {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	if l.head.data == target {
		l.PushFront(data)
		return
	}
	cur := l.head
	for cur.next != nil && cur.next.data != target {
		cur = cur.next
	}
	if cur.next == nil {
		fmt.Printf("There is no %d value\n", target)
		return
	}
	cur.next = &Node{data: data, next: cur.next}
}

func (l *SingleList) InsertAfter(target, data string) {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	cur := l.head
	for cur != nil && cur.data != target {
		cur = cur.next
	}
	if cur == nil {
		fmt.Printf("There is no %d value\n", target)
		return
	}
	cur.next = &Node{data: data, next: cur.next}
}

func (l *SingleList) PrintIter() {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	for cur := l.head; cur != nil; cur = cur.next {
		fmt.Printf("%d ", cur.data)
	}
	fmt.Println()
}

func printRecur(n *Node) {
	if n == nil {
		return
	}
	printRecur(n.next)
	fmt.Printf("%d ", n.data)
}

func (l *SingleList) PrintRecur() {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	printRecur(l.head)
	fmt.Println()
}

func (l *SingleList) RemoveValue(target string) {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	if l.head.data == target {
		l.head = l.head.next
		return
	}
	cur := l.head
	for cur.next != nil && cur.next.data != target {
		cur = cur.next
	}
	if cur.next == nil {
		fmt.Printf("There is no %d value\n", target)
		return
	}
	cur.next = cur.next.next
}

func (l *SingleList) RemoveFront() {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	l.head = l.head.next
}

func (l *SingleList) RemoveBack() {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	if l.head.next == nil {
		l.head = nil
		return
	}
	cur := l.head
	for cur.next.next != nil {
		cur = cur.next
	}
	cur.next = nil
}

func (l *SingleList) RemoveBefore(target string) {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	if l.head.data == target {
		fmt.Printf("There is no element before %d\n", target)
		return
	}
	var prev *Node
	cur := l.head
	for cur.next != nil && cur.next.data != target {
		prev = cur
		cur = cur.next
	}
	if cur.next == nil {
		fmt.Printf("There is no %d value\n", target)
		return
	}
	// cur — узел прямо перед target
	if prev == nil {
		l.head = cur.next
	} else {
		prev.next = cur.next
	}
}

func (l *SingleList) RemoveAfter(target string) {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	cur := l.head
	for cur != nil && cur.data != target {
		cur = cur.next
	}
	if cur == nil {
		fmt.Printf("There is no %d value\n", target)
		return
	}
	if cur.next == nil {
		fmt.Printf("There is no element after %d\n", target)
		return
	}
	cur.next = cur.next.next
}

func (l *SingleList) Search(target string) bool {
	for cur := l.head; cur != nil; cur = cur.next {
		if cur.data == target {
			return true
		}
	}
	return false
}

func (l *SingleList) ToSlice() []string {
	v := []string{}
	for cur := l.head; cur != nil; cur = cur.next {
		v = append(v, cur.data)
	}
	return v
}
