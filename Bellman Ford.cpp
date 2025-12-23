// found in GFG Practice

// User function Template for C++

class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        // Code here
        vector<int>shortestPath(V,100000000);
        shortestPath[src]=0;
        int temp=V+1;
        int updated=0;
        int r=edges.size(),c=edges[0].size();
        unordered_map<int,int>connected;
        queue<int>que;
        que.push(src);
        
        
        while(!que.empty()){
            int node=que.front();
            if(connected[node]==0){
                for(int i=0;i<r;i++){
                    if(edges[i][0]==node){
                        que.push(edges[i][1]);
                    }
                }
            }
            connected[node]=1;
            que.pop();
        }
        
        while(temp--){
            updated=0;
            for(int i=0;i<r;i++){
                
                    if(connected[edges[i][0]]==1){
               
                        if(shortestPath[edges[i][0]] == INT_MAX)continue;
                        else if(shortestPath[edges[i][0]]+edges[i][2] < shortestPath[edges[i][1]]){
                            shortestPath[edges[i][1]]=shortestPath[edges[i][0]]+edges[i][2];
                            updated=1;
                        }
                    }
            }
            if(updated==0)return shortestPath;
        }
        return {-1};
        
    }
};
