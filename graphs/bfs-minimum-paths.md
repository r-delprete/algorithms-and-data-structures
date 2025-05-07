# Assignment description

Grafo BFS dove devi conteggiare il numero dei cammini minimi < K

## Pseudo-code

```
bfs_visit(graph, source_node, K):
    minimum_paths = 0    // minimum paths below K

    for node in (graph.nodes - source_node):
        node.distance = inf
        node.color = white
        node.predecessor = NIL
        node.count = 0         // minimum paths to reach node

    source_node.color = gray
    source_node.distance = 0
    source_node.predecessor = NIL
    source_node.count = 1

    queue = new queue()
    queue.enqueue(source_node)

    while queue != ∅:
        node = queue.dequeue()

        for adj_node in node.adj:
            if adj_node.color == white:
                adj_node.color = gray
                adj_node.predecessor = node
                adj_node.distance = node.distance + 1
                adj_node.count = node.count

                queue.enqueue(adj_node)
            else if adj_node.distance == node.distance + 1:
                adj_node.count += node.count

        node.color = black

        if node.distance < K:
            minimum_paths += node.count

    return minimum_paths
```

### _Notes_

`count` attribute in node represents minimum paths from source to node
