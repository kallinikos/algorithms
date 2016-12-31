#include <stdio.h> // printf, scanf
#include <utility> // pair
#include <vector> // vector
#include <set> // set
#include <queue> // queue

using namespace std;

#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define MAXN 100000

int N, M, S, D;
bool vis[MAXN];
vector<int> adj[MAXN], dist[MAXN];
queue<pair<pair<int, int>, int> > out;

int Prim() {
    int weight=0;
    pair<int, pair<int, int> > now;
    set<pair<int, pair<int, int> > > pq;
    pq.insert(mp(0, mp(1, 0)));

    while(!pq.empty()) {
        now=*pq.begin();
        pq.erase(pq.begin());

        if(vis[now.Y.X]) {
            continue;
        }
        vis[now.Y.X]=true;
        weight+=now.X;
        out.push(mp(mp(now.Y.X, now.Y.Y), now.X));

        for(size_t i=0; i<adj[now.Y.X].size(); ++i) {
            if(!vis[adj[now.Y.X][i]]) {
                pq.insert(mp(dist[now.Y.X][i], mp(adj[now.Y.X][i], now.Y.X)));
            }
        }
    }
    out.pop(); // First element will be (1, 0, 0)

    return weight;
}

int main() {
    int from, to, val;
    scanf("%d %d", &N, &M);
    for(int i=1; i<=M; ++i) {
        scanf("%d %d %d", &from, &to, &val);
        adj[from].pb(to);
        adj[to].pb(from);
        dist[from].pb(val);
        dist[to].pb(val);
    }

    int weight=Prim();
    printf("MST total weight %d\n", weight);
    printf("MST contains:\n");
    while(!out.empty()) {
        printf("(%d, %d, %d) ", out.front().first.first, out.front().first.second, out.front().second);
        out.pop();
    }
    printf("\n");

    return 0;
}

