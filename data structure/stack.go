package main

import (
	"bufio"
	"fmt"
	"os"
)

const MAXSIZE = 20

type Stack struct {
	Data [MAXSIZE]int
	Top  int
}

func (s *Stack) Init() {
	s.Top = -1
}

func (s *Stack) Push(d int) bool {
	if s.Top+1 > MAXSIZE {
		return false
	}
	s.Data[s.Top+1] = d
	s.Top++
	return true
}
func (s *Stack) Pop() int {
	if s.Top == -1 {
		return 0
	}
	d := s.Data[s.Top]
	s.Data[s.Top] = 0
	s.Top--
	return d
}
func (s *Stack) Peek() int {
	if s.Top == -1 {
		fmt.Println("栈是空的")
		panic(0)
	}
	return s.Data[s.Top]
}
func (s *Stack) Change(str string, b []int) {
	var ss Stack
	leng := len(str)
	ss.Push('@')
	i, j := 0, 0
	ch := str[i]
	for i < leng {
		switch ch {
		case ' ':
			i++
			ch = str[i]
		case '(':
			ss.Push(int(ch))
			i++
			ch = str[i]
		case ')':
			for ss.Peek() != '(' {
				b[j] = ss.Pop()
				j++
			}
			ss.Pop()
			i++
			ch = str[i]
		case '+', '-', '*', '/':
			w := ss.Peek()
			for Precedence(w) >= Precedence(int(ch)) {
				b[j] = w
				j++
				ss.Pop()
				w = ss.Peek()
			}
			ss.Push(int(ch))
			i++
			ch = str[i]
		default:
			if (ch < '0' || ch > '9') && ch != '.' {
				fmt.Println("中缀表达式表达错误!")
				panic(0)
			}
			for (ch >= '0' && ch <= '9') || ch == '.' {
				b[j] = int(ch)
				j++
				i++
				if i == leng {
					break
				}
				ch = str[i]
			}
			b[j] = ' '
			j++
		}
	}
	ch = byte(ss.Pop())
	for ch != '@' {
		if ch == '(' {
			fmt.Println("表达错误")
			panic(0)
		} else {
			b[j] = int(ch)
			j++
			ch = byte(ss.Pop())
		}
	}
}
func Precedence(op int) int {
	switch op {
	case '+', '-':
		return 1
	case '*', '/':
		return 2
	default:
		return 0
	}
}
func main() {
	var s Stack
	b := make([]int, 50)
	s.Init()
	reader := bufio.NewReader(os.Stdin)
	str, _, _ := reader.ReadLine()
	a := string(str)
	fmt.Println("中缀表达式:", a)
	s.Change(a, b)
	for _, v := range b {
		fmt.Printf("%d %c", v, v)
	}
}
