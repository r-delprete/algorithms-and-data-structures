from typing import List

def lcs(first_string, second_string):
  m = len(first_string)
  n = len(second_string)
  dp = [[0] * (n + 1) for _ in range(m + 1)]

  for i in range(1, m + 1):
    for j in range(1, n + 1):
      if first_string[i - 1] == second_string[j - 1]:
        dp[i][j] = dp[i - 1][j - 1] + 1
      else:
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

  lcs_seq: List[str] = []
  i, j = m, n
  while i > 0 and j > 0:
    if first_string[i - 1] == second_string[j - 1]:
      lcs_seq.append(first_string[i - 1])
      i -= 1
      j -= 1
    elif dp[i - 1][j] > dp[i][j - 1]:
      i -= 1
    else:
      j -= 1
  
  return "".join(reversed(lcs_seq))

X = "ALBERO"
Y = "TABELLA"
print("LCS:", lcs(X, Y))
