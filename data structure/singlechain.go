package main

import (
	"fmt"
)

type Node struct {
	Data int
	Next *Node
}

func LinkList() *Node {
	var length int
	fmt.Scanln(&length)
	var h Node
	h.Next = nil
	for i := 0; i < length; i++ {
		var temp Node
		fmt.Scanf("%d", &temp.Data)
		temp.Next = h.Next
		h.Next = &temp
	}
	return &h
}
func PrintList(h *Node) {
	p := h.Next
	for p != nil {
		fmt.Printf("%d ", p.Data)
		p = p.Next
	}
	fmt.Println()
}
func Inverse(h *Node) {
	var p Node
	p = *(h.Next)
	//fmt.Println(p)
	h.Next = nil
	for p.Next != nil {
		s := p
		p = *(p.Next)
		//fmt.Println(s, p)
		s.Next = h.Next
		h.Next = &s
	}
	s := p
	s.Next = h.Next
	h.Next = &s
}
func Delete(h *Node) {
	//var temp Node
	//temp = *h
	temp := h
	c := 0
	for temp.Next != nil {
		if c == 0 {
			c = 1
			temp = temp.Next
			continue
		}
		temp.Next = temp.Next.Next
		c = 0
	}
}
func Insert(h *Node, a Node) {
	temp := h
	c := 0
	if temp.Next == nil {
		temp.Next = &a
		c = 1
	}
	for temp.Next != nil {
		t := temp
		temp = temp.Next
		if temp.Data > a.Data {
			t.Next = &a
			a.Next = temp
			c = 1
			break
		}
	}
	if c == 0 {
		temp.Next = &a
	}
}
func Merge(h *Node, t *Node) *Node {
	p := t.Next
	for p.Next != nil {
		Insert(h, *p)
		p = p.Next
	}
	return h
}
func main() {
	fmt.Println("请先输入要建立的链表的长度")
	first := LinkList()
	fmt.Println("遍历链表")
	PrintList(first)
	fmt.Println("逆置链表")
	Inverse(first)
	PrintList(first)
	fmt.Println("删除偶数节点元素")
	Delete(first)
	PrintList(first)
	fmt.Println("先输入要建立的有序链表长度，在输入要插入的值")
	var leng int
	fmt.Scanln(&leng)
	var List Node
	for i := 0; i < leng; i++ {
		var t Node
		fmt.Scanf("%d", &t.Data)
		t.Next = nil
		Insert(&List, t)
	}
	fmt.Println("建立的有序表为:")
	PrintList(&List)
	fmt.Println("建立链表一:")
	var leng1 int
	fmt.Scanln(&leng1)
	var List1 Node
	for i := 0; i < leng1; i++ {
		var t Node
		fmt.Scanf("%d", &t.Data)
		t.Next = nil
		Insert(&List1, t)
	}
	fmt.Println("建立的有序表一为:")
	PrintList(&List1)
	fmt.Println("建立链表二:")
	var leng2 int
	fmt.Scanln(&leng2)
	var List2 Node
	for i := 0; i < leng2; i++ {
		var t Node
		fmt.Scanf("%d", &t.Data)
		t.Next = nil
		Insert(&List2, t)
	}
	fmt.Println("建立的有序表二为:")
	PrintList(&List2)
	fmt.Println("表一与表二合并为：")
	h := Merge(&List1, &List2)
	//fmt.Println(h)
	PrintList(h)

}
