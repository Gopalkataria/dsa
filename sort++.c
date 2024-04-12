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

## Merge Sort

Merge sort is a divide and conquer algorithm that divides the input array into two halves, calls itself for the two halves and then merges the two sorted halves.

```C
void merge(int arr[], int l, int m, int r){
    int ptr1 = l, ptr2 = m+1, ptr3 = 0;
    int temp[r-l+1];
    while(ptr1 <= m && ptr2 <= r){
        if(arr[ptr1] < arr[ptr2]){
            temp[ptr3++] = arr[ptr1++];
        }else{
            temp[ptr3++] = arr[ptr2++];
        }
    }
    while(ptr1 <= m){
        temp[ptr3++] = arr[ptr1++];
    }
    while(ptr2 <= r){
        temp[ptr3++] = arr[ptr2++];
    }
    for(int i = l; i <= r; i++){
        arr[i] = temp[i-l];
    } 
}

void mergeSort(int arr[], int l, int r){
    if(l < r){
        int m = l + (r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}
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
## Shell Sort

Shell sort is a generalization of insertion sort that allows the exchange of items that are far apart. The idea is to arrange the list of elements so that, starting anywhere, taking every hth element produces a sorted list.

```C
void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
                arr[j] = arr[j-gap];
            }
            arr[j] = temp;
        }
    }
}
```

### How this works?

1. The array is divided into subarrays of equal size.
2. The subarrays are sorted using the insertion sort algorithm.
3. The subarrays are merged to produce new subarrays that are twice as large.
4. Steps 2 and 3 are repeated until the entire array is sorted.
5. The last step is to sort the entire array using the insertion sort algorithm.
6. The array is now sorted.


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
void merge(int arr[], int l, int m, int r, int *ans){
    int ptr1 = l, ptr2 = m+1, ptr3 = 0;
    int temp[r-l+1];
    while(ptr1 <= m && ptr2 <= r){
        if(arr[ptr1] <= arr[ptr2]){
            temp[ptr3++] = arr[ptr1++];
        }else{
            *ans += m - ptr1 + 1;
            temp[ptr3++] = arr[ptr2++];
        }
    }
    while(ptr1 <= m){
        temp[ptr3++] = arr[ptr1++];
    }
    while(ptr2 <= r){
        temp[ptr3++] = arr[ptr2++];
    }
    for(int i = l; i <= r; i++){
        arr[i] = temp[i-l];
    } 
}

void mergeSort(int arr[], int l, int r, int *ans){
    if(l < r){
        int m = l + (r-l)/2;
        mergeSort(arr, l, m, ans);
        mergeSort(arr, m+1, r, ans);
        merge(arr, l, m, r, ans);
    }
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
| Shell Sort     | O(n log n)         | O(n log n)            | O(n^2)          | O(1)                   | No     |

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
- **Shell Sort**: Used in real-time systems where the input size is small.

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
- [Shell Sort](https://www.geeksforgeeks.org/shellsort/)

# Mathematical Proofs (Time Complexities)

## Bubble Sort

- **Best Case**: O(n)
- **Average Case**: O(n^2)
- **Worst Case**: O(n^2)

### Proof

Say the outer loop variable is `i`. `i` ranges from `0` to `n-1`. The inner loop variable is `j`. `j` ranges from `i+1` to `n-1`.

Comparison is done for each consecutive pair of elements. Therefore,

```C
Comparisons in ith loop = t(i) = n - i - 1
```
Furthur, the total number of comparisons is:

```C
T(n) = t(0) + t(1) + t(2) + ... + t(n-1)
     = (n-1) + (n-2) + (n-3) + ... + 1 + 0
     = n(n-1)/2
     = O(n^2)
```

## Selection Sort

- **Best Case**: O(n^2)
- **Average Case**: O(n^2)
- **Worst Case**: O(n^2)

### Proof

Say the outer loop variable is `i`. `i` ranges from `0` to `n-1`. The inner loop variable is `j`. `j` ranges from `i+1` to `n-1`.

In each iteration, the minimum element is found and swapped with the element at `i`. Therefore,

```C
Comparisons in ith loop = t(i) = n - i - 1
```

Furthur, the total number of comparisons is:

```C
T(n) = t(0) + t(1) + t(2) + ... + t(n-1)
     = (n-1) + (n-2) + (n-3) + ... + 1 + 0
     = n(n-1)/2
     = O(n^2)
```

## Insertion Sort

- **Best Case**: O(n)
- **Average Case**: O(n^2)
- **Worst Case**: O(n^2)

### Proof

Say the outer loop variable is `i`. `i` ranges from `1` to `n-1`. The inner loop variable is `j`. `j` ranges from `i-1` to `0`.

In each iteration, the element at `i` is inserted at the correct position in the sorted subarray. Therefore,

```C
Comparisons in ith loop = t(i) = i
```

Furthur, the total number of comparisons is:

```C
T(n) = t(1) + t(2) + t(3) + ... + t(n-1)
     = 1 + 2 + 3 + ... + n-1
     = n(n-1)/2
     = O(n^2)
```

## Merge Sort

- **Best Case**: O(n log n)
- **Average Case**: O(n log n)
- **Worst Case**: O(n log n)

### Proof

Merge sort divides the array into two halves and calls itself for the two halves. It then merges the two sorted halves.

Let `T(n)` be the time complexity of merge sort for an array of size `n`.

```C
T(n) = 2T(n/2) + kn
```

`kn` is the time taken to merge the two sorted halves.
`2T(n/2)` is the time taken to sort the two smaller subarrays.

Note that `T(0) = 0`. (Cause what will you do with an empty array?)

The solution to the above recurrence relation is as follows:

```
T(n) = 2T(n/2) + kn
     = 2(2T(n/4) + k(n/2)) + kn
     = 4T(n/4) + 2kn
     = 4(2T(n/8) + k(n/4)) + 2kn
     = 8T(n/8) + 3kn
     = 2^iT(n/2^i) + ikn

When n/2^i = 1 (i.e. we come down to the base case of having only 1 element)
=> i = log n

Therefore,

T(n) = 2^log n T(1) + kn log n
     = nT(1) + kn log n
     = O(n log n)
```

## Quick Sort

- **Best Case**: O(n log n)
- **Average Case**: O(n log n)
- **Worst Case**: O(n^2)

### Proof

Quick sort picks a pivot element and partitions the array around the pivot. It then calls itself for the two partitions.

Let `T(n)` be the time complexity of quick sort for an array of size `n`.

```
T(n) = T(k) + T(n-k-1) + kn

Therefore if we choose the pivot optimally at all times, k = n/2

T(n) = 2T(n/2) + kn
     = 2(2T(n/4) + k(n/2)) + kn
     = 4T(n/4) + 2kn
     = 2^iT(n/2^i) + ikn

When n/2^i = 1 (i.e. we come down to the base case of having only 1 element)
=> i = log n

Therefore,

T(n) = 2^log n T(1) + kn log n
     = nT(1) + kn log n
     = O(n log n)
```

However, for worst case, if pivot is chosen as the smallest or largest element, the recurrence relation becomes:

```
T(n) = T(n-1) + kn
     = T(n-2) + k(n-1) + kn
     = T(n-3) + k(n-2) + k(n-1) + kn
     = ...
     = T(1) + k(2 + 3 + ... + n-1) + kn
     = O(n^2)
```

For average-case analysis, we assume that the pivot is chosen randomly. The probability of choosing the smallest or largest element as the pivot is very low.

Therefore, the average time complexity of quick sort is O(n log n).

```
T(n) = T(k) + T(n-k-1) + kn
     = 2/n * (sum from i=0 to n-1 for T(i)) + kn

nT(n) = 2 * (sum from i=0 to n-1 for T(i)) + kn^2
(n-1)T(n-1) = 2 * (sum from i=0 to n-2 for T(i)) + k(n-1)^2

Subtracting the second equation from the first,

nT(n) - (n-1)T(n-1) = 2T(n-1) + kn^2 - k(n-1)^2
=> nT(n) = (n+1)T(n-1) + 2kn

Dividing by n(n+1),

T(n)/(n+1) = T(n-1)/n + 2k/(n+1)

Telescoping the above equation,

T(n)/(n+1) = T(n-1)/n + 2k/(n+1)
T(n-1)/n = T(n-2)/(n-1) + 2k/n
T(2)/3 = T(1)/2 + 2k/3

Adding all the equations,

T(n)/(n+1) = T(1)/2 + 2k/3 + 2k/4 + ... + 2k/(n+1)
           = T(1)/2 + 2k * (1/3 + 1/4 + ... + 1/(n+1))

This is a summation about ln(n+1) + y - 1.5 where y is Euler constant.

T(n)/(n+1) = O(log n)

Therefore, T(n) = O(n log n)
```

## Heap Sort

- **Best Case**: O(n log n)
- **Average Case**: O(n log n)
- **Worst Case**: O(n log n)

### Proof

Heap sort builds a min or max heap and repeatedly extracts the root element and heapifies the remaining heap.

Insertion of an element in a heap takes `O(log n)` time. Proof is as follows:

-> **Proof of height of a heap with `n` nodes:**

```
Since a heap is filled from left to right, level wise, we can say that,
L(0) = 1 = 2^0
L(1) = 2 = 2^1
L(2) = 4 = 2^2
where L(i) denotes the maximum number of nodes possible at level (i+1).

Note that height is the maximum level of the heap - 1 i.e. h = i(max)

Therefore, the total number of nodes in a heap with height h is always less than 2^(h+1) and greater than or equal to 2^h.

n = L(0) + L(1) + L(2) + ... + L(h) - k (where k is the number of free nodes at the last level)
  = 2^0 + 2^1 + 2^2 + ... + 2^h - k
  = 2^(h+1) - 1 - k
  => 2^(h+1) > n

also, n = L(0) + L(1) + L(2) + ... + L(h-1) + k (where k is the number of used nodes at the last level)
  = 2^0 + 2^1 + 2^2 + ... + 2^(h-1) + k
  = 2^h - 1 + k
  => 2^h < n
   
Therefore, 2^h < n < 2^(h+1)

Taking log on both sides,

h <= log n < h+1
=> h = O(log n)
```

-> **Proof of insertion of an element in a heap:**

```
We know that the height of a heap with n nodes is O(log n).

Insertion in a heap is done at the last level, at the first available position from left to right.
Then we heapify the heap to maintain the heap property by comparing the element with its parent and swapping if necessary.

Thus, maximum number of comparisons done in heapify is equal to the height of the heap.
i.e. T(n) = h*O(1) = O(log n)

where, h is the height of the heap and T is the time taken to insert and heapify an element in a heap.
Swapping and comparison is an O(1) operation.

since h = O(log n), T(n) = O(log n)*O(1) = O(log n)

```
-> **Proof of building a heap:**

```
Building a heap of n elements is done by inserting each element one by one in the heap.

Therefore, the time taken to build a heap of n elements is the sum of time taken to insert and heapify each element.

T(n) = O(log 1) + O(log 2) + O(log 3) + ... + O(log n) < O(log n) + O(log n) + O(log n) + ... + O(log n) (n times)
     = O(log n!) < O(n log n)

Therefore, building a heap of n elements takes O(n log n) time.
```

-> **Proof of extracting the root element:**

```
Extracting the root element of a heap is done by swapping the root element with the last element and heapifying the remaining heap.

Heapifying the remaining heap takes O(log n) time.
i.e. T(n) = O(1)+O(1)*h

where h is the height of the heap and T is the time taken to heapify the remaining heap.
The first O(1) is for extracting the root element and swapping it with the last element.

Since h = O(log n), T(n) = O(1) + O(1)*O(log n) = O(log n)
```

-> **Proof of heap sort:**

```
Heap sort builds a heap and repeatedly extracts the root element and heapifies the remaining heap.

Building a heap of n elements takes O(n log n) time.
Extracting the root element and heapifying the remaining heap takes O(log n) time.

Therefore for an unsorted array of n elements, T(n) = O(n log n) + O(n log n) = O(n log n)
Therefore, heap sort has a time complexity of O(n log n).
```

## Bucket Sort

- **Best Case**: O(n + k)
- **Average Case**: O(n + k)
- **Worst Case**: O(n^2)

### Proof

Bucket sort divides the array into `k` buckets and sorts each bucket individually.
It is used in special cases where the input is uniformly distributed over a range and the range is less than a constant M.

Let `T(n)` be the time complexity of bucket sort for an array of size `n`.
```
Thus, in special case, the sorting of each bucket takes O(1) time. (its already sorted)
We iterate over the array once to put the elements in the buckets and then iterate over the buckets to find the sorted array.

Therefore, T(n) = O(n) + O(k) = O(n + k)

However, in the worst case, if all the elements are in the same bucket, the time complexity becomes equal to the time complexity of the sorting algorithm used to sort the bucket.

Therefore, the worst case time complexity of bucket sort is O(n^2). (if we use the trivial sorting algorithms like bubble, insertion, selection and such)
```

## Counting Sort

- **Best Case**: O(n + k)
- **Average Case**: O(n + k)
- **Worst Case**: O(n + k)

### Proof

Counting sort is an integer sorting algorithm that operates by counting the number of occurrences of each element in the input array and using arithmetic to determine the position of each element in the output array.

THus, it works best only for a small range of integer inputs like bucket sort.

Let `T(n)` be the time complexity of counting sort for an array of size `n`.

```
Time complexity of finding the frequency of each element in the array is O(n).
Time complexity of finding the position of each element in the output array is O(k) (using the frequency array).

Therefore, T(n) = O(n) + O(k) = O(n + k)
```

## Shell Sort

- **Best Case**: O(n log n)
- **Average Case**: O(n log n)
- **Worst Case**: O(n^2)

### Proof

Shell sort is a generalization of insertion sort that allows the exchange of items that are far apart. The idea is to arrange the list of elements so that, starting anywhere, taking every hth element produces a sorted list.

**Worst-case time complexity of shell sort using Shell's increments is O(n^2).**

The proof requires showing not only an upper bound but also showing that there exists some input that actually takes Omega(n^2) (omega is that weird arc thingy) time.

The lower bound is shown by creating a bad input for the algorithm. We choose N to be a power of 2 which makes all the increments even except the last one which will be 1. Now the input array will be N/2 largest elements in even positions and N/2 smallest elements in odd positions. Since the increments are even until the last one, all the LARGE elements are still in even positions and all the SMALL elements are still in odd positions. This means that the algorithm will not be able to sort the array in the first pass and will have to make N/2 passes to sort the array. This gives us a lower bound of Omega(n^2).

The upper bound is shown by showing that the algorithm will take O(n^2) time for the worst-case input. Since a pass with increment h<sub>k</sub> is like h<sub>k</sub> independent insertion sorts, each with N/h<sub>k</sub> elements, the time complexity of a pass is O(h<sub>k</sub> * (N/h<sub>k</sub>)^2) = O(N<sup>2</sup>/h<sub>k</sub>). Summing over all the passes, we get O(N<sup>2</sup> * (1/h<sub>1</sub> + 1/h<sub>2</sub> + ... + 1/h<sub>k</sub>)). Now, the sum of 1/h<sub>k</sub> for Shell's increments is always less than 2 since the largest value of 1/h<sub>k</sub> is 1. This gives us an upper bound of O(N<sup>2</sup> * 2) = O(N<sup>2</sup>).

**Worst-case time complexity of shell sort using Hibbard's increments is O(n<sup>3/2</sup>).**

# Proofs from Weiss

## Average number of inversions in an array of N distinct elements is N(N-1)/4

- **Proof**:

```
For a given array A, let Ar be inverse of A. Consider (i, j) such that i < j 
(i, j) represents inversions in A and Ar. 

Number of inversions in A + Number of inversions in Ar >= N(N-1)/2

On an average, all sequences can be equally likely. Therefore, average number of inversions in A = average number of inversions in Ar = N(N-1)/4
```

## Any sorting algorithm that sorts by comparing adjacent elements needs Omega(N^2) comparisons on an average

- **Proof**:

```
In the worst case, the number of comparisons is N+(N-1)+...+1 = N(N+1)/2 = Omega(N^2)
As in worst case we would need to move the smallest element to the first position, the second smallest to the second position and so on.
```

## Let T be a binary tree of depth d. The number of nodes in T is at most 2^d leaves

- **Proof**:

```
By induction.

For d = 0, the tree has 1 node and 2^0 leaves.

For d = 1, the tree has 1+2 = 3 nodes at most and 2^1 = 2 leaves.

Assume that for d = k, the tree has at most 2^k leaves.

For d = k+1, the tree has at most 1+2+4+...+2^k+2^(k+1) = 2^(k+1) + 2^k - 1 = 2^(k+1) leaves.

Therefore, the number of nodes in T is at most 2^d leaves.
```

## A tree T with L leaves has a depth of at least [log L] 

- **Proof**:

```
For L = 1, the tree has a depth of 0 and [log 1] = 0.

For L = 2, the tree has a depth of 1 and [log 2] = 1.

For L = 3, the tree has a depth of 2 and [log 3] = 1.

For L = 4, the tree has a depth of 2 and [log 4] = 2.

For L = 5, the tree has a depth of 3 and [log 5] = 2.

Since L always lies between 2^d and 2^(d+1), the depth of the tree is d <= [log L] < d+1.
```

## Any sorting algorithm that uses only comparisons to sort N elements has a worst-case time complexity of Omega(N log N)

- **Proof**:

```
log N! = log 1 + log 2 + ... + log N
       >= log N/2 + log N/2 + ... + log N/2
       = N/2 log N/2 >= N/2 log N/2 - N/2 
       = Omega(N log N)
```

# What's a decision tree?

A decision tree is a tree in which each internal node represents a "test" on an attribute (e.g. whether a coin flip comes up heads or tails), each branch represents the outcome of the test, and each leaf node represents a class label (decision taken after computing all attributes). The paths from root to leaf represent classification rules.

Its an abstraction used to prove the lower bounds of algorithms. Every algorithm that sorts by comparing adjacent elements can be represented as a decision tree. The number of comparisons made by the algorithm is the depth of the decision tree. The average depth of the decision tree is Omega(N log N) and is the average number of comparisons made by the algorithm. 
