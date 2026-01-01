class Solution {
  public:
    // Function to detect cycle in a connected component
    bool detectCycleBFS(int startNode, int V, vector<vector<int>>& adj, vector<int>& visited) {
        unordered_map<int, int> parents;
        queue<int> q;
        
        q.push(startNode);
        visited[startNode] = 1;
        parents[startNode] = -1;
        
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            
            // Optimization: Iterate ONLY over actual neighbors (Adjacency List)
            for(int neighbor : adj[node]) {
                
                // If neighbor is not visited, process it
                if(!visited[neighbor]) {
                    visited[neighbor] = 1;
                    q.push(neighbor);
                    parents[neighbor] = node;
                }
                // If neighbor is visited AND it is not the parent, we found a cycle
                else if(parents[node] != neighbor) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isCycle(int V, vector<vector<int>>& edges) {
        // 1. Build Adjacency List (Efficient Space & Time)
        vector<vector<int>> adj(V);
        for(auto& E : edges) {
            adj[E[0]].push_back(E[1]);
            adj[E[1]].push_back(E[0]);
        }
        
        vector<int> visited(V, 0);
        
        // 2. Handle Disconnected Components
        // Check every node. If not visited, start a traversal.
        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                if(detectCycleBFS(i, V, adj, visited)) {
                    return true; 
                }
            }
        }
        
        return false;
    }
};
