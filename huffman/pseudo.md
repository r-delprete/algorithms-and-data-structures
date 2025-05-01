# Huffman algorithm

## Input parameters

- `nodes`: nodes queue to encode

## Output

Returns the Huffman tree root

This is the pseudo-code:

## Pseudo-code

```
Huffman(nodes):
    size = |nodes|
    queue = nodes

    for i = 1 to size - 1:
        z = new Node()      // allocate a new node

        z.left = queue.extract_min()
        z.right = queue.extract_min()

        z.frequency = z.left.frequency + z.right.frequency

        queue.add(z)

    return queue.extract_min()
```

### _Notes_

`queue` variable is a minimum priority queue and the elements inside are ordered by frequency.
