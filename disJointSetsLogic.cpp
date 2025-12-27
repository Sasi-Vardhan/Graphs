int findParent(vector<int>& parents, int node) {
        if (parents[node] == node) return node;
  //this line is path compression which happens everytime when we seaech for parent with in a node  
        return parents[node] = findParent(parents, parents[node]);
    }
    
    int unions(vector<int>& parents, vector<int>& rank, int a, int b) {
        int rootA = findParent(parents, a);
        int rootB = findParent(parents, b);
        
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
