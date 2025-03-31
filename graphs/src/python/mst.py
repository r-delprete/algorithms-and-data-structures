import heapq
from typing import List, Tuple
from node import Node
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
    mst: List[Tuple[Node, Node, int]] = []
    
    for node in graph.nodes:
        __make_set(node)
        
    sorted_edges = sorted(graph.edges, key=lambda edge: edge[2])
    
    for node1, node2, weight in sorted_edges:
        if __find_set(node1) != __find_set(node2):
            mst.append((node1, node2, weight))
            __union(node1, node2)
        
    return mst
            
def prim(graph: Graph, source_node: Node):
    for node in graph.nodes:
        node.key = 0
        node.predecessor = None
        
    source_node.key = 0
    
    min_priority_queue: List[Node] = []
    
    for node in graph.nodes:
        heapq.heappush(min_priority_queue, node)
        
    while min_priority_queue:
        node = heapq.heappop(min_priority_queue)
        
        for adj_node, weight in node.adjacency_list:
            if adj_node in min_priority_queue and weight < adj_node.key:
                adj_node.predecessor = node
                adj_node.key = weight
                
                min_priority_queue.remove((adj_node.key, adj_node))
                heapq.heappush(min_priority_queue, (adj_node.key, adj_node))
    
    mst: List[Tuple[Node, Node, int]] = []
    for node in graph.nodes:
        if node.predecessor:
            mst.append((node.predecessor, node, node.key))
    
    return mst

def print_mst(mst: List[Tuple[Node, Node, int]]):
        print("Minimum Spanning Tree (MST):")
        for node1, node2, weight in mst:
            print(f"{node1.name} --({weight})--> {node2.name}")