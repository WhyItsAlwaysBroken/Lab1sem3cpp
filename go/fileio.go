package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

const CAP = 100 // ёмкость массива, стека и очереди

// FileInOut хранит все именованные структуры и умеет читать/писать файл данных.
type FileInOut struct {
	arrays map[string]*MyArray
	stacks map[string]*Stack
	queues map[string]*Queue
	flists map[string]*SingleList
	llists map[string]*DoubleList
}

func NewFileInOut() *FileInOut {
	return &FileInOut{
		arrays: map[string]*MyArray{},
		stacks: map[string]*Stack{},
		queues: map[string]*Queue{},
		flists: map[string]*SingleList{},
		llists: map[string]*DoubleList{},
	}
}

// Как и в оригинале, обращение к имени создаёт пустую структуру.
func (f *FileInOut) arr(n string) *MyArray {
	if f.arrays[n] == nil {
		f.arrays[n] = NewMyArray(CAP)
	}
	return f.arrays[n]
}
func (f *FileInOut) stk(n string) *Stack {
	if f.stacks[n] == nil {
		f.stacks[n] = NewStack(CAP)
	}
	return f.stacks[n]
}
func (f *FileInOut) que(n string) *Queue {
	if f.queues[n] == nil {
		f.queues[n] = NewQueue(CAP)
	}
	return f.queues[n]
}
func (f *FileInOut) fl(n string) *SingleList {
	if f.flists[n] == nil {
		f.flists[n] = &SingleList{}
	}
	return f.flists[n]
}
func (f *FileInOut) dl(n string) *DoubleList {
	if f.llists[n] == nil {
		f.llists[n] = &DoubleList{}
	}
	return f.llists[n]
}

func parseInt(s string) (string, bool) {
	v, err := strconv.ParseInt(s, 10, 32)
	return string(v), err == nil
}

func (f *FileInOut) Load(path string) {
	file, err := os.Open(path)
	if err != nil {
		return // файла нет
	}
	defer file.Close()
	sc := bufio.NewScanner(file)
	sc.Buffer(make([]byte, 1<<20), 1<<26)
	for sc.Scan() {
		fields := strings.Fields(sc.Text())
		if len(fields) < 2 {
			continue
		}
		typ, name := fields[0], fields[1]
		switch typ {
		case "M":
			f.arr(name)
		case "S":
			f.stk(name)
		case "Q":
			f.que(name)
		case "F":
			f.fl(name)
		case "L":
			f.dl(name)
		default:
			continue // неизвестный тип (например, "T" — деревья не поддерживаются)
		}
		for _, tok := range fields[2:] {
			v, ok := parseInt(tok)
			if !ok {
				break
			}
			switch typ {
			case "M":
				f.arr(name).PushBack(v)
			case "S":
				f.stk(name).Push(v)
			case "Q":
				f.que(name).Push(v)
			case "F":
				f.fl(name).PushBack(v)
			case "L":
				f.dl(name).PushBack(v)
			}
		}
	}
}

func writeLine(w *bufio.Writer, typ, name string, v []string) {
	w.WriteString(typ + " " + name)
	for _, x := range v {
		w.WriteString(" " + x)
	}
	w.WriteString("\n")
}

func sortedKeys[V any](m map[string]V) []string {
	keys := make([]string, 0, len(m))
	for k := range m {
		keys = append(keys, k)
	}
	sort.Strings(keys)
	return keys
}

func (f *FileInOut) Save(path string) {
	file, err := os.Create(path)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Cannot write file", path)
		return
	}
	defer file.Close()
	w := bufio.NewWriter(file)
	defer w.Flush()
	for _, k := range sortedKeys(f.arrays) {
		writeLine(w, "M", k, f.arrays[k].ToSlice())
	}
	for _, k := range sortedKeys(f.stacks) {
		writeLine(w, "S", k, f.stacks[k].ToSlice())
	}
	for _, k := range sortedKeys(f.queues) {
		writeLine(w, "Q", k, f.queues[k].ToSlice())
	}
	for _, k := range sortedKeys(f.flists) {
		writeLine(w, "F", k, f.flists[k].ToSlice())
	}
	for _, k := range sortedKeys(f.llists) {
		writeLine(w, "L", k, f.llists[k].ToSlice())
	}
}

// Execute выполняет запрос вида "CMD name [args]". Возвращает код выхода.
func (f *FileInOut) Execute(query string) int {
	fields := strings.Fields(query)
	if len(fields) < 2 {
		fmt.Fprintln(os.Stderr, "Query format CMD name [args]")
		return 1
	}
	cmd, name := fields[0], fields[1]
	args := fields[2:]

	known := map[string]bool{
		"MPUSH": true, "MINS": true, "MGET": true, "MDEL": true, "MSET": true, "MLEN": true,
		"FPUSH": true, "FPUSHFRONT": true, "FINSBEFORE": true, "FINSAFTER": true, "FDEL": true,
		"FDELFRONT": true, "FDELBACK": true, "FDELBEFORE": true, "FDELAFTER": true,
		"FFIND": true, "FGET": true, "FGETREC": true,
		"LPUSH": true, "LPUSHFRONT": true, "LINSBEFORE": true, "LINSAFTER": true, "LDEL": true,
		"LDELFRONT": true, "LDELBACK": true, "LDELBEFORE": true, "LDELAFTER": true,
		"LFIND": true, "LGET": true, "LGETBACK": true,
		"QPUSH": true, "QGET": true, "QPOP": true, "QFRONT": true, "QREAR": true,
		"SPUSH": true, "SGET": true, "SPOP": true, "STOP": true, "PRINT": true,
	}
	if !known[cmd] {
		fmt.Fprintln(os.Stderr, "Unknown command:", cmd)
		return 1
	}

	// need читает n целочисленных аргументов; при ошибке печатает сообщение.
	need := func(n int) ([]string, bool) {
		out := make([]string, n)
		for i := 0; i < n; i++ {
			if i >= len(args) {
				fmt.Fprintln(os.Stderr, "Missing or invalid argument")
				return nil, false
			}
			v, ok := parseInt(args[i])
			if !ok {
				fmt.Fprintln(os.Stderr, "Missing or invalid argument")
				return nil, false
			}
			out[i] = v
		}
		return out, true
	}
	// Количество аргументов по команде.
	nargs := map[string]int{
		"MPUSH": 1, "MINS": 2, "MGET": 1, "MDEL": 1, "MSET": 2,
		"FPUSH": 1, "FPUSHFRONT": 1, "FINSBEFORE": 2, "FINSAFTER": 2, "FDEL": 1,
		"FDELBEFORE": 1, "FDELAFTER": 1, "FFIND": 1,
		"LPUSH": 1, "LPUSHFRONT": 1, "LINSBEFORE": 2, "LINSAFTER": 2, "LDEL": 1,
		"LDELBEFORE": 1, "LDELAFTER": 1, "LFIND": 1,
		"QPUSH": 1, "SPUSH": 1,
	}
	a, ok := need(nargs[cmd])
	if !ok {
		return 1
	}
	truefalse := func(b bool) {
		if b {
			fmt.Println("TRUE")
		} else {
			fmt.Println("FALSE")
		}
	}

	switch cmd {
	// Array (M)
	case "MPUSH":
		f.arr(name).PushBack(a[0])
	case "MINS":
		idx, err := strconv.Atoi(a[0])
		if err != nil {
		}
		f.arr(name).Insert(idx, a[1])
	case "MGET":
		idx, err := strconv.Atoi(a[0])
		if err != nil {
		}
		m := f.arr(name)
		if idx < 0 || idx >= m.Length() {
			fmt.Println("Out of range")
		} else {
			fmt.Println(m.Get(idx))
		}
	case "MDEL":
		idx, err := strconv.Atoi(a[0])
		if err != nil {
		}
		m := f.arr(name)
		if idx < 0 || idx >= m.Length() {
			fmt.Println("Out of range")
		} else {
			fmt.Println(m.PopIndex(idx))
		}
	case "MSET":
		idx, err := strconv.Atoi(a[0])
		if err != nil {
		}
		f.arr(name).Set(idx, a[1])
	case "MLEN":
		fmt.Println(f.arr(name).Length())

	// Single linked list (F)
	case "FPUSH":
		f.fl(name).PushBack(a[0])
	case "FPUSHFRONT":
		f.fl(name).PushFront(a[0])
	case "FINSBEFORE":
		f.fl(name).InsertBefore(a[0], a[1])
	case "FINSAFTER":
		f.fl(name).InsertAfter(a[0], a[1])
	case "FDEL":
		f.fl(name).RemoveValue(a[0])
	case "FDELFRONT":
		f.fl(name).RemoveFront()
	case "FDELBACK":
		f.fl(name).RemoveBack()
	case "FDELBEFORE":
		f.fl(name).RemoveBefore(a[0])
	case "FDELAFTER":
		f.fl(name).RemoveAfter(a[0])
	case "FFIND":
		truefalse(f.fl(name).Search(a[0]))
	case "FGET":
		f.fl(name).PrintIter()
	case "FGETREC":
		f.fl(name).PrintRecur()

	// Double linked list (L)
	case "LPUSH":
		f.dl(name).PushBack(a[0])
	case "LPUSHFRONT":
		f.dl(name).PushFront(a[0])
	case "LINSBEFORE":
		f.dl(name).InsertBefore(a[0], a[1])
	case "LINSAFTER":
		f.dl(name).InsertAfter(a[0], a[1])
	case "LDEL":
		f.dl(name).RemoveValue(a[0])
	case "LDELFRONT":
		f.dl(name).RemoveFront()
	case "LDELBACK":
		f.dl(name).RemoveBack()
	case "LDELBEFORE":
		f.dl(name).RemoveBefore(a[0])
	case "LDELAFTER":
		f.dl(name).RemoveAfter(a[0])
	case "LFIND":
		truefalse(f.dl(name).Search(a[0]))
	case "LGET":
		f.dl(name).PrintIter()
	case "LGETBACK":
		f.dl(name).PrintBack()

	// Queue (Q)
	case "QPUSH":
		f.que(name).Push(a[0])
	case "QGET":
		if q := f.que(name); q.IsEmpty() {
			fmt.Println("Empty")
		} else {
			q.Print()
		}
	case "QPOP":
		if q := f.que(name); q.IsEmpty() {
			fmt.Println("Underflow")
		} else {
			fmt.Println(q.Pop())
		}
	case "QFRONT":
		if q := f.que(name); q.IsEmpty() {
			fmt.Println("Empty")
		} else {
			fmt.Println(q.FrontElem())
		}
	case "QREAR":
		if q := f.que(name); q.IsEmpty() {
			fmt.Println("Empty")
		} else {
			fmt.Println(q.RearElem())
		}

	// Stack (S)
	case "SPUSH":
		f.stk(name).Push(a[0])
	case "SGET":
		if s := f.stk(name); s.IsEmpty() {
			fmt.Println("Empty")
		} else {
			s.Print()
		}
	case "SPOP":
		if s := f.stk(name); s.IsEmpty() {
			fmt.Println("Underflow")
		} else {
			fmt.Println(s.Pop())
		}
	case "STOP":
		if s := f.stk(name); s.IsEmpty() {
			fmt.Println("Empty")
		} else {
			fmt.Println(s.Top())
		}

	// Any structure
	case "PRINT":
		switch {
		case f.arrays[name] != nil:
			for _, x := range f.arrays[name].ToSlice() {
				fmt.Printf("%d ", x)
			}
			fmt.Println()
		case f.stacks[name] != nil:
			f.stacks[name].Print()
		case f.queues[name] != nil:
			f.queues[name].Print()
		case f.flists[name] != nil:
			f.flists[name].PrintIter()
		case f.llists[name] != nil:
			f.llists[name].PrintIter()
		default:
			fmt.Println("Structure not found")
			return 1
		}
	}
	return 0
}
