#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::string lcs(const std::string& first_string, const std::string& second_string) {
  int m = first_string.length();
  int n = second_string.length();

  std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

  // Fill dp table
  for (int i = 1; i <= m; ++i) {
    for (int j = 1; j <= n; ++j) {
      if (first_string[i - 1] == second_string[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  // Backtrack to find LCS sequence
  std::string lcs_seq;
  int i = m, j = n;
  while (i > 0 && j > 0) {
    if (first_string[i - 1] == second_string[j - 1]) {
      lcs_seq += first_string[i - 1];
      --i;
      --j;
    } else if (dp[i - 1][j] > dp[i][j - 1]) {
      --i;
    } else {
      --j;
    }
  }

  std::reverse(lcs_seq.begin(), lcs_seq.end());
  return lcs_seq;
}

int main() {
  std::string X = "ALBERO";
  std::string Y = "TABELLA";

  std::string result = lcs(X, Y);
  std::cout << "LCS: " << result << std::endl;

  return 0;
}
