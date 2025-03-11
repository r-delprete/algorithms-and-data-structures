from enum import Enum
from typing import List

class Color(Enum):
    white = "white"
    black = "black"
    gray = "gray"

class Node:
    def __init__(self, color: Color, predecessor: "Node", start_visit: int, end_visit: int, vicinity_list: List["Node"]):
        self.color = color
        self.predecessor = predecessor
        self.start_visit = start_visit
        self.end_visit = end_visit
        self.vicinity_list = vicinity_list