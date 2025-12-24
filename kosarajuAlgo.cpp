//Position this line where user code will be pasted.
//this problem is from GFG and this is used to find SCC in the graph
class Solution {
  public:
  
  
   void applyDFS(vector<vector<int>>&adj,vector<int>&visited,int src,stack<int>&s){
       visited[src]=1;
       for(auto e:adj[src]){
           if(visited[e]==0)applyDFS(adj,visited,e,s);
       }
    //   cout<<"P"<<src<<endl;
       s.push(src);
       
   }
   
   void applyRevDFS(vector<vector<int>>&adj,vector<int>&visited,int src){
       visited[src]=1;
       for(auto e:adj[src]){
        //   cout<<"R: "<<e<<endl;
           if(visited[e]==0)applyRevDFS(adj,visited,e);
       }
    //   cout<<src<<endl;
   }
    
    int kosaraju(vector<vector<int>> &adj) {
        // code here
        int V=adj.size();
        vector<vector<int>>revAdj(V);
        for(int i=0;i<V;i++){
            // cout<<i<<" : ";
            for(auto e:adj[i]){
                // cout<<e<<" ";
                revAdj[e].push_back(i);
            }
            // cout<<endl;
        }
        stack<int>s;
        vector<int>visited(V,0);
        for(int i=0;i<V;i++){
            if(visited[i]==0){
                applyDFS(adj,visited,i,s);
            }
        }
        // cout<<"Reverse Order"<<endl;
        // for(int i=0;i<V;i++){
        //      cout<<i<<" : ";
        //     for(auto e:revAdj[i]){
        //         cout<<e<<" ";
        //     }
        //     cout<<endl;
        // }
        
        //after getting the order
        int count=0;
        fill(visited.begin(),visited.end(),0);
        // visited={0};
        while(!s.empty()){
            int node=s.top();
            // cout<<"N "<<node<<endl;
            if(visited[node]==0){
                count++;
                applyRevDFS(revAdj,visited,node);
            }
            s.pop();
        }
        return count;
        
    }
};
