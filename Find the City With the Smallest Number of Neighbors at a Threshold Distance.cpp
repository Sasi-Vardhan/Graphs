/*
this problem is solved usinfg floyd warshall algorithm which finds multiple source shortest path how ever you can apply Dijkstras algo if needed instead of this 
*/
class Solution {
public:
struct cmp {
    bool operator()(const pair<int,int>& a,
                    const pair<int,int>& b) const {
        if(a.first == b.first)
            return a.second < b.second;   // larger second first
        return a.first > b.first;          // smaller first first
    }
};

    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        vector<vector<int>>dist(n,vector<int>(n,100000000));
        //distance matrix
        for(auto e:edges){
            int x=e[0];
            int y=e[1];
            int w=e[2];
            dist[x][y]=w;
            dist[y][x]=w;
        }
        //floyd-warshal Algorithm to update dist matrix
        for(int helper=0;helper<dist.size();helper++){
          for(int src=0;src < dist.size();src++){
              for(int des=0;des<dist.size();des++){
                  if(helper!=src && dist[src][helper] < 100000000 && dist[helper][des] < 100000000)//this condition is used for checking whether there is edge or not and mentoined 10^8 means no edge
                  dist[src][des]=min(dist[src][des],dist[src][helper]+dist[helper][des]);
              }
          }
      }
      priority_queue<pair<int,int>, vector<pair<int,int>>, cmp> que;

      for(int i=0;i<n;i++){
        int points=0;
        
        for(int k=0;k<n;k++){
            if(dist[i][k]!=100000000 && k!=i && dist[i][k] <= distanceThreshold){
               
                points++;
                

            }
        }
        que.push({points,i});
        // cout<<"node "<<i<<" Cities Reached : "<<points<<endl;
        }
        
      
      

      return que.top().second;

    }
};
