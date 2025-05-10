# Maximum depth node in MST (Nodo con profondità massima di un MST)

## Assignment

Dato un grafo connesso non orientato pesato $G = (V, E)$ con pesi $w(u, v)$
ed un vertice $r \in V$, si scriva in pseudo-codice un algoritmo
che restituisca il nodo con la profondità massima del MST radicato in $r$

## Input parameters

- `graph`: graph from which the MST has to be computed
- `source`: source node to start building MST
- `weights`: edges weights

## Output

Return the maximum depth node in MST

## Pseudo-code

```
prim(graph, root, weights):
    max_depth = 0
    max_node = root

    queue = graph.nodes         // minimum priority queue

    for node in graph.nodes:
        node.key = inf
        node.predecessor = null
        node.distance = -1

    root.key = 0
    root.predecessor = null

    while queue != ∅:
        node = queue.extract_min()

        for adj_node in node.adj:
            if adj_node ∈ queue and weights(node, adj_node) < adj_node.key:
                adj_node.predecessor = node
                adj_node.key = weights(node, adj_node)
                adj_node.distance = node.distance + 1

                if adj_node.distance > max_depth
                    max_depth = adj_node.distance
                    max_node = adj_node

    return max_node
```

### _Notes_

- `queue` variable is a minimum priority queue and the elements inside are ordered by `key` value
- `adj_node.key = weights(node, adj_node)`: this code line **decreases** `adj_node` `key` value
