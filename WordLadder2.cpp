//BFS + Backtacking the most difficult problem

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // -------- 1️⃣ Build neighbor words --------
    vector<string> getNeighbors(string word, unordered_set<string>& dict) {
        vector<string> result;
        string temp = word;

        for(int i = 0; i < word.size(); i++) {
            char old = temp[i];
            for(char c = 'a'; c <= 'z'; c++) {
                temp[i] = c;
                if(temp != word && dict.count(temp)) {
                    result.push_back(temp);
                }
            }
            temp[i] = old; // reset back
        }
        return result;
    }


    // -------- 2️⃣ Build shortest distance & parent graph --------
    void bfs(string beginWord, string endWord,
             unordered_set<string>& dict,
             unordered_map<string,int>& dist,
             unordered_map<string,vector<string>>& parent)
    {
        queue<string> q;
        q.push(beginWord);
        dist[beginWord] = 0;

        int shortest = INT_MAX;

        while(!q.empty()) {
            string word = q.front();
            q.pop();

            int step = dist[word];

            if(step > shortest) return;

            vector<string> nbrs = getNeighbors(word, dict);

            for(string& next : nbrs) {

                // first time reaching this word
                if(dist[next] > step + 1) {
                    dist[next] = step + 1;
                    parent[next].clear();
                    parent[next].push_back(word);
                    q.push(next);
                }
                // another shortest parent
                else if(dist[next] == step + 1) {
                    parent[next].push_back(word);
                }

                if(next == endWord)
                    shortest = step + 1;
            }
        }
    }


    // -------- 3️⃣ Backtracking to build all shortest paths --------
    void dfs(string word, string beginWord,
             unordered_map<string,vector<string>>& parent,
             vector<string>& path,
             vector<vector<string>>& ans)
    {
        path.push_back(word);

        if(word == beginWord) {
            vector<string> temp = path;
            reverse(temp.begin(), temp.end());
            ans.push_back(temp);
            path.pop_back();
            return;
        }

        for(string& p : parent[word]) {
            dfs(p, beginWord, parent, path, ans);
        }

        path.pop_back();
    }


    // -------- 4️⃣ Main function --------
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {

        unordered_set<string> dict(wordList.begin(), wordList.end());
        vector<vector<string>> ans;

        if(!dict.count(endWord)) return ans;

        unordered_map<string,int> dist;
        unordered_map<string,vector<string>> parent;

        for(auto &w : dict) dist[w] = INT_MAX;
        dist[beginWord] = 0;

        bfs(beginWord, endWord, dict, dist, parent);

        if(dist[endWord] == INT_MAX) return ans;

        vector<string> path;
        dfs(endWord, beginWord, parent, path, ans);

        return ans;
    }
};
