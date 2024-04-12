# Sorting Algorithms

## Bubble Sort

Bubble sort is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order. The pass through the list is repeated until the list is sorted.

```C
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
```

## Selection Sort

Selection sort is a simple sorting algorithm that repeatedly selects the minimum element from the unsorted portion of the array and places it at the beginning of the unsorted portion.

```C
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}
```

## Insertion Sort

Insertion sort is a simple sorting algorithm that builds the final sorted array one item at a time. It iterates through the list and removes one element at a time, finds the location it belongs to in the sorted list and inserts it there.

```C
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}
```

## Stalin sort
Works by iterating through the array and removing any elements that are out of order, thus 'executing' them. This algorithm is highly inefficient and destructive, and it is totally suitable for any practical use.

```C
void stalinSort(int arr[], int *n) {
    int j = 0;
    for (int i = 1; i < *n; i++) {
        if (arr[j] <= arr[i]) {
            arr[++j] = arr[i];
        }
    }
    *n = j + 1;
}
```


## Bogo Sort

Bogo Sort is a highly ~~in~~efficient and ~~im~~practical sorting algorithm. It works by randomly shuffling the array repeatedly until it happens to be sorted. The time complexity of Bogo Sort is ~~un~~bounded, making it ~~un~~suitable for any practical use.

```c

bool isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

void shuffle(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void bogoSort(int arr[], int n) {
    srand(time(NULL));
    while (!isSorted(arr, n)) {
        shuffle(arr, n);
    }
}
```

## Merge Sort

Merge sort is a divide and conquer algorithm that divides the input array into two halves, calls itself for the two halves and then merges the two sorted halves.

```C
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[l + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[m + 1 + i];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
```


## Quantum sort 
Quantum Sort explores applying quantum computing principles to sorting. Leveraging quantum mechanics phenomena like superposition and entanglement, it aims to process multiple elements simultaneously, potentially leading to faster sorting of large datasets compared to classical algorithms. 
```C
\\ quantum code beyond undestanding of humanity 
```

## Miracle sort 
Miracle Sort whimsically imagines a sorting algorithm effortlessly arranging elements in perfect order without computational effort. 
```C
\\ Wait for the code to MIRACLOUSLY appear !!
```

## Quick Sort

Quick sort is a divide and conquer algorithm that picks an element as pivot and partitions the given array around the picked pivot.

```C
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return i+1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}
```

## Heap Sort

Heap sort is a comparison-based sorting algorithm that uses a binary heap data structure. It divides its input into a sorted and an unsorted region, and it iteratively shrinks the unsorted region by extracting the largest element and moving that to the sorted region.

Below is the implementation of heap sort using a max heap.

```C
typedef struct {
    int *arr;
    int size;
} Heap;

void heapify(Heap *heap, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < heap->size && heap->arr[left] > heap->arr[largest]) {
        largest = left;
    }

    if (right < heap->size && heap->arr[right] > heap->arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[largest];
        heap->arr[largest] = temp;
        heapify(heap, largest);
    }
}

void insert(Heap *heap, int key) {
    heap->size++;
    int i = heap->size - 1;
    heap->arr[i] = key;

    while (i != 0 && heap->arr[(i-1)/2] < heap->arr[i]) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[(i-1)/2];
        heap->arr[(i-1)/2] = temp;
        i = (i-1)/2;
    }
}

int extractMax(Heap *heap) {
    if (heap->size <= 0) {
        return -1;
    }

    if (heap->size == 1) {
        heap->size--;
        return heap->arr[0];
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size-1];
    heap->size--;
    heapify(heap, 0);

    return root;
}

void heapSort(int arr[], int n) {
    Heap heap;
    heap.arr = arr;
    heap.size = n;

    for (int i = n/2 - 1; i >= 0; i--) {
        heapify(&heap, i);
    }

    for (int i = n-1; i >= 0; i--) {
        int temp = heap.arr[0];
        heap.arr[0] = heap.arr[i];
        heap.arr[i] = temp;
        heap.size--;
        heapify(&heap, 0);
    }
}
```

## Counting Sort

Counting sort is an integer sorting algorithm that operates by counting the number of occurrences of each element in the input array and using arithmetic to determine the position of each element in the output array.

```C
void countingSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int count[max+1];
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        count[i] += count[i-1];
    }

    int output[n];
    for (int i = n-1; i >= 0; i--) {
        output[count[arr[i]]-1] = arr[i];
        count[arr[i]]--;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}
```

## Bucket Sort

Bucket sort is a sorting algorithm that distributes elements of an array into a number of buckets. Each bucket is then sorted individually, either using a different sorting algorithm, or by recursively applying the bucket sorting algorithm.

```C
void bucketSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int bucket[max+1];
    for (int i = 0; i <= max; i++) {
        bucket[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        bucket[arr[i]]++;
    }

    for (int i = 0, j = 0; i <= max; i++) {
        while (bucket[i] > 0) {
            arr[j++] = i;
            bucket[i]--;
        }
    }
}
```

# What is Quick Select?

Quick select is a selection algorithm to find the k-th smallest element in an unordered list. It is related to the quick sort sorting algorithm.

```C
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return i+1;
}

int quickSelect(int arr[], int low, int high, int k) {
    if (low < high) {
        int pi = partition(arr, low, high);
        if (pi == k) {
            return arr[pi];
        } else if (pi < k) {
            return quickSelect(arr, pi+1, high, k);
        } else {
            return quickSelect(arr, low, pi-1, k);
        }
    }
    return arr[low];
}
```

### How this `quickSelect` function works?

1. It takes an array `arr[]`, a range defined by `low` and `high` and the value of `k` to find the k-th smallest element.
2. It partitions the array around a pivot element such that all elements on the left of the pivot are smaller and all elements on the right are greater.
3. If the pivot element is at the k-th position, it returns the element at that position.
4. If the pivot element is less than k, it recursively calls itself for the right sub-array.
5. If the pivot element is greater than k, it recursively calls itself for the left sub-array.
6. It returns the element at the k-th position.
7. If the range is reduced to a single element, it returns that element.
8. If the range is reduced to an empty array, it returns the first element of the array.

# Problem of `count_inversions`

Given an array of integers, find the number of inversions in the array. Two elements `arr[i]` and `arr[j]` form an inversion if `arr[i] > arr[j]` and `i < j`.

```C
int merge(int arr[], int temp[], int low, int mid, int high) {
    int i = low, j = mid, k = low;
    int inv_count = 0;

    while ((i <= mid - 1) && (j <= high)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i);
        }
    }

    while (i <= mid - 1) {
        temp[k++] = arr[i++];
    }

    while (j <= high) {
        temp[k++] = arr[j++];
    }

    for (i = low; i <= high; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

int mergeSort(int arr[], int temp[], int low, int high) {
    int inv_count = 0;
    if (low < high) {
        int mid = low + (high - low) / 2;
        inv_count += mergeSort(arr, temp, low, mid);
        inv_count += mergeSort(arr, temp, mid + 1, high);
        inv_count += merge(arr, temp, low, mid + 1, high);
    }
    return inv_count;
}

int countInversions(int arr[], int n) {
    int temp[n];
    return mergeSort(arr, temp, 0, n-1);
}
```

### How this `countInversions` function works?

1. It takes an array `arr[]` and its size `n`.
2. It creates a temporary array `temp[]` of the same size.
3. It calls the `mergeSort` function with the array, temporary array, low index `0` and high index `n-1`.
4. The `mergeSort` function recursively divides the array into two halves and calls itself for the two halves.
5. The `merge` function merges the two halves and counts the number of inversions.
6. It counts inversions by comparing the elements of the two halves. If an element in the left half is greater than an element in the right half, it increments the inversion count by the number of elements remaining in the left half.
7. It returns the total number of inversions in the array.

# Complexity Analysis (Space and Time)

| Algorithm      | Best Time Complexity | Average Time Complexity | Worst Time Complexity | Worst Space Complexity | Stable |
|----------------|----------------------|-------------------------|-----------------------|------------------------|--------|
| Bubble Sort    | O(n)                 | O(n^2)                  | O(n^2)                | O(1)                   | Yes    |
| Selection Sort | O(n^2)               | O(n^2)                  | O(n^2)                | O(1)                   | No     |
| Insertion Sort | O(n)                 | O(n^2)                  | O(n^2)                | O(1)                   | Yes    |
| Merge Sort     | O(n log n)           | O(n log n)              | O(n log n)            | O(n)                   | Yes    |
| Quick Sort     | O(n log n)           | O(n log n)              | O(n^2)                | O(log n)               | No     |
| Heap Sort      | O(n log n)           | O(n log n)              | O(n log n)            | O(1)                   | No     |
| Counting Sort  | O(n + k)             | O(n + k)                | O(n + k)              | O(n + k)               | Yes    |
| Bucket Sort    | O(n + k)             | O(n + k)                | O(n^2)                | O(n)                   | Yes    |


Here, `n` is the number of elements in the array and `k` is the range of input.

# Applications

- **Bubble Sort**: Used in computer graphics to detect overlapping objects.
- **Selection Sort**: Used in the real world where the cost of swapping elements is very high.
- **Insertion Sort**: Used in online algorithms where the list is continuously updated.
- **Merge Sort**: Used in external sorting where data doesn't fit into memory.
- **Quick Sort**: Used in internal sorting where data fits into memory.
- **Heap Sort**: Used in priority queues.
- **Counting Sort**: Used in counting the frequency of letters in a text.
- **Bucket Sort**: Used in distributed systems.
- **Quick Select**: Used in finding the k-th smallest element in an array.

## Why can't we use `Counting Sort` or `Bucket Sort` always?

- **Counting Sort**: It is efficient when the range of input is not significantly greater than the number of elements in the array. It can't be used if the range is very large. This is because it will create an array of that size which is not feasible.

- **Bucket Sort**: It is efficient when the input is uniformly distributed over a range. It can't be used if the input is skewed. This is because it will create empty buckets which is not efficient.

# GeeksForGeeks links

- [Bubble Sort](https://www.geeksforgeeks.org/bubble-sort/)
- [Selection Sort](https://www.geeksforgeeks.org/selection-sort/)
- [Insertion Sort](https://www.geeksforgeeks.org/insertion-sort/)
- [Merge Sort](https://www.geeksforgeeks.org/merge-sort/)
- [Quick Sort](https://www.geeksforgeeks.org/quick-sort/)
- [Heap Sort](https://www.geeksforgeeks.org/heap-sort/)
- [Counting Sort](https://www.geeksforgeeks.org/counting-sort/)
- [Bucket Sort](https://www.geeksforgeeks.org/bucket-sort/)
- [Quick Select](https://www.geeksforgeeks.org/quickselect-algorithm/)
- [Count Inversions](https://www.geeksforgeeks.org/counting-inversions/)