/*
this is from Leetcode 1319
and it asks us to find minimum number of operations required to make a network  connected

intution is: to make an Network connected we need to check how many components are there in it in before hand 

here an operation refers to we can use any of the existing edge and use that edge to connect the components 

the solution for every componet lets find number of edges in it and nodes for every component there should minimum n-1 edges to make it connected remaining are extra 

so lets find all the extra edges and check if we can combine all the components using them Like if(extra > components-1)return components-1 because we will need to connect components-1 so it is the minimum number 
*/
class Solution {
public:
    
    pair<int,int> applyBFS(vector<vector<int>>&adj,int src,vector<int>&visited){
        queue<int>que;
        unordered_map<string,bool>edges;
        int edg=0;
        visited[src]=1;
        int nodes=0;
        que.push(src);
        while(!que.empty()){
            int node=que.front();
            que.pop();
            nodes++;
            for(auto nbr:adj[node]){
                string s=to_string(nbr)+to_string(node);
                string rs=to_string(node)+to_string(nbr);
                if(edges[s]==false && edges[rs]==false){
                    edg++;
                    edges[s]=true;
                    edges[rs]=true;
                }
                if(visited[nbr]==0){
                    visited[nbr]=1;
                    que.push(nbr);
                }
            }
        }
        return {nodes,edg};
    }

    int makeConnected(int n, vector<vector<int>>& connections) {
        vector<int>visited(n,0);
        int dis=0;
        vector<vector<int>>adj(n);
        for(auto e:connections){
            int x=e[0];int y=e[1];
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        int extra=0;
        for(int i=0;i<n;i++){
            if(visited[i]==0){
                pair<int,int>ne=applyBFS(adj,i,visited);
                extra+=ne.second-(ne.first-1);
                dis++;
            }
        }
        cout<<extra<<" "<<dis<<endl;
        if(extra >= dis-1)return dis-1;
        return -1;

    }
};
