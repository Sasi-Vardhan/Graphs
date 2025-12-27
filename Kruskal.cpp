class Solution {
public:
    int findParent(vector<int>& parents, int node) {
        if (parents[node] == node) return node;
        return parents[node] = findParent(parents, parents[node]);
    }
    
    int unions(vector<int>& parents, vector<int>& rank, int a, int b) {
        int rootA = findParent(parents, a);
        int rootB = findParent(parents, b);
        //you should not update a,b because intermediate node may not be updated if done so. even if updated no issue no effect but redundant and you can update rank everytime but no need only update when they are equla.
        if (rootA == rootB) return -1;
        
        if (rank[rootA] < rank[rootB]) {
            parents[rootA] = rootB;
        } else if (rank[rootA] > rank[rootB]) {
            parents[rootB] = rootA;
        } else {
            parents[rootB] = rootA;
            rank[rootA]++;
        }
        return 1;
    }

    int spanningTree(int V, vector<vector<int>>& edges) {

        // parents and rank sized to V
        vector<int> parents(V);
        vector<int> rank(V, 0);

        // initialize DSU
        for (int i = 0; i < V; i++)
            parents[i] = i;

        // swap to {w, u, v}
        for (int i = 0; i < edges.size(); i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int w = edges[i][2];
            edges[i] = {w, u, v};
        }

        // sort by weight (now index 0)
        sort(edges.begin(), edges.end());

        int ans = 0;

        for (int i = 0; i < edges.size(); i++) {
            int w = edges[i][0];
            int u = edges[i][1];
            int v = edges[i][2];

            if (unions(parents, rank, u, v) == 1)
                ans += w;
        }

        return ans;
    }
};
