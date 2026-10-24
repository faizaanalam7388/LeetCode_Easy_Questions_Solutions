class Solution {
public:
    int countDaysTogether(string a, string b, string c, string d) {
        int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};

        auto convert = [&](string s) {
            int m = stoi(s.substr(0, 2));
            int day = stoi(s.substr(3, 2));

            for (int i = 0; i < m - 1; i++)
                day += days[i];

            return day;
        };

        int start = max(convert(a), convert(c));
        int end = min(convert(b), convert(d));

        return max(0, end - start + 1);
    }
};