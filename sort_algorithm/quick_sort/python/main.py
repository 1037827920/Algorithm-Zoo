# 快速排序的分区函数
def partition(arr, left, right):
    # 选择最右边的元素作为基准
    pivot = arr[right]
    # 小于基准的元素的索引
    i = left

    # 遍历数组
    # 将小于基准的元素放到左边
    # 将大于基准的元素放到右边
    for j in range(left, right):
        if arr[j] < pivot:
            arr[i], arr[j] = arr[j], arr[i]
            i += 1

    # 将基准元素放到正确的位置
    arr[i], arr[right] = arr[right], arr[i]
    # 返回基准元素的索引
    return i


# 递归函数
def quick_sort(arr, left, right):
    if left < right:
        # 分区操作
        pivot_index = partition(arr, left, right)
        # 对两边进行递归
        quick_sort(arr, left, pivot_index - 1)
        quick_sort(arr, pivot_index + 1, right)


def main():
    arr = [10, 7, 8, 9, 1, 5]

    quick_sort(arr, 0, len(arr) - 1)

    for num in arr:
        print(num, end=' ')
    print()

if __name__ == '__main__':
    main()
