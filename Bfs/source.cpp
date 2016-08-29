#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define MAXN 1000000 //Το μέγιστο πλήθος κορυφών

int N, M; //Το πλήθος των κορυφών και το πλήθος των ακμών
bool vis[MAXN+5]; //Ο πίνακας που υποδεικνύει ποιους κόμβους έχει επισκεφτεί ο αλγόριθμος
vector<int> adj[MAXN+5]; //Η λίστα γειτνίασης

void Bfs(int source) {
    queue<int> qu;
    qu.push(source);
    int now;

    while(!qu.empty()) {
        now=qu.front();
        qu.pop();
        vis[now]=true;

        for(int i=0; i<adj[now].size(); ++i) {
            if(!vis[adj[now][i]]) {
                qu.push(adj[now][i]);
            }
        }
    }
}

int main() {
    scanf("%d %d", &N, &M);
    int from, to, source;
    for(int i=1; i<=M; ++i) {
        scanf("%d %d", &from, &to);
        adj[from].push_back(to);
    }
    scanf("%d", &source);

    Bfs(source);

    bool flag=false;
    for(int i=1; i<=N; ++i) {
        if(!vis[i]) {
            flag=true;
        }
    }

    if(flag) {
        printf("No\n");
    }
    else {
        printf("Yes\n");
    }
    return 0;
}

