class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int count[10] = {};

        for (int x : digits)
            count[x]++;

        int ans = 0;

        for (int num = 100; num <= 998; num++) {
            if (num % 2 != 0)
                continue;

            int a = num / 100;
            int b = (num / 10) % 10;
            int c = num % 10;

            if (a == b && b == c) {
                if (count[a] >= 3)
                    ans++;
            }
            else if (a == b) {
                if (count[a] >= 2 && count[c] >= 1)
                    ans++;
            }
            else if (a == c) {
                if (count[a] >= 2 && count[b] >= 1)
                    ans++;
            }
            else if (b == c) {
                if (count[b] >= 2 && count[a] >= 1)
                    ans++;
            }
            else {
                if (count[a] >= 1 && count[b] >= 1 && count[c] >= 1)
                    ans++;
            }
        }

        return ans;
    }
};