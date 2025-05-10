# Maximum rank node in MST (Nodo con rank massimo nell'MST)

## Assignment

Dato un grafo $G$ non orientato e pesato con nodo sorgente $s$,
scrivere un algoritmo in pseudo-codice che restituisca il nodo di grado massimo dell'MST

## Input parameters

- `graph`: graph from which the MST has to be computed
- `source`: source node to start building MST
- `weights`: edges weights

## Output

Return the maximum rank node in MST

## Pseudo-codice

```
prim (graph, source, weights):
    for node in graph.nodes:
        node.predecessor = NIL
        node.key = ∞
        node.rank = 0

    source.predecessor = NIL
    source.key = 0
    source.rank = 0

    queue = new queue()         // minimum priority queue
    queue.push(source)

    while queue != ∅:
        node = queue.extract_min()

        for adj_node in node.adj:
            if adj_node ∈ queue and weights(node, adj_node) < adj_node.key:
                adj_node.key = weights(node, adj_node)
                adj_node.predecessor = node
                queue.push(adj_node)

        if node.predecessor != NIL:
            node.rank += 1
            node.predecessor.rank += 1

    max_rank_node = NIL
    max_rank = -1

    for node in graph.nodes:
        if node.rank > max_rank:
            max_rank_node = node
            max_rank = node.rank

    return max_rank_node
```

### _Notes_

- `queue` variable is a minimum priority queue and the elements inside are ordered by `key` value
- `adj_node.key = weights(node, adj_node)`: this code line **decreases** `adj_node` `key` value

#### `rank` property

##### Description

The `rank` property represents the number of edges connecting a node within the Minimum Spanning Tree (MST). Each node keeps a counter that is incremented each time an edge is added to the MST.

##### Functionality

During the execution of Prim's algorithm, every time a node is added to the MST and an edge connects the node to its predecessor, both nodes' ranks are incremented by one. The rank of a node indicates how many connections (edges) it has within the MST.
