# Minimum weights not in MST and is MST unique

## Assignment

Grafo che ritorna i pesi minimi non appartenenti all'mst
e dire che se un MST è unico

## Input parameters

- `graph`: graph from which MST has to be computed

## Output

Returns:

- a boolean which indicates if MST is unique
- a set which contains minimum weights not in MST

## Pseudo-code

```
kruskal(graph):
    mst = ∅

    for node in graph.nodes:
        make_set(node)

    sorted_edges = sort(graph.edges)        // sort edges by weight in not-decrescent order

    for (node1, node2) in sorted_edges
        if find_set(node1) != find_set(node2)
            union(node1, node2)
            mst = mst ∪ (node1, node2)         // add (node1, node2) edge to mst

    min_edge_mst_weight = ∞
    for (node1, node2) in mst:
        if (node1, node2).weight < min_edge_mst_weight:
            min_edge_mst_weight = (node1, node2).weight

    is_unique = true
    for (node1, node2) in graph.edges:
        if (node1, node2) ∉ mst and (node1, node2).weight == min_edge_mst_weight:
                is_unique = false
                break

    min_edges_weights = ∅
    min_weight = ∞
    for (node1, node2) in graph.edges:
        if (node1, node2) ∉ mst:
            if (node1, node2).weight < min_weight:
                min_weight = (node1, node2).weight
                min_edges_weights = min_edges_weights ∪ (node1, node2).weight
            else if (node1, node2).weight == min_weight:
                min_edges_weights = min_edges_weights ∪ (node1, node2).weight

    return is_unique, min_edges_weights
```

To view `union`, `make_set` and `find_set` functions, see [Kruskal algorithm → make_set, find_set and union functions](kruskal.md#make_node-find_set-and-union-functions)
