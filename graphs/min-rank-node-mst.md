# Minimum MST rank node (Nodo di rango minimo dell'MST)

Restituire nodo con rango minimo di un MST

## Input parameters

- `graph`: graph from which the MST has to be computed

## Output

Return the minimum rank node in MST

## Pseudo-code

```
kruskal(graph):
    mst = ∅

    for node in graph.nodes:
        make_set(node)

    sorted_edges = sort(graph.edges)  // sort edges by weight in not-desc order

    for (node1, node2) in sorted_edges:
        if find_set(node1) != find_set(node2):
            mst = mst ∪ (node1, node2)
            union(node1, node2)

    min_node = NIL
    min_rank = ∞

    for node in graph.nodes:
        if node.rank < min_rank:
            min_rank = node.rank
            min_node = node

    return min_node
```

To view `union`, `make_set` and `find_set` functions, see [Kruskal algorithm → make_set, find_set and union functions](kruskal.md#make_node-find_set-and-union-functions)
