class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);

        for (char c : s) {

            if (c == '(') {
                st.push(0);
            }
            else {
                int inside = st.top();
                st.pop();

                if (inside == 0)
                    st.top() += 1;
                else
                    st.top() += 2 * inside;
            }
        }

        return st.top();
    }
};