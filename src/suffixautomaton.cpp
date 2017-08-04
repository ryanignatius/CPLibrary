#include <bits/stdc++.h>

using namespace std;

class SuffixAutomaton {
    private:
        long long dfs(int cur){
            if (memo[cur] >= 0) return memo[cur];
            long long q = 1;
            for (map<char, int>::iterator it = edges[cur].begin(); it != edges[cur].end(); it++){
                int v = it->second;
                q += dfs(v);
            }
            return memo[cur] = q;
        }
        long long dfs2(int cur){
            if (memo2[cur] >= 0) return memo2[cur];
            long long q = 0;
            if (isTerminal(cur)) q = 1;
            for (map<char, int>::iterator it = edges[cur].begin(); it != edges[cur].end(); it++){
                int v = it->second;
                q += dfs2(v);
            }
            return memo2[cur] = q;
        }
        int dfs3(int cur){
            if (memo3[cur] >= 0) return memo3[cur];
            int q = 1;
            for (map<char, int>::iterator it = edges[cur].begin(); it != edges[cur].end(); it++){
                int v = it->second;
                q = max(q, 1+dfs3(v));
            }
            return memo3[cur] = q;
        }

    public:
        vector<map<char,int> > edges; // edges[i]    : the labeled edges from node i
        vector<int> link;             // link[i]     : the parent of i
        vector<int> length;           // length[i] : the length of the longest string in the ith class
        int last;                     // the index of the equivalence class of the whole string
        int originalLength;
        vector<int> terminals;
        vector<long long> memo; // number path from this node
        vector<long long> memo2; // number path from this node end in terminal
        vector<int> memo3; // longest path from this node to terminal
        vector<vector<int> > children;

        SuffixAutomaton(char *s, int len) {
            originalLength = len;
            // add the initial node
            edges.push_back(map<char,int>());
            link.push_back(-1);
            length.push_back(0);
            last = 0;

            for(int i=0;i<len;i++) {
                // construct r
                edges.push_back(map<char,int>());
                length.push_back(i+1);
                link.push_back(0);
                int r = edges.size() - 1;

                // add edges to r and find p with link to q
                int p = last;
                while(p >= 0 && edges[p].find(s[i]) == edges[p].end()) {
                    edges[p][s[i]] = r;
                    p = link[p];
                }
                if(p != -1) {
                    int q = edges[p][s[i]];
                    if(length[p] + 1 == length[q]) {
                        // we do not have to split q, just set the correct suffix link
                        link[r] = q;
                    } else {
                        // we have to split, add q'
                        edges.push_back(edges[q]); // copy edges of q
                        length.push_back(length[p] + 1);
                        link.push_back(link[q]); // copy parent of q
                        int qq = edges.size()-1;
                        // add qq as the new parent of q and r
                        link[q] = qq;
                        link[r] = qq;
                        // move short classes pointing to q to point to q'
                        while(p >= 0 && edges[p][s[i]] == q) {
                            edges[p][s[i]] = qq;
                            p = link[p];
                        }
                    }
                }
                last = r;
            }
            terminals.assign(last+10,0);
            int p = last;
            while(p > 0) {
                terminals[p] = 1;
                p = link[p];
            }
            children = vector<vector<int> >(link.size());
            for(int i=0;i<link.size();i++) {
                if(link[i] >= 0) children[link[i]].push_back(i);
            }
        }
        bool isTerminal(int n){
            return terminals[n] > 0;
        }
        bool isSubstring(string w){
            int n = automatonMove(w);
            if (n >= 0){
                return true;
            } else return false;
        }
        bool isSuffix(string w){
            int n = automatonMove(w);
            if (n >= 0){
                return isTerminal(n);
            } else return false;
        }
        long long numDistinctSubstring(){
            return memo[0]-1;
        }
        long long numOccurence(string w){
            int n = automatonMove(w);
            if (n >= 0){
                return memo2[n];
            } else return 0;
        }
        int firstOccurence(string w){
            int n = automatonMove(w);
            if (n >= 0){
                return length[n]-w.length();
            } else return -1;
        }
        vector<int> allOccurences(string w){
            int n = automatonMove(w);
            return allOccurences(n, w.length());
        }
        vector<int> allOccurences(int n, int len){
            vector<int> ret;
            vector<int> vis;
            vis.assign(last, 0);
            if (n >= 0){
                queue<int> q;
                q.push(n);
                int cur;
                while (!q.empty()){
                    cur = q.front();
                    q.pop();
                    if (vis[cur]) continue;
                    vis[cur] = 1;
                    if (cur <= originalLength){
                        ret.push_back(length[cur]-len);
                    }
                    for (int j=0; j<children[cur].size(); j++){
                        q.push(children[cur][j]);
                    }
                }
            }
            return ret;
        }
        void buildMemo(){
            memo.assign(last+10, -1);
            dfs(0);
        }
        void buildMemo2(){
            memo2.assign(last+10, -1);
            dfs2(0);
        }
        void buildMemo3(){
            memo3.assign(last+10, -1);
            dfs3(0);
        }
        int automatonMove(string w){
            bool fail = false;
            int n = 0;
            for (int i=0; i<w.size(); i++) {
                if (edges[n].find(w[i]) == edges[n].end()) {
                    fail = true;
                    break;
                }
                n = edges[n][w[i]];
            }
            if (fail) return -1;
            else return n;
        }
        int automatonSingleMove(int pos, char ch){
            bool fail = false;
            int n = pos;
            if (edges[n].find(ch) == edges[n].end()) {
                fail = true;
            }
            n = edges[n][ch];
            if (fail) return -1;
            else return n;
        }
};

int main(){
    char s[] = "fixprefixsuffix";
    string w = "fix";
    string pref = "fixprefix";
    string suff = "fixsuffix";
    string no = "prep";
    SuffixAutomaton at(s, strlen(s));
    at.buildMemo();
    at.buildMemo2();
    at.buildMemo3();
    cout << "String: " << s << endl;
    cout << w << " is substring: " << at.isSubstring(w) << ", is suffix: " << at.isSuffix(w) << endl;
    cout << pref << " is substring: " << at.isSubstring(pref) << ", is suffix: " << at.isSuffix(pref) << endl;
    cout << suff << " is substring: " << at.isSubstring(suff) << ", is suffix: " << at.isSuffix(suff) << endl;
    cout << no << " is substring: " << at.isSubstring(no) << ", is suffix: " << at.isSuffix(no) << endl;
    cout << "num distinct substring: " << at.numDistinctSubstring() << endl;
    string ss[] = {"fix", "prefix", "suffix", "f", "x"};
    for (int i=0; i<5; i++){
        cout << ss[i] << ", num occurence: " << at.numOccurence(ss[i]) << ", first occurence: " << at.firstOccurence(ss[i]) << endl;
        vector<int> ao = at.allOccurences(ss[i]);
        cout << "all occurence " << ss[i] << ": ";
        for (int j=0; j<ao.size(); j++){
            cout << ao[j] << " ";
        }
        cout << endl;
    }
    return 0;
}
