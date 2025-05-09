# DFS (Depth-First-Search) visit with Strongly Connected Components (SCC)

## Input parameters

- `graph`: graph from which apply the visit

## Output

Graph SCC

## Pseudo-code

### Assignment

Dato un grafo G = (V,E) si scriva in pseudo-codice un algoritmo che calcoli le componenti
fortemente connesse del grafo. Si descriva lo pseudo-codice di ogni funzione richiamata

```
time = 0

dfs (graph):                                        // DFS function that computes strongly connected components
    stack = ∅                                       // Initialize a new stack to store nodes

    for node in graph.nodes:                        // Iterate over all nodes in the graph
        node.predecessor = NIL                           // Set the predecessor of each node to NIL
        node.distance = 0                           // Initialize discovery time to 0
        node.color = white                          // Set all nodes as unvisited (white)

    for node in graph.nodes:                        // Iterate again over all nodes
        if node.color == white:                     // If the node is unvisited
            dfs_visit_1(node, stack)                // Perform DFS visit on node, pushing results to stack

    t_graph = create_t_graph()                      // Create the transposed graph (reverse edges)

    scc_list = []
    while stack != ∅:                               // While stack is not empty
        scc = ∅                                     // current SCC
        node = stack.pop()                          // Pop a node from the stack

        if node.color == white:                     // If the node is unvisited in the transposed graph
            dfs_visit_2(node, t_graph, scc)         // Perform DFS visit on the node in the transposed graph
            scc_list = scc_list ∪ scc

    return scc_list


dfs_visit_1(node, stack):                           // DFS visit function for the original graph
    node.color = gray;                              // Mark the node as visited (gray)
    node.distance = time + 1                        // Set the discovery time of the node

    for adj_node in node.adj:                       // Iterate over the adjacent nodes of the current node
        if adj_node.color == white:                 // If the adjacent node is unvisited
            adj_node.predecessor = node             // Set the predecessor of the adjacent node to the current node
            dfs_visit_1(adj_node, stack)            // Recursively call dfs_visit_1 on the adjacent node

    node.color = black                              // Mark the node as fully processed (black)
    node.f = time + 1                               // Set the finish time of the node

    stack.push(node);                               // Push the node to the stack after visiting all its adjacent nodes


dfs_visit_2(node, t_graph, scc):                    // DFS visit function for the transposed graph
    node.color = gray                               // Mark the node as visited (gray)
    scc = scc ∪ node
    node.distance = time + 1                        // Set the discovery time of the node

    for t_adj_node in node.adj:                     // Iterate over the adjacent nodes in the transposed graph
        if t_adj_node.color == white:               // If the adjacent node is unvisited
            t_adj_node.predecessor = node           // Set the predecessor of the adjacent node to the current node
            dfs_visit_2(t_adj_node, t_graph, scc)   // Recursively call dfs_visit_2 on the adjacent node

    node.f = time + 1                               // Set the finish time of the node
    node.color = black                              // Mark the node as fully processed (black)
```

### _Notes_

- `scc_list`: all SCC
- `scc`: representing the current strongly connected component
  being constructed. Nodes added to this list are part of
  the same SCC
- `t_graph`: transposed graph (graph with reversed edges)
