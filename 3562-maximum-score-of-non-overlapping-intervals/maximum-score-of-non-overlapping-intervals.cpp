class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(a.begin(), a.end());

        // dp[i][k] = best answer from i onward using at most k intervals
        vector<vector<pair<long long, vector<int>>>> dp(
            n + 1, vector<pair<long long, vector<int>>>(5)
        );

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {

                // Don't take current interval
                dp[i][k] = dp[i + 1][k];

                // Find next non-overlapping interval
                int lo = i + 1;
                int hi = n;

                while (lo < hi) {
                    int mid = (lo + hi) / 2;

                    if (a[mid][0] > a[i][1])
                        hi = mid;
                    else
                        lo = mid + 1;
                }

                int next = lo;

                // Take current interval
                vector<int> take = dp[next][k - 1].second;
                take.push_back((int)a[i][3]);

                sort(take.begin(), take.end());

                long long score =
                    a[i][2] + dp[next][k - 1].first;

                // Better score
                if (score > dp[i][k].first) {
                    dp[i][k] = {score, take};
                }

                // Same score → lexicographically smaller
                else if (score == dp[i][k].first) {

                    if (take < dp[i][k].second) {
                        dp[i][k].second = take;
                    }
                }
            }
        }

        return dp[0][4].second;
    }
};