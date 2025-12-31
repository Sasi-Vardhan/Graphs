class Solution {
public:

    int LOG;                        // number of jump levels
    vector<vector<int>> up;         // up[v][k] = 2^k ancestor of v
    vector<int> depth;              // depth of each node
    vector<vector<int>> cnt;        // cnt[v][w] = frequency of weight w on path root → v


    // ==========================
    // DFS (runs once from root)
    // ==========================
    void dfs(int v, int parent, vector<vector<pair<int,int>>>& adj) {

        // 1️⃣ store immediate parent (2^0 ancestor)
        up[v][0] = parent;

        // 2️⃣ fill ancestors for all powers of two
        // up[v][k] = 2^k ancestor
        for (int k = 1; k < LOG; k++) {
            if (up[v][k-1] == -1)
                up[v][k] = -1;
            else
                up[v][k] = up[ up[v][k-1] ][k-1];
        }

        // 3️⃣ explore children
        for (auto &edge : adj[v]) {

            int to = edge.first;     // neighbor node
            int w  = edge.second;    // edge weight (1..26)

            if (to == parent) continue;   // don't go back up the tree

            depth[to] = depth[v] + 1;     // child is 1 deeper

            // copy parent's frequency counts
            cnt[to] = cnt[v];

            // increment count of this edge weight
            cnt[to][w]++;

            // DFS further down
            dfs(to, v, adj);
        }
    }



    // ==========================
    // LCA FUNCTION
    // ==========================
    int lca(int a, int b) {

        // 1️⃣ Ensure a is deeper or equal
        if (depth[a] < depth[b]) 
            swap(a, b);

        // 2️⃣ Lift `a` up to the same depth as `b`
        int diff = depth[a] - depth[b];

        for (int k = 0; k < LOG; k++) {
            if (diff & (1 << k)) {       // if this bit is set
                a = up[a][k];            // jump a up by 2^k
            }
        }

        // Now depth[a] == depth[b]

        // 3️⃣ If they are already same node → that's LCA
        if (a == b) return a;

        // 4️⃣ Lift both upwards together
        // Start from largest jump → smallest
        for (int k = LOG - 1; k >= 0; k--) {

            // If jumping does NOT make them equal
            if (up[a][k] != up[b][k]) {
                a = up[a][k];   // jump both
                b = up[b][k];
            }
        }

        // 5️⃣ Now both are direct children of LCA
        return up[a][0];
    }
};
