/*

  one the difficult problems which i feared to read the Question and that fig in Explanation is too scary
the thing is we are going solve this by
1.sort the edges
2.find the actual MST value
3. for each edge check if we skip it if the total value MST value is increased it is Critical Edge
4. if above fails now we need to check if it is pseudo edge this is will be done by adding the edge already to the MST if the value is same it does belong to some MST

Note: if total Edges in MST is Less than V-1 then it is not MST return INT_MAX

This is how we solved it.... 🫡
  */

class Solution {
public:

    int findParent(vector<int>& parents, int node) {
        if (parents[node] == node) return node;
        return parents[node] = findParent(parents, parents[node]);
    }
    
    int unions(vector<int>& parents, vector<int>& rank, int a, int b) {
        int rootA = findParent(parents, a);
        int rootB = findParent(parents, b);
        //you should not update a,b because intermediate node may not be updated if done so. even if updated no issue no effect but redundant and you can update rank everytime but no need only update when they are equla.
        if (rootA == rootB) return -1;
        
        if (rank[rootA] < rank[rootB]) {
            parents[rootA] = rootB;
        } else if (rank[rootA] > rank[rootB]) {
            parents[rootB] = rootA;
        } else {
            parents[rootB] = rootA;
            rank[rootA]++;
        }
        return 1;
    }

    int spanningTree(int V,vector<vector<int>>& edges,int skip,int add) {

        // parents and rank sized to V
        vector<int> parents(V);
        vector<int> rank(V, 0);

        // initialize DSU
        for (int i = 0; i < V; i++)
            parents[i] = i;

        // // swap to {w, u, v}
        // for (int i = 0; i < edges.size(); i++) {
        //     int u = edges[i][0];
        //     int v = edges[i][1];
        //     int w = edges[i][2];
        //     edges[i] = {w, u, v};
        // }

        // sort by weight (now index 0)
        // sort(edges.begin(), edges.end());

        int ans = 0;
        int tEdges=0;

        if(add!=-1){
            tEdges++;
            ans+=edges[add][2];
            unions(parents,rank,edges[add][0],edges[add][1]);
        }


        for (int i = 0; i < edges.size(); i++) {
            int w = edges[i][2];
            int u = edges[i][0];
            int v = edges[i][1];

            if(i==skip)continue;

            if (unions(parents, rank, u, v) == 1){
                ans += w;
                tEdges++;
            }
        }

        if(tEdges < V-1 || tEdges > V-1 )return INT_MAX;

        return ans;
    }


    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        //this is pretty difficult problem i think so
        for(int i=0;i<edges.size();i++){
            edges[i].push_back(i);
        }
        auto cmp=[&](vector<int>&a,vector<int>&b){
            return a[2] < b[2];
        };

        //these are the answers...
        vector<int>critical;
        vector<int>pseudo;

        sort(begin(edges),end(edges),cmp);


         int actual=spanningTree(n,edges,-1,-1);

        cout<<actual<<endl;


        for(int i=0;i<edges.size();i++){
            if(spanningTree(n,edges,i,-1) > actual){
                critical.push_back(edges[i][3]);
            }
            else if(spanningTree(n,edges,-1,i)==actual){
                pseudo.push_back(edges[i][3]);
            }
        }
        return {critical,pseudo};
    }
};
