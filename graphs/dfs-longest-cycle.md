# Assignment description

Definire un algoritmo ricorsivo che, dato un grafo $G$ con funzione peso $W: E \rightarrow R$,
conta il numero di nodi nel più lungo ciclo di $G$

## Input parameters

- `graph`: graph from which apply the visit

## Output

Returns the graph maximum cycle length

## Pseudo-code

```
time = 0

dfs(graph):
    max_cycle_length = 0

    for node in graph.nodes:
        node.color = white
        node.predecessor = NIL
        node.distance = 0
        node.end_visit = 0
        node.depth = 0

    for node in graph.nodes:
        if node.color == white:
            max_cycle_length = max(max_cycle_length, dfs_visit(node))

    return max_cycle_length

dfs_visit(node):
    cycle_length = 0

    time += 1
    node.color = gray
    node.distance = time

    for adj_node in node.adj:
        if adj_node.color == gray:
            cycle_length = node.depth - adj_node.depth + 1
        else if adj_node.color == white:
            adj_node.depth = node.depth + 1
            adj_node.predecessor = node

    node.color = black
    time += 1
    node.end_visit = time

    return cycle_length
```
