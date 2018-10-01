/*
Virtual Tree implementation based on https://blog.sengxian.com/algorithms/virtual-tree (in Chinese).

Build in O(L log N) where L = # of Virtual Tree nodes
*/
#include <algorithm>    // sort
#include <vector>

using namespace std;

const int MAX_N = ;     // <- insert value

// NOTE: nodes are 1-based indexed
vector<int> gr[MAX_N];  // adjacency list of the tree
int stk[MAX_N];
int dfn[MAX_N];         // DFS-order time
int lvl[MAX_N];         // node level
int df_counter;

bool comp(int a, int b) {
    return dfn[a] < dfn[b];
}

// NOTE: need to specify the content of this function
void addEdge(int u, int v) {
    // ...
    // e.g. tree[u].push_back(v)
}

void dfs(int u, int p = -1) {
    dfn[u] = df_counter++;
    for (auto v : gr[u]) {
        if (v == p) continue;
        lvl[v] = lvl[u] + 1;
        dfs(v);
    }
}

int LCA(int u, int v) {
    // fill in this function
}

// returns the VT nodes
vector<int> buildVT(vector<int> vtx) {
    sort(vtx.begin(), vtx.end(), comp);

    int top = 0;

    lvl[0] = -1;
    stk[top++] = 0;

    int L = (int)vtx.size();
    for (int i = 0; i < L; i++) {
        int u = vtx[i];
        int p = LCA(u, stk[top - 1]);
        while (top >= 2 && lvl[stk[top - 2]] >= lvl[p]) {
            addEdge(stk[top - 2], stk[top - 1]);
            top--;
        }

        if (stk[top - 1] != p) {
            addEdge(p, stk[top - 1]);
            top--;
            stk[top++] = p;
            vtx.push_back(p);
        }

        stk[top++] = u;
    }

    for (int i = 1; i < top - 1; i++) {
        addEdge(stk[i], stk[i + 1]);
    }

    return vtx;
}

/*
int main() {
    computeLCA();
    df_counter = 0;
    lvl[1] = 0;
    dfs(1);
    vector<int> vtx = ; // <- insert value
    vtx = buildVT(vtx);
    return 0;
}
*/

