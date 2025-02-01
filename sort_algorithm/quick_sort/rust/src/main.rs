use std::vec::Vec;

// 快速排序的分区函数
fn partition<T: PartialOrd + Copy>(arr: &mut Vec<T>, left: usize, right: usize) -> usize {
    // 选择最右边的元素作为基准
    let pivot = arr[right as usize];
    // 小于基准的元素的索引
    let mut i = left;

    // 遍历数组
    // 将小于基准的元素放到左边
    // 将大于基准的元素放到右边
    for j in left..right {
        if arr[j] < pivot {
            arr.swap(i, j);
            i += 1;
        }
    }

    // 将基准元素放到正确的位置
    arr.swap(i, right);
    // 返回基准元素的索引
    i
}

// 快排函数
fn quick_sort<T: PartialOrd + Copy>(arr: &mut Vec<T>, left: usize, right: usize) {
    if left < right {
        // 分区操作
        let pivot_index = partition(arr, left, right);
        // 对两边执行递归
        quick_sort(arr, left, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, right);
    }
}

fn main() {
    let mut arr = vec![10, 7, 8, 9, 1, 5];
    let len = arr.len();

    quick_sort(&mut arr, 0, len - 1);

    arr.iter().for_each(|x| print!("{x} "));
    println!();
}