from typing import List, Deque, Tuple
from enum import Enum
from node import Node, Color
from collections import deque

class EdgeTypes(Enum):
    forward = 'forward'
    backward = 'back'
    cross = 'cross'


class Graph:
    def __init__(self, nodes: List[Node], edges: List[Tuple[Node, Node, int]]):
        self.nodes = nodes
        self.time = 0
        self.loops = 0
        self.cycles = 0
        self.edges_type_count: dict[EdgeTypes, int] = {
            EdgeTypes.backward: 0,
            EdgeTypes.forward: 0,
            EdgeTypes.cross: 0
        }
        self.edges = edges
        
        
    def dfs(self):
      for node in self.nodes:
          node.color = Color.white
          node.distance = 0
          node.end_visit = 0
          node.predecessor = None
          
      for node in self.nodes:
          if node.color == Color.white:
              self.__dfs_visit(node)
          
    def __dfs_visit(self, node: Node):
        self.time += 1
        node.color = Color.gray
        node.distance = self.time
        
        for adj_node, weight in node.adjacency_list:
            if adj_node.color == Color.white:
                adj_node.predecessor = node
                self.__dfs_visit(adj_node)
            elif adj_node == node:
                self.loops += 1
            elif adj_node.color == Color.gray:
                self.edges_type_count[EdgeTypes.backward] += 1
                self.cycles += 1
            elif adj_node.color == Color.black:
                if node.distance < adj_node.distance:
                    self.edges_type_count[EdgeTypes.forward] += 1
                elif node.distance > adj_node.distance:
                    self.edges_type_count[EdgeTypes.cross] += 1
        
        self.time += 1
        node.end_visit = self.time
        node.color = Color.black
        
    def bfs(self, source_node: Node):      
        for node in self.nodes:
            node.color = Color.white
            node.distance = 0
            node.predecessor = None
        
        source_node.color = Color.gray
        source_node.distance = 0
        source_node.predecessor = None
        
        queue: Deque[Node] = deque()
        queue.append(source_node)
        
        while queue:
            node = queue.popleft()
            
            for adj_node, weight in node.adjacency_list:
                if adj_node.color == Color.white:
                    adj_node.predecessor = node
                    adj_node.color = Color.gray
                    adj_node.distance = node.distance + 1
                    queue.append(adj_node)
                    
            node.color = Color.black
