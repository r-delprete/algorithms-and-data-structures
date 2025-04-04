import heapq
from typing import List, Tuple
from node import Node
from edge import Edge
from graph import Graph


def __make_set(node: Node):
    node.parent = node
    node.rank = 0


def __find_set(node: Node) -> Node:
    if node.parent != node:
        node.parent = __find_set(node.parent)
    return node.parent


def __union(node1: Node, node2: Node):
    root1 = __find_set(node1)
    root2 = __find_set(node2)

    if root1 != root2:
        if root1.rank < root2.rank:
            root1.parent = root2
        elif root2.rank < root1.rank:
            root2.parent = root1
        elif root1.rank == root2.rank:
            root2.parent = root1
            root1.rank += 1


def kruskal(graph: Graph):
    """ 
    Function to execute Kruskal algorithm to build Minimum Spanning Tree

    Parameters
    ----------
    graph : Graph
        The graph

    Return
    ------
    Minimum Spanning Tree builded
    """
    mst: List[Edge] = []

    for node in graph.nodes:
        __make_set(node)

    # sort edges by weight
    sorted_edges = sorted(graph.edges, key=lambda edge: edge.weight)

    for edge in sorted_edges:
        if __find_set(edge.source_node) != __find_set(edge.destination_node):
            mst.append(edge)
            __union(edge.source_node, edge.destination_node)

    return mst


def prim(graph: Graph, source_node: Node):
    for node in graph.nodes:
        node.key = float('inf')
        node.predecessor = None

    source_node.key = 0

    min_priority_queue: List[Node] = []

    for node in graph.nodes:
        heapq.heappush(min_priority_queue, node)

    while min_priority_queue:
        node = heapq.heappop(min_priority_queue)

        for adj_node in node.adjacency_list:
            edge = graph.find_edge(node, adj_node)

            if adj_node in min_priority_queue and edge and edge.weight < adj_node.key:
                adj_node.predecessor = node
                adj_node.key = edge.weight

                min_priority_queue.remove(adj_node)
                heapq.heappush(min_priority_queue, adj_node)

    mst: List[Edge] = []
    for node in graph.nodes:
        if node.predecessor:
            mst.append(Edge(node.predecessor, node, node.key))

    return mst


def print_mst(mst: List[Edge]):
    print("Minimum Spanning Tree (MST):")
    for edge in mst:
        print(
            f"{edge.source_node.name} --({edge.weight})--> {edge.destination_node.name}")
