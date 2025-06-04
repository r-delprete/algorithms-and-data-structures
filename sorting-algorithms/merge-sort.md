# Abstract: Merge Sort with Sentinels

Merge Sort is a classic **divide-and-conquer** sorting algorithm that divides the input array into two halves, recursively sorts them, and then merges the sorted halves to produce the final sorted array. This version of Merge Sort uses **sentinels** to simplify the merge process by eliminating the need for boundary checks during comparison.

## How It Works

### 1. Divide

The array is recursively divided into two halves until the base case is reached (i.e., subarrays of size 1 or 0, which are trivially sorted).

### 2. Conquer

Each half is sorted recursively using the `merge_sort` function.

### 3. Combine (Merge)

The `merge` function merges the two sorted subarrays into a single sorted array. This implementation uses **sentinels**—special "infinite" values placed at the end of the temporary left and right subarrays—to streamline comparisons and avoid explicitly checking if a subarray has been fully traversed.

## Input Parameters

- `array`: The array of elements to be sorted.
- `start`: The starting index of the subarray to be sorted.
- `end`: The ending index of the subarray to be sorted.

These parameters allow the function to operate on sub-sections of the array during recursion.

## Output

The function returns the original array with its elements sorted in **non-decreasing order**. Sorting is done in-place in terms of the input array, but additional memory is used during the merging step.

## Pseudo-code

```text
merge_sort(array, start, end):
    if start < end:
        int mid = (start + end) / 2

        merge_sort(array, start, mid)
        merge_sort(array, mid + 1, end)

        return merge(array, start, end, mid)

merge(array, start, end, mid):
    int left_size = mid - start + 1
    int right_size = end - mid
    int left[left_size], right[right_size]

    for i = 0 to left_size - 1:
        left[i] = array[start + i]

    for j = 0 to right_size - 1:
        right[j] = array[mid + j + 1]

    left[left_size] = right[right_size] = inf

    int i = j = 0

    for k = start to end:
        if left[i] <= right[j]:
            array[k] = left[i]
            i++
        else:
            array[k] = right[j]
            j++

    return array

```
