# MST Height

## Trace

Dato un grafo non orientato, pesato, con radice R. Calcolare l'altezza del MST radicato in R.

## Pseudo-code

```
prim(graph, root, weights):
    for node in graph.nodes:
        node.predecessor = NIL
        node.key = inf

    root.key = 0
    root.predecessor = NIL

    queue = graph.nodes         // minimum priority queue

    while not queue.is_empty():
        node = queue.extract_min()

        for adj_node in node.adj:
            if adj_node ∈ queue and weights(node, adj_node) < adj_node.key:
                adj_node.predecessor = node
                adj_node.key = weights(node, adj_node)    // decrease key


bfs_visit(graph, root):
    prim(graph, root)

    max_height = 0

    root.d = 0
    root.predecessor = null
    root.color = gray

    queue = ∅
    queue.append(root)

    while queue != ∅:
        node = queue.pop()

        for adj_node in node.adj:
            if adj_node.color == white and node == adj_node.predecessor:
                adj_node.color = gray
                adj_node.d = node.d + 1

                if adj_node.d > max_height:
                    max_height = adj_node.d

                queue.append(adj_node)

        node.color = black

    return max_height
```
