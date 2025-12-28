// User function Template for C++

/*
this is on GFG and the thing is we will be using BFS and
and the solution key logic we will keep ops array which tells how many operations are used for reached for there and the thing how we will keep track of the visited nodes
the key idea is
if(ops[next] > ops[node]+1)
we will visited the already visited node only if number of operations are less to that node.
  */

class Solution {
  public:
    int minimumMultiplications(vector<int>& arr, int start, int end) {
        sort(arr.begin(),arr.end());
        queue<int>que;
        int endL=arr.size();
        if(start==end)return 0;
        // if(start*arr[0] < end)que.push(start);
        que.push(start);
        vector<int>ops(100000,INT_MAX);
        ops[start]=0;
        while(!que.empty()){
           int node=que.front();
           que.pop();
           for(auto i:arr){
               int next=node*i%100000;
               if(next==end)return ops[node]+1;
               if(ops[next] > ops[node]+1){
                   ops[next]=ops[node]+1;
                   que.push(next);
               }
           }
        }
        return -1;
    }
};
