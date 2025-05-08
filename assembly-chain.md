# Assembly chain algorithm

## Input parameters

- `a1, a2`: processing times for each station on the two lines.
- `t1, t2`: transition times between the lines.
- `e1, e2`: entry times into the two lines.
- `x1, x2`: exit times from the two lines.
- `n`: number of stations.

## Output parameters

- `f_opt`: minimum time required to complete the process.
- `l_opt`: last line used in the optimal path.

## Pseudo-code

```
fastest(a, t, e, x, n):
    f1[1] = e1 + a1, 1   // entrance chain 1
    f2[1] = e2 + a2, 1   // entrance chain 2

    for j = 2 to n:
        if f1[j - 1] <= f2[j - 1] + t2[j - 1]:  // check switch to station 1
            f1[j] = f1[j - 1] + a1, j
            l1[j] = 1
        else:
            f1[j] = f2[j - 1] + t2[j - 1] + a1, j
            l1[j] = 2

        if f2[j - 1] <= f1[j - 1] + t1[j - 1]:  // check switch to station 2
            f2[j] = f2[j - 1] + a2, j
            l2[j] = 2
        else:
            f2[j] = f1[j - 1] + t1[j - 1] + a2, j
            l2[j] = 1

    if f1[n] + x1 <= f2[n] + x2:  // exit
        f_opt = f1[n] + x1
        l_opt = 1
    else:
        f_opt = f2[n] + x2
        l_opt = 2

    return f_opt, l_opt
```

## Algorithm steps

### 1. Initialization

The first station of each line starts with the time `e1 + a1, 1` and `e2 + a2, 1`

### 2. Iteration over stations

For each station `j` from `2 to n`, we decide whether to stay on the same line or switch lines.

- If staying is faster, we update the time without changing lines:

  ```
  f1[j] = f1[j - 1] + a1, j
  ```

- If switching lines is faster, we pay the transition cost:

  ```
  f1[j] = f2[j - 1] + t2[j - 1] + a1, j
  ```

The same procedure applies for line 2.

### 3. Determine the exit time

After completing the last station `n`, we calculate the minimum time considering the exit times `x1` and `x2`:

```
if f1[n] + x1 <= f2[n] + x2:
    f_opt = f1[n] + x1
    l_opt = 1
else:
    f_opt = f2[n] + x2
    l_opt = 2
```

### Algorithm complexity

Since we visit each station only once, the algorithm has a time complexity of $O(n)$, making it much more efficient compared to an exhaustive search with a complexity of $O(2^n)$.

### Example usage

If the values are:

```
a1 = [4, 5, 3, 2]
a2 = [2, 10, 1, 4]
t1 = [7, 4, 5]
t2 = [9, 2, 8]
e1 = 10
e2 = 12
x1 = 18
x2 = 7
```

The algorithm calculates the minimum time required and the optimal path to follow through the assembly line stations.
