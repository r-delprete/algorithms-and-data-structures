# Maximum rank node in MST (Nodo con rank massimo nell'MST)

Dato un grafo $G$ non orientato e pesato con nodo sorgente $s$,
scrivere un algoritmo in pseudo-codice che restituisca il nodo di grado massimo dell'MST

## Pseudo-codice

```
prim(graph, source, weights):
    max_degree = -1
    max_node = NIL

    for node in graph.nodes:
        node.key = inf
        node.predecessor = NIL
        node.degree = 0

    source.key = 0

    queue = graph.nodes

    while queue != ∅:
        node = queue.extract_min()

        if node.predecessor != NIL:
            node.predecessor.degree += 1
            node.degree += 1

        for adj_node in node.adj:
            if adj_node ∈ queue and weights(node, adj_node) < adj_node.key:
                adj_node.predecessor = node
                adj_node.key = weights(node, adj_node)

    for node in graph.nodes:
        if node.degree > max_degree:
            max_degree = node.degree
            max_node = node

    return max_node
```

### _Notes_

#### `degree` property

##### Description

The `degree` property represents the number of edges connecting a node within the Minimum Spanning Tree (MST). Each node keeps a counter that is incremented each time an edge is added to the MST.

##### Functionality

During the execution of Prim's algorithm, every time a node is added to the MST and an edge connects the node to its predecessor, both nodes' degrees are incremented by one. The degree of a node indicates how many connections (edges) it has within the MST.
