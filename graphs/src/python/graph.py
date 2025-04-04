from typing import List, Deque, Optional, Tuple
from node import Node, Color
from collections import deque
from edge import Edge, EdgeType


class Graph:
    def __init__(self, nodes: List[Node], edges: List[Edge]):
        self.nodes = nodes
        self.time = 0
        self.loops = 0
        self.cycles = 0
        self.edges_type_count: dict[EdgeType, int] = {
            EdgeType.backward: 0,
            EdgeType.forward: 0,
            EdgeType.cross: 0
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

        for adj_node in node.adjacency_list:
            edge = self.find_edge(node, adj_node)

            if adj_node.color == Color.white:
                adj_node.predecessor = node
                self.__dfs_visit(adj_node)
            elif adj_node == node:
                self.loops += 1
            elif adj_node.color == Color.gray:
                self.edges_type_count[EdgeType.backward] += 1
                if edge:
                    edge.type = EdgeType.backward

                self.cycles += 1
            elif adj_node.color == Color.black:
                if node.distance < adj_node.distance:
                    self.edges_type_count[EdgeType.forward] += 1

                    if edge:
                        edge.type = EdgeType.forward
                elif node.distance > adj_node.distance:
                    self.edges_type_count[EdgeType.cross] += 1

                    if edge:
                        edge.type = EdgeType.cross

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

            for adj_node in node.adjacency_list:
                if adj_node.color == Color.white:
                    adj_node.predecessor = node
                    adj_node.color = Color.gray
                    adj_node.distance = node.distance + 1
                    queue.append(adj_node)

            node.color = Color.black

    def find_edge(self, source_node: Node, destitation_node: Node) -> Optional[Edge]:
        for edge in self.edges:
            if edge.source_node == source_node and edge.destination_node == destitation_node:
                return edge
        return None
