class Solution {
public:
    int uniquePaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size(), n = grid[0].size();

        vector<vector<array<int, 2>>> dp(
            m, vector<array<int, 2>>(n, {0, 0})
        );

        // Starting position
        dp[0][0][0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                int right = dp[i][j][0];
                int down = dp[i][j][1];

                if (grid[i][j] == 0) {
                    int total = (right + down) % MOD;

                    // Move right
                    if (j + 1 < n)
                        dp[i][j + 1][0] =
                            (dp[i][j + 1][0] + total) % MOD;

                    // Move down
                    if (i + 1 < m)
                        dp[i + 1][j][1] =
                            (dp[i + 1][j][1] + total) % MOD;
                }
                else {
                    // Mirror: right becomes down
                    if (i + 1 < m)
                        dp[i + 1][j][1] =
                            (dp[i + 1][j][1] + right) % MOD;

                    // Mirror: down becomes right
                    if (j + 1 < n)
                        dp[i][j + 1][0] =
                            (dp[i][j + 1][0] + down) % MOD;
                }
            }
        }

        return (dp[m - 1][n - 1][0] +
                dp[m - 1][n - 1][1]) % MOD;
    }
};