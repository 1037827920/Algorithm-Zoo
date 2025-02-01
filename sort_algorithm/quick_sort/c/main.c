#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

int partition(int* arr, int left, int right) {
    // 确定基准元素
    int pivot = arr[right];
    // 小于基准的元素的索引
    int i = left;

    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    // 将基准元素放到正确的位置
    swap(&arr[i], &arr[right]);
    // 返回基准元素的索引
    return i;
}

void quick_sort(int* arr, int left, int right) {
    if (left < right) {
        int pivot_index = partition(arr, left, right);
        quick_sort(arr, left, pivot_index - 1);
        quick_sort(arr, pivot_index + 1, right);
    }
}

int main() {
    int* arr = (int*)malloc(6 * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    arr[0] = 10;
    arr[1] = 7;
    arr[2] = 8;
    arr[3] = 9;
    arr[4] = 1;
    arr[5] = 5;

    quick_sort(arr, 0, 5);

    for (int i = 0; i < 6; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}