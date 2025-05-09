# DFS (Depth-First-Search) visit algorithm

## Input parameters

- `graph`: graph from which apply the visit

## Pseudo-code

```
time = 0

dfs(graph):
    for node in graph.nodes:
        node.predecessor = NIL
        node.d = 0
        node.f = 0
        node.color = white

    for node in graph.nodes:
        if node.color == white:
            dfs_visit(node)

dfs_visit(node):
    node.color = gray

    time += 1
    node.d = time

    for adj_node in node.adj
        if adj_node.color == white:
            adj_node.predecessor = node
            dfs_visit(adj_node)

    time += 1
    node.f = time
    node.color = black
```
