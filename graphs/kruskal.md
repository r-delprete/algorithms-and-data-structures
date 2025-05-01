# Kruskal algorithm

## Input parameters

- `graph`: graph from which the MST is to be computed

## Output

Returns the _MST (Minimum Spanning Tree)_ builded

## Pseudo-code

```
kruskal(graph):
    mst = empty_set

    for node in graph.nodes:
        make_set(node)

    sorted_edges = sort(graph.edges)        // sort edges by weight in not-decrescent order

    for (node1, node2) in sorted_edges
        if find_set(node1) != find_set(node2)
            union(node1, node2)
            mst.add((node1, node2))         // add (node1, node2) edge to mst

    return mst
```

## `make_node`, `find_set` and `union` functions

### `make_set`

This function create a disjoint set with input node included (_singleton_)

#### Input parameters

- `node`: element which create the disjoint set

```
make_set(node):
    node.parent = node
    node.rank = 0
```

### `find_set`

This function find the input node set representative

#### Input parameters

- `node`: node to apply the find_set

#### Output

- Returns the input node set representative

#### Pseudo-code

```
find_set(node):
    if node != node.predecessor
        node.predecessor = find_set(node.predecessor)       // path compression

    return node.predecessor
```

### `union`

This function takes as input two elements, possibly from different sets. It determines the representative (or root) of the set each element belongs to, and if the representatives are different, it merges the two sets into a single one.

#### Input parameters

- `node1`: first element
- `node2`: second element

#### Pseudo-code

```
union(node1, node2):
    root1 = find_set(node1)
    root2 = find_set(node2)

    if root1 != root2:
        if root1.rank < root2.rank:
            root1.predecessor = root2    // join root1 under root2
        else if root2.rank < root1.rank:
            root2.predecessor = root1    // join root2 under root1
        else if root1.rank == root2.rank:
            root2.predecessor = root1    // join root2 under root1
            root1.rank += 1              // increase root1 rank
```
