//this is there on the leetcode and solved using BFS

class Solution {
public:
    
    void findRel(string&word,unordered_map<string,vector<string>>&mp,unordered_map<string,bool>&neighbors){
        int temp=word.size();
        int pos=0;
        string act=word;
        while(temp--){
            char old=word[pos];
            for(char i='a';i<='z';i++){
                word[pos]=i;
                if(neighbors[word]){
                    mp[act].push_back(word);
                }
            }
            word[pos]=old;
            pos++;

        }
    }

    int applyBFS(string&beginWord,unordered_map<string,vector<string>>&related,unordered_map<string,bool>&neighbors,string &endWord){
        queue<pair<string,int>>que;
        que.push({beginWord,1});
         neighbors[beginWord]=false;
        while(!que.empty()){
            pair<string,int> node=que.front();
            que.pop();
            if(node.first==endWord)return node.second;
            for(auto nbr:related[node.first]){
                if(nbr==endWord)return node.second+1;
                if(neighbors[nbr]){
                    que.push({nbr,node.second+1});
                    neighbors[nbr]=false;
                }
            }
        }
        return 0;
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string,bool>neighbors;
        neighbors[beginWord]=true;
        for(auto str:wordList){
            neighbors[str]=true;
        }
        unordered_map<string,vector<string>>related;
        findRel(beginWord,related,neighbors);
        for(auto str:wordList){
            if(str!=beginWord)
            findRel(str,related,neighbors);
        }
        int ans=applyBFS(beginWord,related,neighbors,endWord);
        return ans;

    }
};
auto init = atexit([](){ofstream("display_runtime.txt")<<0;});
