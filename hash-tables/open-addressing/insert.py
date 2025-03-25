def insert(hash_table, element, size):
    i = 0
    while i < size:
        index = hash_function(element, i) # type: ignore
        if hash_table[index] == None or hash_table[index] == '#':
            hash_table[index] = element
            return index
        elif hash_table[index] == element:    # if element already exists
            return -1
        else:
            i += 1
            
    return 'overflow'
      
      