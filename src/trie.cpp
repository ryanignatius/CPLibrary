#include <bits/stdc++.h>

using namespace std;

class Trie {
    private:

    public:
        vector<map<char,int> > edges; // edges[i]    : the labeled edges from node i
        vector<int> terminals;

        void init() {
            // add the initial node
            edges.push_back(map<char,int>());
            terminals.push_back(0);
        }
        
        void build(char *s, int len) {
            int n = 0;
            char ch;
            int r;
            for(int i=0; i<len; i++) {
                ch = s[i];
                if (edges[n].find(ch) == edges[n].end()) {
                    // build new node
                    r = edges.size();
                    edges.push_back(map<char,int>());
                    terminals.push_back(0);
                    edges[n][ch] = r;
                    n = r;
                } else {
                    // node already exist
                    n = edges[n][ch];
                }
            }
            terminals[n] = 1;
        }

        Trie() {
            init();
        }
        bool isTerminal(int n){
            return terminals[n] > 0;
        }
        int trieMove(char *w, int len){
            bool fail = false;
            int n = 0;
            for (int i=0; i<len; i++) {
                if (edges[n].find(w[i]) == edges[n].end()) {
                    fail = true;
                    break;
                }
                n = edges[n][w[i]];
            }
            if (fail) return -1;
            else return n;
        }
        int trieSingleMove(int pos, char ch){
            int n = pos;
            if (edges[n].find(ch) == edges[n].end()) {
                return -1;
            }
            return edges[n][ch];
        }
};

int main(){
    return 0;
}
