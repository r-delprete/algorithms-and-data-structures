# Bellman-Ford algorithm

**Bellman-Ford** finds the shortest path from a source node to all other nodes in a weighted graph with non-negative and negative edge weights

## Input parameters

- `graph`: graph from which the shortest paths are computed
- `source`: source node from which the shortest paths are computed
- `weights`: nodes weights

## Output

Returns:

- `true` if there are no negative-weight cycles reachable from the source node. In this case, the algorithm successfully computes the shortest paths.

- `false` if a negative-weight cycle is detected. This indicates the presence of paths with indefinitely decreasing cost, making shortest paths undefined.

## Pseudo-code

```
bellman_ford(graph, source, weights):
    initialize_single_source(graph, source):

    for i = 1 to |graph.nodes| - 1:
        for (node1, node2) in graph.edges:
            relax(node1, node2, weights)

    for (node1, node2) in graph.edges:
        if node2.d > node1.d + weights(node1, node2):
            return false

    return true
```

## `initialize_single_source` and `relax` functions

### `initialize_single_source`

This function initializes the distances and predecessors for all nodes in the graph, setting the source node’s distance to 0 and all other nodes' distances to infinity. It also sets the predecessor of the source node to NIL and all other nodes' predecessors to NIL.

#### Input parameters

- `graph`: the graph to initialize
- `source`: the source node from which distances are computed

#### Pseudo-code

```
initialize_single_source(graph, source):
    for node in (graph.nodes - source):
        node.predecessor = NIL
        node.d = inf

    source.predecessor = NIL
    source.d = 0
```

### `relax`

This function attempts to update the distance of `node2` using the distance of `node1` and the weight of the edge between them. If the new distance through `node1` is smaller than the current distance of `node2`, it updates the distance and sets `node1` as the predecessor of `node2`.

#### Input parameters

- `node1`: source edge node
- `node2`: destination edge node
- `weights`: edges weights

#### Pseudo-code

```
relax(node1, node2, weights):
    if node2.d > node1.d + weights(node1, node2)
        node2.d = node1.d + weights(node1, node2)
        node2.predecessor = node1
```
