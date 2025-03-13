from typing import List, Deque, Tuple
from enum import Enum
from node import Node, Color
from collections import deque
import heapq

class EdgeTypes(Enum):
    forward = 'forward'
    back = 'back'
    cross = 'cross'


class Graph:
    def __init__(self, nodes: List[Node], edges: List[Tuple[Node, Node, int]]):
        self.nodes = nodes
        self.time = 0
        self.loops = 0
        self.cycles = 0
        self.edges_type_count: dict[EdgeTypes, int] = {
            EdgeTypes.back: 0,
            EdgeTypes.forward: 0,
            EdgeTypes.cross: 0
        }
        self.edges = edges
        
    def make_set(self, node: Node):
        node.parent = node
        node.rank = 0
    
    def find_set(self, node: Node) -> Node:
        if node.parent != node:
            node.parent = self.find_set(node.parent)
        return node.parent
    
    def union(self, node1: Node, node2: Node):
        root1 = self.find_set(node1)
        root2 = self.find_set(node2)
        
        if root1 != root2:
            if root1.rank < root2.rank:
                root1.parent = root2
            elif root2.rank < root1.rank:
                root2.parent = root1
            elif root1.rank == root2.rank:
                root2.parent = root1
                root1.rank += 1
    
    def kruskal(self):
        mst: List[Tuple[Node, Node, int]] = []
        
        for node in self.nodes:
            self.make_set(node)
            
        sorted_edges = sorted(self.edges, key=lambda edge: edge[2])
        
        for node1, node2, weight in sorted_edges:
            if self.find_set(node1) != self.find_set(node2):
                mst.append((node1, node2, weight))
                self.union(node1, node2)
            
        return mst
    
    def print_mst(self, mst: List[Tuple[Node, Node, int]]):
        print("Minimum Spanning Tree (MST):")
        for node1, node2, weight in mst:
            print(f"{node1.name} --({weight})--> {node2.name}")
            
    def prim(graph, source_node: Node):
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
        
        
    def dfs(self):
      for node in self.nodes:
          node.color = Color.white
          node.start_visit = 0
          node.end_visit = 0
          node.predecessor = None
          
      for node in self.nodes:
          if node.color == Color.white:
              self.dfs_visit(node)
          
    def dfs_visit(self, node: Node):
        self.time += 1
        node.color = Color.gray
        node.start_visit = self.time
        
        for adj_node, weight in node.adjacency_list:
            if adj_node.color == Color.white:
                adj_node.predecessor = node
                self.dfs_visit(adj_node)
            elif adj_node == node:
                self.loops += 1
            elif adj_node.color == Color.gray:
                self.edges_type_count[EdgeTypes.back] += 1
                self.cycles += 1
            elif adj_node.color == Color.black:
                if node.start_visit < adj_node.start_visit:
                    self.edges_type_count[EdgeTypes.forward] += 1
                elif node.start_visit > adj_node.start_visit and node.end_visit > adj_node.end_visit:
                    self.edges_type_count[EdgeTypes.cross] += 1
        
        self.time += 1
        node.end_visit = self.time
        node.color = Color.black
        
    def bfs(self, source_node: Node):      
        for node in self.nodes:
            node.color = Color.white
            node.start_visit = 0
            node.predecessor = None
        
        source_node.color = Color.white
        source_node.start_visit = 0
        source_node.predecessor = None
        
        queue: Deque[Node] = deque()
        queue.append(source_node)
        
        while queue:
            node = queue.popleft()
            
            for adj_node, weight in node.adjacency_list:
                if adj_node.color == Color.white:
                    adj_node.predecessor = node
                    adj_node.color = Color.gray
                    adj_node.start_visit = node.start_visit + 1
                    queue.append(adj_node)
                    
            node.color = Color.black
