from node import Node
from graph import Graph
import random
import mst

a = Node("A")
b = Node("B")
c = Node("C")
d = Node("D")
e = Node("E")
f = Node("F")
g = Node("G")

nodes = [a, b, c, d, e, f, g]

edges = [
    (a, d, random.randint(1, 10)),
    (a, b, random.randint(1, 10)),
    (b, c, random.randint(1, 10)),
    (b, d, random.randint(1, 10)),
    (b, e, random.randint(1, 10)),
    (c, e, random.randint(1, 10)),
    (d, e, random.randint(1, 10)),
    (d, f, random.randint(1, 10)),
    (e, f, random.randint(1, 10)),
    (e, g, random.randint(1, 10)),
    (f, g, random.randint(1, 10))
]


adjacency_list = {
    a: [(b, 1), (d, 1)],
    b: [(a, 1), (c, 1), (d, 1), (e, 1)],
    c: [(b, 1), (e, 1)],
    d: [(a, 1), (b, 1), (e, 1), (f, 1)],
    e: [(b, 1), (c, 1), (d, 1), (f, 1), (g, 1)],
    f: [(d, 1), (e, 1), (g, 1)],
    g: [(e, 1), (f, 1)],
}

for node in nodes:
    node.adjacency_list = adjacency_list[node]

graph = Graph(nodes, edges)
graph.dfs()
# graph.bfs(c)

for node in graph.nodes:
    print(f"{node.name}: {node.distance} - {node.end_visit}")

print("\n")
mst.print_mst(mst.kruskal(graph))
