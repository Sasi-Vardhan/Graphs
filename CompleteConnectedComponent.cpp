//Leetcode problem 

// the difference between this question and SCC is in an SCC there will be an directed edge between the the components which will cause this algorith to fail as the order will be distorted with connecting edge
// so for scc we need to use  kosaraju algorithm not this one.

class Solution {
public:

    void applyDFS(vector<vector<int>>&adj,vector<pair<int,int>>&visited,int src,stack<int>&s){
        visited[src].first=1;
        for(auto e:adj[src]){
            if(visited[e].first==0){
                applyDFS(adj,visited,e,s);
               
            }
        }
        s.push(src);
    }
    
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<pair<int,int>>visited(n,{0,0});
        vector<vector<int>>adj(n);
        for(auto E:edges){
            int x=E[0];
            int y=E[1];
            visited[x].second++;
            visited[y].second++;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        stack<int>temp;
        int component=0;
        for(int i=0;i<n;i++){
            if(visited[i].first==0){
                applyDFS(adj,visited,i,temp);
                int limit=temp.size()-1;
                bool isComponent=true;
                while(!temp.empty()){
                    int node=temp.top();
                    if(visited[node].second!=limit)isComponent=false;
                    temp.pop();
                }
                if(isComponent)component++;
            }
        }
        return component;
    }
};
