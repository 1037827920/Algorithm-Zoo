
function quickSort(arr) {
    if (arr.length <= 1) {
        return arr;
    }

    // 选择基准值
    const pivot = arr[arr.length - 1];
    const left = [];
    const right = [];
    const equal = [];

    // 遍历数组
    for (let num of arr) {
        if (num < pivot) {
            left.push(num);
        } else if (num > pivot) {
            right.push(num);
        } else {
            equal.push(num);
        }
    }

    // 对left和right进行递归排序
    return [...quickSort(left), ...equal, ...quickSort(right)];
}

const arr = [10, 7, 8, 9, 1, 5];
console.log(quickSort(arr));