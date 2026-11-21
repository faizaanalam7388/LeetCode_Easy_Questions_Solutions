#include <array>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        // 1. Build adjacency list for the original tree
        vector<vector<int>> orig_children(n);
        for (int i = 1; i < n; ++i) {
            orig_children[parent[i]].push_back(i);
        }

        vector<int> new_parent = parent;
        array<int, 26> last_seen;
        last_seen.fill(-1);

        // 2. DFS on the original tree to find closest matching ancestors
        auto find_new_parents = [&](auto& self, int u) -> void {
            int char_idx = s[u] - 'a';
            int prev_ancestor = last_seen[char_idx];

            if (prev_ancestor != -1) {
                new_parent[u] = prev_ancestor;
            }

            last_seen[char_idx] = u;
            for (int v : orig_children[u]) {
                self(self, v);
            }

            // Backtrack: restore the ancestor state before visiting u
            last_seen[char_idx] = prev_ancestor;
        };

        find_new_parents(find_new_parents, 0);

        // 3. Build adjacency list for the modified tree
        vector<vector<int>> new_children(n);
        for (int i = 1; i < n; ++i) {
            new_children[new_parent[i]].push_back(i);
        }

        // 4. Post-order DFS to calculate subtree sizes
        vector<int> ans(n, 1);
        auto compute_sizes = [&](auto& self, int u) -> int {
            int total = 1;
            for (int v : new_children[u]) {
                total += self(self, v);
            }
            ans[u] = total;
            return total;
        };

        compute_sizes(compute_sizes, 0);
        return ans;
    }
};