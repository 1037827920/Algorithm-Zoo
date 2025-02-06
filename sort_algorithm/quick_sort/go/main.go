package main

import (
	"fmt"

	"golang.org/x/exp/constraints"
)

// 快速排序的分区函数
func partition[T constraints.Ordered](arr []T, left, right int) int {
	// 选择最右边的元素作为基准
	pivot := arr[right]
	// 小于基准的元素的索引
	i := left

	// 遍历数组
	// 将小于基准的元素放到左边
	// 大于基准的元素放到右边
	for j := left; j < right; j++ {
		if arr[j] < pivot {
			arr[i], arr[j] = arr[j], arr[i]
			i++
		}
	}

	// 将基准元素放到正确的位置
	arr[i], arr[right] = arr[right], arr[i]
	// 返回基准元素的索引
	return i
}

// 快速排序
func quickSort[T constraints.Ordered](arr []T, left, right int) {
	if left < right {
		// 分区
		pivotIndex := partition(arr, left, right)

		// 对两边执行递归
		quickSort(arr, left, pivotIndex-1)
		quickSort(arr, pivotIndex+1, right)
	}
}

func main() {
	arr := []int{10, 7, 8, 9, 1, 5}
	quickSort(arr, 0, len(arr)-1)
	fmt.Println(arr)
}