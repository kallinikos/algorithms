#include <stdio.h> // printf, scanf
#include <utility> // pair
#include <queue> // priority_queue

using namespace std;

#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define MAXN 100000

struct el {
    el* next;
    int to, val;
    el(el* next, int to, int val) {
        this->next=next;
        this->to=to;
        this->val=val;
    }
} *adj[MAXN];

int N, M, S, D;
bool vis[MAXN];

int Dijkstra() {
    pair<int, int> now;
    priority_queue<pair<int, int> > pq;
    pq.push(mp(0, S));

    while(!pq.empty()) {
        now=pq.top();
        pq.pop();

        if(now.Y==D) {
            return now.X;
        }

        if(vis[now.Y]) {
            continue;
        }

        vis[now.Y]=true;

        for(el* nxt=adj[now.Y]; nxt; nxt=nxt->next) {
            if(!vis[nxt->to]) {
                pq.push(mp(now.X+nxt->val, nxt->to));
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
        adj[from]=new el(adj[from], to, val);
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

