from typing import List, Deque
from enum import Enum
from node import Node, Color
from collections import deque

class EdgeTypes(Enum):
    forward = 'forward'
    back = 'back'
    cross = 'cross'


class Graph:
    def __init__(self, nodes: List[Node]):
        self.nodes = nodes
        self.time = 0
        self.loops = 0
        self.cycles = 0
        self.edges_type_count: dict[EdgeTypes, int] = {
            EdgeTypes.back: 0,
            EdgeTypes.forward: 0,
            EdgeTypes.cross: 0
        }
        
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
        
        for vicinity_node in node.vicinity_list:
            if vicinity_node.color == Color.white:
                vicinity_node.predecessor = node
                self.dfs_visit(vicinity_node)
            elif vicinity_node == node:
                self.loops += 1
            elif vicinity_node.color == Color.gray:
                self.edges_type_count[EdgeTypes.back] += 1
                self.cycles += 1
            elif vicinity_node.color == Color.black:
                if node.start_visit < vicinity_node.start_visit:
                    self.edges_type_count[EdgeTypes.forward] += 1
                elif node.start_visit > vicinity_node.start_visit and node.end_visit > vicinity_node.end_visit:
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
            
            for vicinity_node in node.vicinity_list:
                if vicinity_node.color == Color.white:
                    vicinity_node.predecessor = node
                    vicinity_node.color = Color.gray
                    vicinity_node.start_visit = node.start_visit + 1
                    queue.append(vicinity_node)
                    
            node.color = Color.black
      
node1 = Node(color=Color.white, predecessor=None, start_visit=0, end_visit=0, vicinity_list=[])
node2 = Node(color=Color.white, predecessor=None, start_visit=0, end_visit=0, vicinity_list=[])
node3 = Node(color=Color.white, predecessor=None, start_visit=0, end_visit=0, vicinity_list=[])
node4 = Node(color=Color.white, predecessor=None, start_visit=0, end_visit=0, vicinity_list=[])

# Set the connections (vicinity)
node1.vicinity_list = [node2, node3, node1]  # Node1 is connected to Node2 and Node3
node2.vicinity_list = [node1, node4]  # Node2 is connected to Node1 and Node4
node3.vicinity_list = [node1]        # Node3 is connected to Node1
node4.vicinity_list = [node2]        # Node4 is connected to Node2

# node1.vicinity_list = [node2]
# node2.vicinity_list = [node3]
# node3.vicinity_list = [node4]
# node4.vicinity_list = [node2]

graph = Graph(nodes=[node1, node2, node3, node4])

graph.dfs()
# graph.bfs(node1)

for node in graph.nodes:
    print(f"Node {node}: {node.color}, {node.start_visit}, {node.end_visit}")
    
print(f"Loops: {graph.loops}")
print(f"Cycles: {graph.cycles}")

for type in EdgeTypes:
    print(f"{type.name.capitalize()}: {graph.edges_type_count[type]}")
