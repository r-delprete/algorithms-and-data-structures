# Prim algorithm

**Prim** algorithm is used to build a **Minimum Spanning Tree (MST)**

## Input parameters

- `graph`: graph from which the MST is to be computed
- `source`: source node to start building MST
- `weights`: edges weights

## Pseudo-code

```
prim(graph, source, weights):
    for node in graph.nodes:
        node.key = inf
        node.predecessor = NIL

    source.key = 0

    queue = graph.nodes

    while queue != ∅:
        node = queue.extract_min()

        for adj_node in node.adj:
            if adj_node ∈ queue and weights(node, adj_node) < adj_node.key:
                adj_node.predecessor = node
                adj_node.key = weights(node, adj_node)
```

### _Notes_

- `queue` variable is a minimum priority queue and the elements inside are ordered by `key` value
- `adj_node.key = weights(node, adj_node)`: this code line **decreases** `adj_node` `key` value
