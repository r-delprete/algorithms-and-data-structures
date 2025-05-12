from typing import List
from node import Node
from min_priority_queue import Min_Priority_Queue

def huffman(nodes: List[Node]) -> Node:
    queue = Min_Priority_Queue(nodes)
        
    while queue.size() > 1:
        new_node = Node(None, 0, None, None, True)
        
        new_node.left_child = queue.extract_min()
        new_node.right_child = queue.extract_min()
        
        new_node.frequency = new_node.left_child.frequency + new_node.right_child.frequency
        
        queue.push(new_node)
      
    return print(f"root: {queue.peek()}")
  
nodes = [
    Node("A", 5), 
    Node("B", 10), 
    Node("C", 15), 
    Node("D", 20), 
    Node("E", 25),
    Node("F", 25)
]
huffman(nodes)