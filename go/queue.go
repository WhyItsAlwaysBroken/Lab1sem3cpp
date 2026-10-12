package main

import "fmt"

// Queue — линейная очередь фиксированной ёмкости (как в оригинале:
// место освободившееся после pop не переиспользуется).
type Queue struct {
	arr         []string
	capacity    int
	front, rear int
}

func NewQueue(capacity int) *Queue {
	return &Queue{arr: make([]string, capacity), capacity: capacity, front: -1, rear: -1}
}

func (q *Queue) Push(elem string) {
	if q.rear == q.capacity-1 {
		fmt.Println("Overflow")
		return
	}
	if q.front == -1 {
		q.front, q.rear = 0, 0
	} else {
		q.rear++
	}
	q.arr[q.rear] = elem
}

func (q *Queue) Pop() string {
	if q.front == -1 {
		fmt.Println("Underflow")
		return ""
	}
	tmp := q.arr[q.front]
	if q.front == q.rear {
		q.front, q.rear = -1, -1
	} else {
		q.front++
	}
	return tmp
}

func (q *Queue) FrontElem() string {
	if q.front == -1 {
		fmt.Println("queue is Empty")
		return ""
	}
	return q.arr[q.front]
}

func (q *Queue) RearElem() string {
	if q.front == -1 {
		fmt.Println("queue is Empty")
		return ""
	}
	return q.arr[q.rear]
}

func (q *Queue) IsEmpty() bool { return q.front == -1 }

func (q *Queue) Print() {
	if q.front > q.rear || q.front == -1 {
		fmt.Println("Queue is empty")
		return
	}
	for i := q.front; i <= q.rear; i++ {
		fmt.Printf("%d ", q.arr[i])
	}
	fmt.Println()
}

func (q *Queue) ToSlice() []string {
	if q.front == -1 {
		return []string{}
	}
	return append([]string(nil), q.arr[q.front:q.rear+1]...)
}
