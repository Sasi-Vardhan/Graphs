// User function template for C++

//problem is in GFG..

class Solution {
  public:
    void floydWarshall(vector<vector<int>> &dist) {
      for(int helper=0;helper<dist.size();helper++){
          for(int src=0;src < dist.size();src++){
              for(int des=0;des<dist.size();des++){
                  if(helper!=src && dist[src][helper] < 100000000 && dist[helper][des] < 100000000)//this condition is used for checking whether there is edge or not and mentoined 10^8 means no edge
                  dist[src][des]=min(dist[src][des],dist[src][helper]+dist[helper][des]);
              }
          }
      }
    }
};
