#include <cstring> // memset
#include <vector>

using namespace std;

const int MAX_N = ;     // <- insert value
const int LOGN = ;      // <- insert value

vector<int> gr[MAX_N];  // adjacency list of the tree
int par[MAX_N][LOGN];   // binary lifting table
int lvl[MAX_N];         // node level

void init(int u) {
    for (int j = 1; j < LOGN; j++)
        if (par[u][j - 1] != -1)
            par[u][j] = par[par[u][j - 1]][j - 1];
    for (auto v : gr[u]) {
        if (v == par[u][0]) continue;
        par[v][0] = u;
        lvl[v] = lvl[u] + 1;
        init(v);
    }
}

int LCA(int u, int v) {
    if (lvl[v] > lvl[u]) swap(u, v);
    for (int j = LOGN - 1; j >= 0; j--)
        if (lvl[v] + (1 << j) <= lvl[u])
            u = par[u][j];
    if (u == v) return u;
    for (int j = LOGN - 1; j >= 0; j--)
        if (par[u][j] != -1 && par[u][j] != par[v][j])
            u = par[u][j], v = par[v][j];
    return par[u][0];
}

int main() {
    int root = ;    // <- insert value

    memset(par, -1, sizeof par);

    lvl[root] = 0;
    init(root);
}


