/*
Centroid Decomposition implementation with support for centroid tree construction.
*/

#include <vector>

using namespace std;

const int MAX_N = ;         // <- insert value

vector<int> gr[MAX_N];      // adjacency list of the tree
vector<int> tree[MAX_N];    // centroid tree
bool mark[MAX_N];           // currently marked centroids
int sz[MAX_N];              // subtree size

void get_sz(int u, int p) {
    sz[u] = 1;
    for (auto v : gr[u]) {
        if (v == p || mark[v]) continue;
        get_sz(v, u);
        sz[u] += sz[v];
    }
}

int cent_dec(int u, int p, const int n) {
    int big = -1, mx = -1;
    for (auto v : gr[u]) {
        if (!mark[v] && v != p && sz[v] > mx) {
            mx = sz[v];
            big = v;
        }
    }
    if (2 * mx <= n) {
        mark[u] = true;
        for (auto v : gr[u]) {
            if (mark[v]) continue;
            get_sz(v, u);
            int cent = cent_dec(v, u, sz[v]);
            tree[u].push_back(cent);
        }
        return u;
    } else {
        return cent_dec(big, u, n);
    }
}

/*
int main() {
    get_sz(1, -1);
    int centroid = cent_dec(1, -1, sz[1]);
    return 0;
}
*/

