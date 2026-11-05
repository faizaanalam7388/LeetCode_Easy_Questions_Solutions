class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> low, high;
        long long sumLow = 0, sumHigh = 0;

        // Balance the two halves
        auto balance = [&]() {
            while (low.size() > high.size() + 1) {
                auto it = prev(low.end());
                int v = *it;

                low.erase(it);
                sumLow -= v;

                high.insert(v);
                sumHigh += v;
            }

            while (low.size() < high.size()) {
                int v = *high.begin();

                high.erase(high.begin());
                sumHigh -= v;

                low.insert(v);
                sumLow += v;
            }
        };

        // Insert an element
        auto add = [&](int v) {
            if (low.empty() || v <= *prev(low.end())) {
                low.insert(v);
                sumLow += v;
            } else {
                high.insert(v);
                sumHigh += v;
            }
            balance();
        };

        // Remove an element
        auto remove = [&](int v) {
            auto it = low.find(v);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= v;
            } else {
                it = high.find(v);
                high.erase(it);
                sumHigh -= v;
            }

            balance();
        };

        // Calculate cost for every window of size x
        vector<long long> cost(n - x + 1);

        for (int i = 0; i < x; i++)
            add(nums[i]);

        for (int i = 0; i + x <= n; i++) {
            long long med = *prev(low.end());

            cost[i] = med * (long long)low.size() - sumLow
                    + sumHigh - med * (long long)high.size();

            if (i + x < n) {
                remove(nums[i]);
                add(nums[i + x]);
            }
        }

        // DP: minimum cost for choosing k non-overlapping windows
        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        for (int i = 0; i <= n; i++)
            dp[0][i] = 0;

        for (int t = 1; t <= k; t++) {
            for (int i = 1; i <= n; i++) {
                // Skip current position
                dp[t][i] = dp[t][i - 1];

                // Select the window ending at i - 1
                if (i >= x && dp[t - 1][i - x] != INF) {
                    dp[t][i] = min(
                        dp[t][i],
                        dp[t - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
    }
};