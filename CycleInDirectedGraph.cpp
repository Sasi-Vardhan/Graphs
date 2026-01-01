class Solution {
  public:
    bool findCycle(vector<vector<int>>&adj,int src,unordered_map<int,bool>dfsTrack,int V){
       for(auto nbr:adj[src]){
           if(dfsTrack[nbr])return true;
           dfsTrack[nbr]=true;
           bool ans=findCycle(adj,nbr,dfsTrack,V);
           if(ans)return true;
            dfsTrack[nbr]=false;
       }
       return false;
   }
    
    
    bool isCyclic(int V, vector<vector<int>> &edges) {
        
        //create an adjacency List
        vector<vector<int>>adj(V);
        unordered_map<int,bool>dfsTrack;
        // cout<<dfsTrack[2]<<endl;
        for(int i=0;i<edges.size();i++){
            // cout<<edges[i][0]<<edges[i][1]<<endl;
            adj[edges[i][0]].push_back(edges[i][1]);
        }
        bool ans=false;
        for(int i=0;i<V;i++){
            dfsTrack[i]=true;
            // cout<<"Start"<<i<<endl;
            ans=ans||findCycle(adj,i,dfsTrack,V);
             dfsTrack[i]=false;
            if(ans)return true;
        }
        return ans;
    }
};
