def search(hash_table, element, size):
    """ Function to search an element into an hash table """
    i = 0
    while i < size:
        index = hash_function(element, i) # type: ignore
        if hash_table[index] == element:
            return index
        elif hash_table[index] == None:
            return -1   # key not exists into bucket
        else:
            i += 1
            
    return -1   # key not found