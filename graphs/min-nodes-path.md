# Minimum nodes path (Cammino minimo dei nodi)

## Assignment

Dato un grafo G(V, E), un nodo s ed un intero K,
restituire il numero di nodi il cui cammino minimo
da s sia maggiore di K

## Input parameters

- `graph`: graph from which apply the visit
- `source`: source node to start the visit
- `K`

## Output

Return the nodes number which path is greater than `K`

## Pseudo-code

```
bfs_visit(graph, source, K):
    for node in (graph.nodes - source):
        node.predecessor = NIL
        node.color = white
        node.distance = ∞

    source.color = gray
    source.distance = 0
    source.predecessor = NIL

    queue = new queue()
    queue.enqueue(source)

    while queue != ∅:
        node = queue.dequeue()

        for adj_node in node.adj:
            if adj_node.color == white:
                adj_node.predecessor = node
                adj_node.color = gray
                adj_node.distance = node.distance + 1

                queue.push(adj_node)

        node.color = black

    total_nodes = 0

    for node in graph.nodes:
        if node.distance > K:
            total_nodes += 1

    return total_nodes
```
