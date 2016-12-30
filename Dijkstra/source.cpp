#include <stdio.h> // printf, scanf
#include <utility> // pair
#include <vector> // vector
#include <set> // set

using namespace std;

#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define MAXN 100000

int N, M, S, D;
bool vis[MAXN];
vector<int> adj[MAXN], dist[MAXN];

int Dijkstra() {
    pair<int, int> now;
    set<pair<int, int> > pq;
    pq.insert(mp(0, S));

    while(!pq.empty()) {
        now=*pq.begin();
        pq.erase(pq.begin());

        if(now.Y==D) {
            return now.X;
        }

        if(vis[now.Y]) {
            continue;
        }
        vis[now.Y]=true;

        for(size_t i=0; i<adj[now.Y].size(); ++i) {
            if(!vis[adj[now.Y][i]]) {
                pq.insert(mp(now.X+dist[now.Y][i], adj[now.Y][i]));
            }
        }
    }

    return -1;
}

int main() {
    int from, to, val;
    scanf("%d %d %d %d", &N, &M, &S, &D);
    for(int i=1; i<=M; ++i) {
        scanf("%d %d %d", &from, &to, &val);
        adj[from].pb(to);
        dist[from].pb(val);
    }

    int ans=Dijkstra();
    if(ans==-1) {
        printf("Cannot reach destination\n");
    }
    else {
        printf("%d\n", ans);
    }

    return 0;
}

