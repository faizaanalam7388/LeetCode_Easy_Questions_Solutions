class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        vector<int> order(n), rank(n);

        iota(order.begin(), order.end(), 0);

        sort(order.begin(), order.end(), [&](int a, int b) {
            if (nums[a] != nums[b])
                return nums[a] < nums[b];
            return a < b;
        });

        for (int i = 0; i < n; i++)
            rank[order[i]] = i;

        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0) continue;

            bool ok = true;

            for (int s = 0; s < n && ok; s += k) {
                int drops = (nums[s + k - 1] > nums[s]);

                for (int i = s; i < s + k; i++) {
                    if (rank[i] / k != s / k) {
                        ok = false;
                        break;
                    }

                    if (i + 1 < s + k && nums[i] > nums[i + 1])
                        drops++;
                }

                if (drops > 1)
                    ok = false;
            }

            if (ok)
                ans += k;
        }

        return ans;
    }
};