#include <bits/stdc++.h>

using namespace std;

class PalTree {
    private:
        static const int MAXN = 5050;

        struct node {
            int next[26];
            int len;
            int sufflink;
            int occ;
            int cc;
        };

        void initTree() {
            num = 2; suff = 2;
            tree[1].len = -1; tree[1].sufflink = 1;
            tree[2].len = 0; tree[2].sufflink = 1;
            for (int i=0; i<len+5; i++){
                memset(tree[i].next, 0, sizeof tree[i].next);
                tree[i].occ = tree[i].cc = 0;
            }
        }

    public:
        int len;
        char s[MAXN];
        node tree[MAXN]; 
        int num;            // node 1 - root with len -1, node 2 - root with len 0
        int suff;           // max suffix palindrome

        PalTree(string ss){
            len = ss.length();
            for (int i=0; i<len; i++){
                s[i] = ss[i];
            }
            initTree();
        }

        PalTree(char* ss, int leng){
            len = leng;
            for (int i=0; i<len; i++){
                s[i] = ss[i];
            }
            initTree();
        }

        bool addLetter(int pos) {
            int cur = suff, curlen = 0;
            int let = s[pos] - 'a';

            while (true) {
                curlen = tree[cur].len;
                if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos])     
                    break;  
                cur = tree[cur].sufflink;
            }       
            if (tree[cur].next[let]) {  
                suff = tree[cur].next[let];
                tree[tree[cur].next[let]].occ++;
                tree[tree[cur].next[let]].cc++;
                return false;
            }

            // create new node
            num++;
            suff = num;
            tree[num].len = tree[cur].len + 2;
            tree[cur].next[let] = num;

            if (tree[num].len == 1) {
                tree[num].sufflink = 2;
                tree[num].occ = 1;
                tree[num].cc = 1;
                return true;
            }

            while (true) {
                cur = tree[cur].sufflink;
                curlen = tree[cur].len;
                if (pos - 1 - curlen >= 0 && s[pos - 1 - curlen] == s[pos]) {
                    tree[num].sufflink = tree[cur].next[let];
                    break;
                }       
            }           

            tree[num].occ = 1;
            tree[num].cc = 1;

            return true;
        }

        void processCC(){
            int cur = num;
            while (cur > 0){
                tree[tree[cur].sufflink].occ += tree[cur].cc;
                tree[tree[cur].sufflink].cc += tree[cur].cc;
                tree[cur].cc = 0;
                cur--;
            }
        }
};

int main(){
    char s[5050];
    int n;
    scanf("%s", s);
    n = strlen(s);
    PalTree paltree(s, n);
    for (int i=0; i<n; i++){
        paltree.addLetter(i);
    }
    paltree.processCC();
	return 0;
}
