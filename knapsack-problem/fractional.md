# Fractional Knapsack Problem

Suppose there is a thief who enters a store. He has a backpack of fixed size 𝑊. The goal is to fill the backpack in such a way that the total value of the items $v_i$ inside is as high as possible. Each item has a weight $w_i$ and a value $v_i$. The items can either be taken, left, or fractioned.

## Input parameters

- `weights`: items weights sorted by $\frac{v_i}{w_i}$
- `values`: items values sorted by $\frac{v_i}{w_i}$
- `fractions`: items fractions. It can be equals to:
  - `fractions[k] = 0`: item isn't taken
  - `fractions[k] = 1`: item is fully taken
  - `fractions[k] = 0 < fractions[k] < 1`: item is in part taken
- `knapsackCapacity`: total knapsack capacity

## Output

Returns the maximum profit

## Pseudo-code

```
fractional_knapsack(weights, values, fractions, knapsackCapacity):
    numItems = length(values)

    profit = 0
    capacity = knapsackCapacity

    // Initialize fractions to 0 (no items selected initially)
    for i = 0 to numItems:
        fractions[i] = 0.0

    k = 1

    // Iterate until there are items and there's capacity into knapsack
    while k <= numItems and capacity > 0.0:

        // If the item fits completely, take it
        if weights[k] <= capacity:
            // Take the whole item
            fractions[k] = 1.0
            capacity = capacity - weights[k]

        // Otherwise, take the fraction that fits and break
        else:
            // Take only what fits
            fractions[k] = capacity / weights[k]
            capacity = 0.0

        profit = profit + fractions[k] * values[k]

        // next object
        k = k + 1

    return profit
```
