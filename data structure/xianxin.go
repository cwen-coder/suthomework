package main

import (
	"fmt"
)

const MAXSIZE = 20

type List struct {
	Element [MAXSIZE]int
	length  int
}

func (l *List) InitList() {
	fmt.Scanln(&l.length)
	for i := 0; i < l.length; i++ {
		fmt.Scanf("%d", &l.Element[i])
	}
}
func (l *List) Delete(p int) bool {
	if p < 0 || p > l.length || p > MAXSIZE {
		return false
	}
	for ; p < l.length; p-- {
		l.Element[p] = l.Element[p-1]
	}
	l.Element[l.length-1] = 0
	l.length--
	return true
}
func (l *List) SeqList() {
	for i := 0; i < l.length; i++ {
		fmt.Printf("%d ", l.Element[i])
	}
	fmt.Println()
}
func (l *List) Search() int {
	var d int
	fmt.Println("输入你要查找的数：")
	fmt.Scanf("%d", &d)
	for i := 0; i < l.length; i++ {
		if d == l.Element[i] {
			return 1
		}
	}
	return 0
}
func (l *List) Symmetric() int {
	temp := 0
	for i, j := 0, l.length-1; i < j; {
		if l.Element[i] != l.Element[j] {
			temp = 1
			break
		}
		i++
		j--
	}
	if temp == 1 {
		return 0
	} else {
		return 1
	}
}
func (l *List) OddEven() {
	var a, b []int
	for i := 0; i < l.length; i++ {
		if l.Element[i]%2 == 0 {
			a = append(a, l.Element[i])
		} else {
			b = append(b, l.Element[i])
		}
	}
	for i := 0; i < l.length; i++ {
		if i < len(b) {
			l.Element[i] = b[i]
		} else {
			l.Element[i] = a[i-len(b)]
		}
	}
	l.SeqList()
}
func (l *List) InsertList() []int {
	var arr []int
	//arr := make([]int, 0, 20)
	var leng, temp int
	fmt.Scanln(&leng)
	for i := 0; i < leng; i++ {
		fmt.Scanf("%d", &temp)
		if i == 0 {
			arr = append(arr, temp)
		} else {
			c := i - 1
			arr = append(arr, 0)
			for ; c >= 0 && temp < arr[c]; c-- {
				arr[c+1] = arr[c]
			}
			if c != i-1 {
				arr[c+1] = temp
			} else {
				arr[i] = temp
			}
		}
	}
	return arr
}
func (l *List) Merge(arr1 []int, arr2 []int) []int {
	for _, value := range arr2 {
		c := len(arr1) - 1
		temp := c
		arr1 = append(arr1, 0)
		for ; c >= 0 && value < arr1[c]; c-- {
			arr1[c+1] = arr1[c]
		}
		if c != temp {
			arr1[c+1] = value
		} else {
			arr1[temp+1] = value
		}
	}
	return arr1
}
func main() {
	var l List
	l.InitList()
	fmt.Println("顺序表遍历：")
	l.SeqList()
	search := l.Search()
	if search == 1 {
		fmt.Println("返回值为1，查找成功")
	} else {
		fmt.Println("返回值为0，查找的数不存在")
	}
	fmt.Println("判断顺序表是否对称：")
	symmetric := l.Symmetric()
	if symmetric == 1 {
		fmt.Println("返回值为1，顺序表对称")
	} else {
		fmt.Println("返回值为0，顺序表不对称")
	}
	fmt.Println("未奇偶排序前的线性表")
	l.SeqList()
	fmt.Println("奇偶排序后的线性表")
	l.OddEven()
	fmt.Println("请先输入要建立有序表的长度：")
	arr := l.InsertList()
	fmt.Println(arr)
	fmt.Println("建立两个非递减有序表并把它们合并成一个非递减有序表")
	fmt.Println("建立有序表1")
	arr1 := l.InsertList()
	fmt.Println(arr1)
	fmt.Println("建立有序表2")
	arr2 := l.InsertList()
	fmt.Println(arr2)
	fmt.Println("表1与表2合并后：")
	arr3 := l.Merge(arr1, arr2)
	fmt.Println(arr3)

}
