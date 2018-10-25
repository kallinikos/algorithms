/*
Successive Shortest Paths Algorithm for computing Min-Cost Max-Flow. Basically, it is just Edmonds-Karp with Bellman-Ford instead of BFS for getting an augmenting path.
Works in O(V ^ 2 * E ^ 2) worst case.
Implementation also supports multiple edges.
The graph must not contain a negative cycle at the time of calling the compute function.
*/
#include <algorithm>    // fill, min
#include <cstring>      // memset
#include <utility>      // pair, make_pair
#include <limits>       // numeric_limits
#include <vector>

using namespace std;

template<typename t_mc, typename t_mf>
struct mcmf {
    static const int NODES = ;  // <- insert value
    // Be carefule to set 2 * #ofedges because we count each one twice
    // (they are bidirectional in the residual network).
    static const int EDGES = ;  // <- insert value

    // Intentionally set INF_MC = MAX_VAL / 2 so that Bellamn Ford
    // will not crush.
    static const t_mc INF_MC = numeric_limits<t_mc>::max() / 2;
    static const t_mf INF_MF = numeric_limits<t_mf>::max();

    vector<int> adj[NODES];
    t_mf cap[EDGES];
    t_mc wgt[EDGES], dist[NODES];
    int to[EDGES], cnt_ed = 0;
    int p[NODES], pe[NODES], max_node;

    void init(int mx_nd) {
        max_node = mx_nd;
        fill(adj, adj + NODES, vector<int>());
        cnt_ed = 0;
    }

    void addEdge(int u, int v, t_mf c, t_mc w) {
        adj[u].push_back(cnt_ed);
        to[cnt_ed] = v;
        cap[cnt_ed] = c;
        wgt[cnt_ed] = w;
        cnt_ed++;

        adj[v].push_back(cnt_ed);
        to[cnt_ed] = u;
        cap[cnt_ed] = 0;
        wgt[cnt_ed] = -w;
        cnt_ed++;
    }

    bool BellmanFord(int s, int t) {
        memset(p, -1, sizeof p);
        fill(dist, dist + max_node + 1, INF_MC);
        dist[s] = 0;
        bool changed = true;
        for (int i = 0; i <= max_node && changed; i++) {
            changed = false;
            for (int u = 0; u <= max_node; u++) {
                for (auto e : adj[u]) {
                    int v = to[e];
                    if (cap[e] > ( t_mf )0 && dist[u] + wgt[e] < dist[v]) {
                        dist[v] = dist[u] + wgt[e];
                        p[v] = u;
                        pe[v] = e;
                        changed = true;
                    }
                }
            }
        }
        return p[t] != -1;
    }

    pair<t_mc, t_mf> compute(int s, int t) {
        t_mc mc = 0;
        t_mf mf = 0;
        while (BellmanFord(s, t)) {
            t_mf f = INF_MF;
            for (int u = t; u != s; u = p[u])
                f = min(f, cap[pe[u]]);
            if (f == ( t_mf )0) break;
            for (int u = t; u != s; u = p[u]) {
                cap[pe[u]] -= f;
                cap[pe[u] ^ 1] += f;
            }
            mf += f;
            mc += dist[t] * f;
        }
        return make_pair(mc, mf);
    }
};

/*
int main() {
    mcmf<int, int> box;

    s = // source
    t = // sink

    box.init(max_node_value);

    int mc, mf;
    tie(mc, mf) = box.compute(s, t);

    return 0;
}
*/

