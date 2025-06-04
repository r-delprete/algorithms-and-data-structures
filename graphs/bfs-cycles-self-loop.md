# Assignment description

Visita BFS che tiene conto anche di cappi e cicli di un grafo

## Pseudo-code

```
bfs_visit(graph, source):
    cycles = 0
    self_loops = 0

    for node in (graph.nodes - source):
        node.color = white
        node.distance = ∞
        node.predecessor = NIL


    source.color = gray
    source.distance = 0
    source.predecessor = NIL

    queue = new queue()
    queue.enqueue(source)

    while queue != ∅:
        node = queue.dequeue()

        for adj_node in node.adj:
            if adj_node == node:
                self_loops++
            else if adj_node.color == white:
                adj_node.color = gray
                adj_node.distance = node.distance + 1
                adj_node.predecessor = node

                queue.enqueue(adj_node)
            else if adj_node.color == gray:
                cycles++



        node.color = black

    return cycles, self_loops
```
