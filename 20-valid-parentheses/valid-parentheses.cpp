#include <iostream>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;

        for (char ch : s) {
            // Opening brackets
            if (ch == '(' || ch == '[' || ch == '{') {
                st.push(ch);
            }
            // Closing brackets
            else {
                if (st.empty())
                    return false;

                char top = st.top();
                st.pop();

                if ((ch == ')' && top != '(') ||
                    (ch == ']' && top != '[') ||
                    (ch == '}' && top != '{')) {
                    return false;
                }
            }
        }

        return st.empty();
    }
};