# MST Height

## Assignment description

Dato un grafo non orientato, pesato, con radice R. Calcolare l'altezza del MST radicato in R.

## Input parameters

- `graph`: graph from which the MST has to be computed
- `source`: source node to start building MST
- `weights`: edges weights

## Pseudo-code

```
prim(graph, source, weights):
    for node in graph.nodes:
        node.predecessor = NIL
        node.key = ∞

    source.key = 0
    source.predecessor = NIL

    queue = graph.nodes         // minimum priority queue

    while queue != ∅:
        node = queue.extract_min()

        for adj_node in node.adj:
            if adj_node ∈ queue and weights(node, adj_node) < adj_node.key:
                adj_node.predecessor = node
                adj_node.key = weights(node, adj_node)    // decrease key


bfs_visit(graph, source):
    prim(graph, source)

    max_height = 0

    source.d = 0
    source.predecessor = NIL
    source.color = gray

    queue = ∅
    queue.enqueue(source)

    while queue != ∅:
        node = queue.dequeue()

        for adj_node in node.adj:
            if adj_node.color == white and node == adj_node.predecessor:
                adj_node.color = gray
                adj_node.d = node.d + 1

                if adj_node.d > max_height:
                    max_height = adj_node.d

                queue.enqueue(adj_node)

        node.color = black

    return max_height
```
