def delete(hash_table, element, size):
    """ 
    Function to delete an item in a hash table.
      
    In the hash table, the element's index will be marked as deleted with '#'.
    """
    i = 0
    index = hash_function(element, i) # type: ignore
    
    while hash_table[index] != None and i < size:
        if hash_table[index] != '#' and hash_table[index].key == element:
            hash_table[index] = '#'   # mark as deleted
            return f'element {element} deleted'
        i += 1
        index = hash_function(element, i) # type: ignore
    
    return f'element {element} not found'