#include <stdio.h> // scanf, printf
#include <algorithm> // sort
#include <queue> // queue

using namespace std;

#define MAXN 1000010
#define MAXM 1000010

struct el {
    int from, to, val;
} edge[MAXM];

int height[MAXN], par[MAXN];

int Find(int now) {
    if(now!=par[now]) {
        par[now]=Find(par[now]);
    }
    return par[now];
}

void Union(int from, int to) {
    (void)Find(from);
    (void)Find(to);

    if(height[par[from]]<height[par[to]]) {
        par[par[from]]=par[to];
    }
    else if(height[par[from]]>height[par[to]]) {
        par[par[to]]=par[from];
    }
    else {
        par[par[to]]=par[from];
        ++height[par[from]];
    }
}

bool comp(el u, el v) {
    return u.val<v.val;
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    for(int i=1; i<=M; ++i) {
        scanf("%d %d %d", &edge[i].from, &edge[i].to, &edge[i].val);
    }

    sort(edge+1, edge+M+1, comp);
    for(int i=1; i<=N; ++i) {
        height[i]=0;
        par[i]=i;
    }

    int weight=0;
    queue<el> out;

    for(int i=1; i<=M; ++i) {
        if(Find(edge[i].from)!=Find(edge[i].to)) {
            out.push(edge[i]);
            weight+=edge[i].val;
            Union(edge[i].from, edge[i].to);
        }
    }

    printf("MST total weight: %d\n", weight);
    printf("MST contains:\n");
    while(!out.empty()) {
        printf("(%d, %d, %d) ", out.front().from, out.front().to, out.front().val);
        out.pop();
    }
    printf("\n");
    return 0;
}

