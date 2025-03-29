import heapq
from typing import List
from node import Node

class Min_Priority_Queue:
    def __init__(self, node_list: List[Node] = None):
        if node_list is not None:
            self._heap = [(node.frequency, not node.combined, node) for node in node_list]
            heapq.heapify(self._heap)
        else:
            self._heap = []
    
    def push(self, item: Node):
        """Adds an element to the queue"""
        heapq.heappush(self._heap, (item.frequency, not item.combined, item))
    
    def extract_min(self) -> Node:
        """Removes and returns the element with the minimum priority."""
        if self.is_empty():
            raise IndexError("The queue is empty")
        return heapq.heappop(self._heap)[2]
    
    def peek(self):
        """Returns the element with the minimum priority without removing it."""
        if self.is_empty():
            raise IndexError("The queue is empty")
        return self._heap[0][2]
    
    def is_empty(self):
        """Checks if the queue is empty."""
        return len(self._heap) == 0
    
    def size(self):
        """Returns the number of elements in the queue."""
        return len(self._heap)
    
    def __str__(self):
        """Returns a string representation of the priority queue."""
        return str(sorted(self._heap))
