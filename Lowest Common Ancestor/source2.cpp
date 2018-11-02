/*
Lowest Common Ancestor implementation with euler tour + sparse table.
- O(N log N) precomputation
- O(1) per query
*/

#include <algorithm>    // min, max
#include <vector>

using namespace std;

const int MAX_N = ;     // <- insert value
// LOGN must be equal to log2(3 * MAX_N)
const int LOGN = ;      // <- insert value

vector<int> gr[MAX_N];      // adjacency list of the tree
int euler[MAX_N * 3];       // tree euler tour (DFS-order)
int in[MAX_N], out[MAX_N];  // in and out time of DFS
int lvl[MAX_N];             // node level
int node_cnt;
int spt[LOGN][MAX_N * 3];   // sparse table
int lg[MAX_N * 3];          // array of logs (base 2)

void init(int u, int p = -1) {
    in[u] = out[u] = node_cnt;
    euler[node_cnt++] = u;

    for (auto v : gr[u]) {
        if (v == p) continue;
        lvl[v] = lvl[u] + 1;
        init(v, u);
        out[u] = node_cnt;
        euler[node_cnt++] = u;
    }
}

void buildSPT() {
    lg[1] = 0;
    for (int i = 2; i < MAX_N * 3; i++)
        lg[i] = lg[i >> 1] + 1;
    int n = node_cnt;
    for (int i = 0; i < n; i++)
        spt[0][i] = euler[i];
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++)
            if (lvl[spt[j - 1][i]] < lvl[spt[j - 1][i + (1 << (j - 1))]])
                spt[j][i] = spt[j - 1][i];
            else
                spt[j][i] = spt[j - 1][i + (1 << (j - 1))];
    }
}

int LCA(int u, int v) {
    int i = min(in[u], in[v]);
    int j = max(out[u], out[v]);
    int log = lg[j - i + 1];
    int a = spt[log][i], b = spt[log][j - (1 << log) + 1];
    if (lvl[a] < lvl[b])
        return a;
    return b;
}
/*
int main() {
    int root = ;    // <- insert value

    node_cnt = 0;
    lvl[root] = 0;

    init(root);
    buildSPT();

    return 0;
}
*/
