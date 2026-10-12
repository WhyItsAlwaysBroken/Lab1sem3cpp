package main

import (
	"fmt"
	"os"
)

func main() {
	var file, query string
	args := os.Args[1:]
	for i := 0; i < len(args); i++ {
		switch {
		case args[i] == "--file" && i+1 < len(args):
			i++
			file = args[i]
		case args[i] == "--query" && i+1 < len(args):
			i++
			query = args[i]
		}
	}
	if file == "" || query == "" {
		fmt.Fprintln(os.Stderr, "Usage: ./ds --file file.data --query 'COMAND name [args]'")
		os.Exit(1)
	}
	fio := NewFileInOut()
	fio.Load(file)
	rc := fio.Execute(query)
	if rc == 0 {
		fio.Save(file)
	}
	os.Exit(rc)
}
