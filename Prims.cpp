//the working of the algorithm is :
/*

first select the start node mostly '0' so the keys array = [0,INT_MAX,INT_MAX .....] will have and later the nodes will have INT_MAX

now 
src =0 
we will  update all the nodes ( which are connected src ) with weights condition keys[node] > weight[node][src] => keys[node]=weight[node][src];

so next we will selcted nearest one i.e key with minimum value

the intution is here the nodes we will be selecting are connected to each other at every point 
first 0 will update let say k1 nodes are updates we will be selecting ith node from them
next this nodes may update k2 nodes there can be overlapped next one node jth may be selected and this will be connected 

now lets see order

0 -> K1 two possibilites

0->k1->k2 or 0->K1
             | 
             k2

nor the possibilites be like

0->k1->k2->k3 or k3
                 |
                 0->K1
                 | 
                 k2

  but what is the guarantee that this would always be corrected 
  let's see our goal is to find minium spanning tree such that total sum of the edges will be minimum when it is converte to a tree
  this is ensured as we will be selecting node which is connted already selected nodes with minium value of key which will be updated everytime

  Star Condition :
   if(keys[i] > ( adjMat[i][node])){
                        keys[i]=adjMat[i][node];
                        parents[i]=node;
                    }
                }
  

  */


class Solution {
  public:
    
    int findMin(vector<int>&keys,vector<int>&visited,int V){
        int node=-1;
        int minAns=INT_MAX;
        for(int i=0;i<V;i++){
            if(visited[i]==0 && keys[i] < minAns ){
                minAns=keys[i];
                node=i;
            }
        }
        return node;
    }
    
    int spanningTree(int V, vector<vector<int>>& edges) {
        vector<int>parents(V,-1);
        vector<int>keys(V,INT_MAX);
        vector<int>visited(V,0);
        int src=0;
        keys[src]=0;
        int itr=V-1;
        vector<vector<int>>adjMat(V,vector<int>(V,INT_MAX));
        for(auto E:edges){
            int x=E[0],y=E[1],val=E[2];
            adjMat[x][y]=val;
            adjMat[y][x]=val;
        }
        
        while(itr--){
            int node=findMin(keys,visited,V);
            if(node==-1)continue;
            visited[node]=1;
            for(int i=0;i<V;i++){
                //an integer which is less than INT_MAX indicates there is an edge between the nodes
                if(adjMat[node][i]!=INT_MAX && visited[i]==0){
                    if(keys[i] > ( adjMat[i][node])){
                        keys[i]=adjMat[i][node];
                        parents[i]=node;
                    }
                }
            }
        }
        return accumulate(keys.begin(), keys.end(), 0);
        }
};
