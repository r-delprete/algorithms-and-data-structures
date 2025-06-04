# DFS (Depth-First-Search) visit algorithm with cycles counting

Dato un grafo G = (V, E) si scriva un algoritmo in pseudo-codice
che restituisca in numero di cicli di G

## Input parameters

- `graph`: graph from which apply the visit

## Pseudo-code

```
dfs(graph):
    cycles = 0

    for node in graph.nodes:
        node.predecessor = NIL
        node.d = 0
        node.f = 0
        node.color = white

    for node in graph.nodes:
        if node.color == white:
            cycles += dfs_visit(node)

    return cycles

dfs_visit(node):
    cycles = 0
    node.color = gray

    node.d = time = time + 1

    for adj_node in node.adj
        if adj_node.color == white:
            adj_node.predecessor = node
            dfs_visit(adj_node)
        else adj_node.color == gray and node != adj_node:
            cycles++

    node.f = time = time + 1
    node.color = black

    return cycles
```
