# Hash Table Open Addressing Insert Function

This is the hash table _open addressing_ **search** function pseudo-code

## Input parameters:

- `hash_table`: hash table data structure
- `element`: element to search

## Output

Returns:

- `NIL` if element isn't found
- _element index_ if it has found successfully.

## Pseudo-code

```
search(hash_table, element):
    size = length(hash_table)
    i = 0

    while i < size or hash_table[index] != NIL:
        index = hash_function(element, i)

        if hash_table[index] == element:
            return index

        i += 1

    return NIL
```
