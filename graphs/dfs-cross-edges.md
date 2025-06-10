# Assignment description

Dato un grafo orientato $G = (V, E)$ ed un intero $K$ appartenente $R^+$
si scriva un algoritmo in pseudo-codice
che restituisca la lista degli archi trasversali del grafo

## Input parameters

- `graph`: graph from which apply the visit

## Output

Returns cross egdes list

## Pseudo-code

```
time = 0

dfs(graph, K):
    cross_edges = ∅

    for node in graph.nodes:
        node.predecessor = NIL
        node.distance = 0
        node.end_visit = 0
        node.color = white

    for node in graph.nodes:
        if node.color == white:
            dfs_visit(node, K, cross_edges)

    return cross_edges

dfs_visit(node, K, cross_edges):
    node.color = gray
    time += 1
    node.distance = time

    for adj_node in node.adj:
        if adj_node.color == white:
            adj_node.predecessor = node
            dfs_visit(adj_node, K)
        else if adj_node == black and node.distance > adj_node.distance:
            cross_edges <- cross_edges ∪ (node, adj_node)    // push edge into list

    time += 1
    node.end_visit = time
    node.color = black
```
