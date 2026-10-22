class Solution {
public:
    int minOperations(string s) {
        int n = s.size();

        if (is_sorted(s.begin(), s.end()))
            return 0;

        if (n == 2)
            return -1;

        char mn = *min_element(s.begin(), s.end());
        char mx = *max_element(s.begin(), s.end());

        if (s[0] == mn || s[n - 1] == mx)
            return 1;

        int firstMin = s.find(mn);
        int lastMax = s.rfind(mx);

        if (firstMin == n - 1 && lastMax == 0)
            return 3;

        return 2;
    }
};