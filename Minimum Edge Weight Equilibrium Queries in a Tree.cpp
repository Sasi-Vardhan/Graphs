class Solution {
public:
    int LOG;
    vector<vector<int>> up;          // ancestors table
    vector<vector<int>> cnt;         // prefix weight count
    vector<int> depth;
    
    void dfs(int v, int p, vector<vector<pair<int,int>>>& adj) {
        up[v][0] = p;
        for (int k = 1; k < LOG; k++)
            up[v][k] = (up[v][k-1] == -1 ? -1 : up[ up[v][k-1] ][k-1]);
        
        for (auto &e : adj[v]) {
            int to = e.first;
            int w = e.second;
            if (to == p) continue;
            
            depth[to] = depth[v] + 1;
            cnt[to] = cnt[v];
            cnt[to][w]++;
            
            dfs(to, v, adj);
        }
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        
        int diff = depth[a] - depth[b];
        for (int k = 0; k < LOG; k++)
            if (diff & (1 << k))
                a = up[a][k];
        
        if (a == b) return a;
        
        for (int k = LOG-1; k >= 0; k--)
            if (up[a][k] != up[b][k]) {
                a = up[a][k];
                b = up[b][k];
            }

        return up[a][0];
    }

    vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {

        LOG = 20;
        up.assign(n, vector<int>(LOG, -1));
        depth.assign(n, 0);
        cnt.assign(n, vector<int>(27, 0));

        vector<vector<pair<int,int>>> adj(n);
        for (auto &e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }

        dfs(0, -1, adj);   // root at 0

        vector<int> ans;

        for (auto &q : queries) {
            int x = q[0], y = q[1];
            int c = lca(x, y);

            int total = 0, mx = 0;

            for (int w = 1; w <= 26; w++) {
                int freq = cnt[x][w] + cnt[y][w] - 2 * cnt[c][w];
                total += freq;
                mx = max(mx, freq);
            }

            ans.push_back(total - mx);
        }

        return ans;
    }
};
