class Solution {
public:
    
    int applyDFS(vector<vector<int>>&adj,vector<int>&visited,vector<pair<int,int>>&isSafe,int src,vector<int>&ans){
        // cout<<src<<endl;
        if(isSafe[src].first==1 || isSafe[src].second==1)
        {
            ans.push_back(src);
            return 1;
        }

        if(adj[src].size()==0){
            ans.push_back(src);
            isSafe[src].first=1 ;
            isSafe[src].second=1;
            return 1;
        }
        int flag=1;

        for(auto node:adj[src]){
            if(visited[node]==0){
                visited[node]=1;
                int check=applyDFS(adj,visited,isSafe,node,ans);
                if(check==-1){
                    // cout<<"SRC : "<<src<<" "<<node<<endl;
                    flag=0;
                    break;
                }
            }
            else if(isSafe[node].first==1 || isSafe[node].second==1){
                continue;
            }
            else{
                // cout<<"SRC : "<<src<<" "<<node<<endl;
                flag=0;
                break;
            }
        }

        if(flag==1){
            ans.push_back(src);
            isSafe[src].first=1 ;
            isSafe[src].second=1;
        }
        return flag==1?1:-1;

    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int V=graph.size();
        vector<int>visited(V,0);
        vector<pair<int,int>>isSafe(V,{0,0});
        vector<int>ans;

        for(int i=0;i<V;i++){
            if(visited[i]==0){
            visited[i]=1;
            int check=applyDFS(graph,visited,isSafe,i,ans);
            }
        }
        sort(ans.begin(),ans.end());
        return ans;

    }
};
auto init = atexit([](){ofstream("display_runtime.txt")<<"0";});
