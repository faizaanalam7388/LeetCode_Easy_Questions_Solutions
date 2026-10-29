class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        int LOG = 1;
        while ((1 << LOG) <= n) LOG++;

        vector<int> tin(n), tout(n), depth(n), parent(n), pref(n);
        vector<vector<int>> up(LOG, vector<int>(n));
        int timer = 0;

        // Iterative DFS to avoid deep recursion
        stack<tuple<int, int, bool>> st;
        st.push({0, -1, false});

        while (!st.empty()) {
            auto [u, p, exit] = st.top();
            st.pop();

            if (exit) {
                tout[u] = timer;
                continue;
            }

            parent[u] = (p == -1 ? u : p);
            depth[u] = (p == -1 ? 0 : depth[p] + 1);
            tin[u] = ++timer;

            int mask = 1 << (s[u] - 'a');
            pref[u] = (p == -1 ? 0 : pref[p]) ^ mask;

            st.push({u, p, true});

            for (int v : adj[u]) {
                if (v != p)
                    st.push({v, u, false});
            }
        }

        for (int i = 0; i < n; i++)
            up[0][i] = parent[i];

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++)
                up[j][i] = up[j - 1][up[j - 1][i]];
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++)
                if (diff & (1 << j))
                    u = up[j][u];

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return parent[u];
        };

        // Fenwick Tree supporting range XOR updates
        vector<int> bit(n + 2, 0);

        auto update = [&](int i, int val) {
            for (; i <= n + 1; i += i & -i)
                bit[i] ^= val;
        };

        auto rangeXor = [&](int l, int r, int val) {
            update(l, val);
            update(r + 1, val);
        };

        auto get = [&](int i) {
            int result = 0;
            for (; i > 0; i -= i & -i)
                result ^= bit[i];
            return result;
        };

        vector<bool> ans;

        for (string q : queries) {
            string type, a, b;
            stringstream ss(q);
            ss >> type >> a >> b;

            int u = stoi(a);

            if (type == "update") {
                char c = b[0];

                int oldMask = 1 << (s[u] - 'a');
                int newMask = 1 << (c - 'a');
                int delta = oldMask ^ newMask;

                rangeXor(tin[u], tout[u], delta);
                s[u] = c;
            } else {
                int v = stoi(b);
                int l = lca(u, v);

                int maskU = pref[u] ^ get(tin[u]);
                int maskV = pref[v] ^ get(tin[v]);

                int mask = maskU ^ maskV ^ (1 << (s[l] - 'a'));

                ans.push_back(__builtin_popcount(mask) <= 1);
            }
        }

        return ans;
    }
};