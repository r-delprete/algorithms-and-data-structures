# Hash Table Open Addressing Insert Function

This is the hash table _open addressing_ **insert** function pseudo-code

## Input parameters:

- `hash_table`: hash table data structure
- `element`: element to insert

## Output

Returns:

- `overflow` if element cannot be inserted
- _inserted element index_ if it has added successfully.

## Pseudo-code

```
insert(hash_table, element):
    size = length(hash_table)
    i = 0

    while i < size:
        if hash_table[index] == NIL:
            hash_table[index] = element

            return index

        i += 1

    return 'overflow'
```

### _Notes_

If an hash table cell can be considered deleted with character `'#'`, the `if` condition `hash_table[index] == NIL` will change to `hash_table[index] == NIL or if hash_table[index] == '#'`
