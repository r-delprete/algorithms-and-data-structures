# Optimal Substructure

## Description

The problem is about calculating the recursive function F(x,y) defined as:

$F \left(x,y \right) = max { \left(F\left(x - 1,y - 1\right) + 1, F\left(x - 1, y\right), F\left(x, y - 1\right)\right) }$

The goal is to find the maximum value of F(x,y) using the optimal substructure property, which allows calculating the result based on the optimal results of smaller sub-problems. This approach can be optimized using dynamic programming with memoization.

## Input parameters

- `x` _(int)_: The first dimension of the problem. Represents the current index along the horizontal axis of the recursive table. Must be a non-negative integer.

- `y` _(int)_: The second dimension of the problem. Represents the current index along the vertical axis of the recursive table. Must be a non-negative integer.

- `memo` _(2D list of int)_: A matrix (table) used for **memoization**, which stores previously computed results of sub-problems. Each cell `memo[i][j]` contains the value of `F(i, j)` if already computed, otherwise `-1`.

## Output

Returns the maximum value returned by the function `F(x, y)`, computed using the defined recurrence. This value represents the optimal solution based on the optimal substructure property.

## Pseudo-code

```
F(x, y, memo):
    if x == 0 or y == 0:
        return 0

    if memo[x][y] != -1:
        return memo[x][y]

    val1 = F(x - 1, y - 1, memo) + 1
    val2 = F(x - 1, y, memo)
    val3 = F(x, y - 1, memo)

    result = max(val1, val2, val3)

    memo[x][y] = result

    return memo[x][y]
```
