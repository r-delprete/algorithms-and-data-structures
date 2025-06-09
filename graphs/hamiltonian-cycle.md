# Hamiltonian cycle

Dato un grafo non orientato $G(V, E)$, implementare in pseudo-codice un algoritmo ricorsivo
che restituisca `true` se in $G$ è presente un ciclo Hamiltoniano e `false` altrimenti.

## Input parameters

- `graph`: graph from which the hamiltonian cycle needs to be computed

# Output

Returns `true` if in input graph there's an Hamiltonian cycle, `false` otherwise.

## Pseudo-code

```
hamiltonian_cycle(graph):
    path = ∅

    for node in graph.nodes:
        path = path ∪ node

        if recursive_hamiltonian_cycle(graph, path, node):
            return true

        path.pop_last()   // Backtracking: delete last element in list

    return false

recursive_hamiltonian_cycle(graph, path, current_node):
    if length(path) = length(graph.nodes):    // if path contains all graph vertices, it verifies if cycle can be closed
        first = path[0]

        if (current_node, first) ∈ graph.edges:
            return true     // Hamiltonian cycle

        return false

    // Recursion: explore not visited adjacent nodes
    for adj_node in current_node.adj:
        if adj_node ∉ path:
            path = path ∪ adj_node

            if recursive_hamiltonian_cycle(graph, path, adj_node):
                return true

            path.pop_last()   // Backtracking: delete last element in list

    return false    // if no valid path found
```
