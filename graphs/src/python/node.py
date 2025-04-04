from enum import Enum
from typing import Dict, List, Optional, Tuple


class Color(Enum):
    white = "white"
    black = "black"
    gray = "gray"


class Node:
    def __init__(
        self,
        name: str,
        color: Color = Color.white,
        predecessor: Optional["Node"] = None,
        start_visit: int = 0,
        end_visit: int = 0,
        adjacency_list: List["Node"] = [],
        parent: Optional["Node"] = None,
        rank: int = 0,
        key: int = 0
    ):
        self.name = name
        self.color = color
        self.predecessor = predecessor
        self.distance = start_visit
        self.end_visit = end_visit
        self.adjacency_list = adjacency_list
        self.parent = parent
        self.rank = rank
        self.key = key

    def __repr__(self):
        return f"Node({self.name})"

    def __lt__(self, other: "Node"):
        return self.key < other.key
