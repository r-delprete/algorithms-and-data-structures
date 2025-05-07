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
    index = h(element, i)

    while hash_table[index] != NIL and i < size:
        if hash_table[index] != '#' and hash_table[index].key == element:
            hash_table[index] = '#'

            return 'element deleted'

        i++
        index = h(element, i)

    return NIL
```
