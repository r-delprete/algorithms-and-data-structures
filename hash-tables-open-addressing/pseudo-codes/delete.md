# Hash Table Open Addressing Insert Function

This is the hash table _open addressing_ **delete** function pseudo-code.
The **deleted element's index** will be marked as deleted with `#`.

## Input parameters:

- `hash_table`: hash table data structure
- `element`: element to insert

## Output

Returns:

- `NIL` if element cannot be deleted
- `element deleted` if it has deleted successfully.

## Pseudo-code

```
delete(hash_table, element):
    size = length(hash_table)
    i = 0

    while i < size:
        index = h(element, i)

        if hash_table[index] == NIL:
            return NIL

        if hash_table[index] == element:
            hash_table[index] = '#'
            return 'element deleted'


        i++

    return NIL
```
