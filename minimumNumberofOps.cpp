//this is Greedy problem but can be confused with graph problems due to we have seen problems with similar names


class Solution {
public:
    int minMoves(int target, int maxDoubles) {
       int ans=0;
       if(maxDoubles==0)return target-1;
       while(target > 1){
        if(maxDoubles==0){
            ans+=target-1;
            return ans;
        }
        if(target%2==0 && maxDoubles){
            target=target/2;
            maxDoubles--;
        }
        else target=target-1;
        ans++;
       }
       return ans;
    }
};
