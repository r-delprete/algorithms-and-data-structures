from node import Node
from graph import Graph
from edge import Edge
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
    Edge(a, d, random.randint(1, 10)),
    Edge(a, b, random.randint(1, 10)),
    Edge(b, c, random.randint(1, 10)),
    Edge(b, d, random.randint(1, 10)),
    Edge(b, e, random.randint(1, 10)),
    Edge(c, e, random.randint(1, 10)),
    Edge(d, e, random.randint(1, 10)),
    Edge(d, f, random.randint(1, 10)),
    Edge(e, f, random.randint(1, 10)),
    Edge(e, g, random.randint(1, 10)),
    Edge(f, g, random.randint(1, 10))
]


adjacency_list = {
    a: [b, d],
    b: [a, c, d, e],
    c: [b, e],
    d: [a, b, e, f],
    e: [b, c, d, f, g],
    f: [d, e, g],
    g: [e, f],
}

for node in nodes:
    node.adjacency_list = adjacency_list[node]

graph = Graph(nodes, edges)
graph.dfs()
# graph.bfs(c)

for node in graph.nodes:
    print(f"{node.name}: {node.distance} - {node.end_visit}")

print("\n")
mst.print_mst(mst.prim(graph, a))
