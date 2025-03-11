class Node:  
    def __init__(self, symbol: str = None, frequency: int = 0, left_child: "Node" = None, right_child: "Node" = None, combined: bool = False):
        self.symbol = symbol
        self.frequency = frequency
        self.left_child = left_child
        self.right_child = right_child
        self.combined = combined
    
    def __str__(self, level=0): 
        indent = "  " * level
        left = f"\n{indent}├─ Left: {self.left_child.__str__(level + 1)}" if self.left_child else ""
        right = f"\n{indent}└─ Right: {self.right_child.__str__(level + 1)}" if self.right_child else ""
        
        return f"{indent} {f"symbol: {self.symbol} - " if self.symbol else ''}frequency: {self.frequency} {left} {right}"

  
    def __lt__(self, other: "Node"):
        """First compare by frequency, then by combined flag (favoring combined=True)"""
        if not isinstance(other, Node):
            return NotImplemented
        return (self.frequency, not self.combined) < (other.frequency, not other.combined)