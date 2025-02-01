#include <iostream>
#include <vector>
#include <cmath>
#include <concepts>

using std::vector;
using std::swap;
using std::cout;
using std::endl;
using std::totally_ordered;

// 快速排序的分区函数
template<totally_ordered T>
int partition(vector<T>& arr, size_t left, size_t right) {
    // 选择最右边的元素作为基准
    T pivot = arr[right];
    // 小于基准的元素的索引
    size_t i = left;

    // 遍历数组
    // 将小于基准的元素放到左边
    // 将大于基准的元素放到右边
    for (size_t j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            ++i;
        }
    }

    // 将基准元素放到正确的位置
    swap(arr[i], arr[right]);
    // 返回基准元素的索引
    return i;
}

template<totally_ordered T>
void quick_sort(vector<T>& arr, size_t left, size_t right) {
    if (left < right) {
        // 分区操作
        size_t pivot_index = partition<T>(arr, left, right);

        // 对两边进行递归
        quick_sort(arr, left, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, right);
    }
}

int main() {
    vector<int> arr = { 10, 7, 8, 9, 1, 5 };

    quick_sort<int>(arr, 0, arr.size() - 1);

    for (const auto& num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}