def F(x, y, memo):
    """ Algorithm to calculate F(x,y) = max { F(x - 1,y - 1) + 1, F(x - 1, y),F(x, y - 1) } """
    if x == 0 or y == 0:
        return 0
      
    if memo[x][y] != -1:
        return memo[x][y]
      
    val1 = F(x - 1, y - 1, memo) + 1
    val2 = F(x - 1, y)
    val3 = F(x, y - 1)
    
    result = max(val1, val2, val3)
    
    memo[x][y] = result
    
    return memo[x][y]
      