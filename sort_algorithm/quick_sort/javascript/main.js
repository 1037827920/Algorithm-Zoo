

// 快速排序的分区函数
function partition(arr, left, right) {
    // 选择最右边的元素作为基准
    let pivot = arr[right];
    // 小于基准的元素的索引
    let i = left;

    // 遍历数组
    // 将小于基准的元素放到左边
    // 将大于基准的元素放到右边
    for (let j = left; j < right; j++) {
        if (arr[j] < pivot) {
            [arr[i], arr[j]] = [arr[j], arr[i]];
            i++;
        }
    }

    // 将基准元素放到正确的位置
    [arr[i], arr[right]] = [arr[right], arr[i]];
    return i;
}

// 快速排序
function quickSort(arr, left, right) {
    if (left < right) {
        // 分区操作
        let pivotIndex = partition(arr, left, right);

        // 对两边进行递归
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }
}

// 测试
let arr = [ 10, 7, 8, 9, 1, 5 ];
quickSort(arr, 0, arr.length - 1);
console.log(arr);