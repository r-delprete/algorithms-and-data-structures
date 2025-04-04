from node import Node
from enum import Enum


class EdgeType(Enum):
    forward = 'forward'
    backward = 'back'
    cross = 'cross'


class Edge:
    def __init__(self, source_node: Node, destination_node: Node, weight: int, type: EdgeType = None):
        self.source_node = source_node
        self.destination_node = destination_node
        self.weight = weight
        self.type = type
