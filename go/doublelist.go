package main

import "fmt"

type dbNode struct {
	data        string
	left, right *dbNode
}

type DoubleList struct {
	head *dbNode
}

func (l *DoubleList) PushFront(data string) {
	n := &dbNode{data: data, right: l.head}
	if l.head != nil {
		l.head.left = n
	}
	l.head = n
}

func (l *DoubleList) PushBack(data string) {
	n := &dbNode{data: data}
	if l.head == nil {
		l.head = n
		return
	}
	cur := l.head
	for cur.right != nil {
		cur = cur.right
	}
	cur.right = n
	n.left = cur
}

func (l *DoubleList) find(target string) *dbNode {
	cur := l.head
	for cur != nil && cur.data != target {
		cur = cur.right
	}
	return cur
}

func (l *DoubleList) InsertBefore(target, data string) {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	if l.head.data == target {
		l.PushFront(data)
		return
	}
	cur := l.find(target)
	if cur == nil {
		fmt.Printf("There is no %d value\n", target)
		return
	}
	n := &dbNode{data: data, right: cur, left: cur.left}
	cur.left.right = n
	cur.left = n
}

func (l *DoubleList) InsertAfter(target, data string) {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	cur := l.find(target)
	if cur == nil {
		fmt.Printf("There is no %d value\n", target)
		return
	}
	if cur.right == nil {
		l.PushBack(data)
		return
	}
	n := &dbNode{data: data, right: cur.right, left: cur}
	cur.right.left = n
	cur.right = n
}

func (l *DoubleList) PrintIter() {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	for cur := l.head; cur != nil; cur = cur.right {
		fmt.Printf("%d ", cur.data)
	}
	fmt.Println()
}

func (l *DoubleList) PrintBack() {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	cur := l.head
	for cur.right != nil {
		cur = cur.right
	}
	for ; cur != nil; cur = cur.left {
		fmt.Printf("%d ", cur.data)
	}
	fmt.Println()
}

func (l *DoubleList) RemoveValue(target string) {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	if l.head.data == target {
		l.head = l.head.right
		if l.head != nil {
			l.head.left = nil
		}
		return
	}
	cur := l.find(target)
	if cur == nil {
		fmt.Printf("There is no %d value\n", target)
		return
	}
	cur.left.right = cur.right
	if cur.right != nil {
		cur.right.left = cur.left
	}
}

func (l *DoubleList) RemoveFront() {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	l.head = l.head.right
	if l.head != nil {
		l.head.left = nil
	}
}

func (l *DoubleList) RemoveBack() {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	cur := l.head
	for cur.right != nil {
		cur = cur.right
	}
	if cur.left == nil {
		l.head = nil
	} else {
		cur.left.right = nil
	}
}

func (l *DoubleList) RemoveBefore(target string) {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	cur := l.find(target)
	if cur == nil {
		fmt.Printf("There is no %d value\n", target)
		return
	}
	if cur.left == nil {
		fmt.Printf("There is no element before %d\n", target)
		return
	}
	tmp := cur.left
	if tmp.left != nil {
		tmp.left.right = cur
	} else {
		l.head = cur
	}
	cur.left = tmp.left
}

func (l *DoubleList) RemoveAfter(target string) {
	if l.head == nil {
		fmt.Println("Underflow")
		return
	}
	cur := l.find(target)
	if cur == nil {
		fmt.Printf("There is no %d value\n", target)
		return
	}
	if cur.right == nil {
		fmt.Printf("There is no element after %d\n", target)
		return
	}
	tmp := cur.right
	cur.right = tmp.right
	if tmp.right != nil {
		tmp.right.left = cur
	}
}

func (l *DoubleList) Search(target string) bool { return l.find(target) != nil }

func (l *DoubleList) ToSlice() []string {
	v := []string{}
	for cur := l.head; cur != nil; cur = cur.right {
		v = append(v, cur.data)
	}
	return v
}
