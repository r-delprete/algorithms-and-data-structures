# Huffman algorithm

## Input parameters

- `nodes`: nodes to encode

## Output

Returns the Huffman tree root

This is the pseudo-code:

## Pseudo-code

```
Huffman(nodes):
    size = |nodes|
    queue = nodes

    for i = 1 to size - 1:
        z = allocate_node()

        z.left = queue.extract_min()
        z.right = queue.extract_min()

        z.frequency = z.left.frequency + z.right.frequency;

        queue.insert(z)

    return queue.extract_min()
```

### _Notes_

`queue` variable is a minimum priority queue and the elements inside are ordered by frequency.
