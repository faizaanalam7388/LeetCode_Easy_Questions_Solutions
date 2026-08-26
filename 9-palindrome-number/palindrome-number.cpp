class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0)
            return false;

        int original = x;
        long long reverse = 0;

        for (; x > 0; x = x / 10) {
            int digit = x % 10;
            reverse = reverse * 10 + digit;
        }

        return original == reverse;
    }
};