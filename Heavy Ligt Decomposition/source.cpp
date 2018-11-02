/*
Heavy Light Decomposition (+ subtree queries) based on
this blog: https://codeforces.com/blog/entry/53170?locale=en
*/

#include <algorithm>    // swap
#include <vector>

using namespace std;

const int MAX_N = ; // <- insert value

vector<int> gr[MAX_N];      // adjacency list of the tree
int from[MAX_N], to[MAX_N]; // subtree range
int node_cnt;
int sz[MAX_N];              // subtree size
int head[MAX_N];            // chain head
int par[MAX_N];             // parent node
int lvl[MAX_N];             // node level

void get_sz(int u) {
    sz[u] = 1;
    // par[root] = -1
    if (par[u] != -1)
        gr[u].erase(find(gr[u].begin(), gr[u].end(), par[u]));
    for (auto &v : gr[u]) {
        par[v] = u;
        lvl[v] = lvl[u] + 1;
        get_sz(v);
        sz[u] += sz[v];
        if (sz[v] > sz[gr[u][0]])
            swap(gr[u][0], v);
    }
}

void hld(int u) {
    from[u] = to[u] = node_cnt++;
    for (auto v : gr[u]) {
        if (v == gr[u][0])
            head[v] = head[u];
        else
            head[v] = v;
        hld(v);
        to[u] = to[v];
    }
}

int LCA(int u, int v) {
    while (head[u] != head[v]) {
        if (lvl[head[u]] > lvl[head[v]])
            u = par[head[u]];
        else
            v = par[head[v]];
    }
    if (lvl[u] > lvl[v])
        return v;
    return u;
}

/*
int main() {
    int root = ; // <- insert value

    lvl[root] = 0;
    par[root] = -1;
    get_sz(root);

    node_cnt = 0;
    head[root] = root;
    hld(root);

    return 0;
}
*/

