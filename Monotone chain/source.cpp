#include <stdio.h> // scanf, printf
#include <math.h> // sqrt
#include <algorithm> // sort
#include <utility> // pair

using namespace std;

#define X first
#define Y second
#define mp make_pair
#define pii pair<int,int>
#define llint long long
#define pll pair<llint, llint>
#define sq(x) ((x)*(x))
#define MAXN 100010

llint CCW(pll A, pll B, pll C) { // CCW = Counter-ClockWise. Θεωρητικά εσωτερικό γινόμενο των διανυσμάτων (A-B) και (C-B) (επί δύο). Είναι θετικό αν και μόνο αν το σημείο C είναι αριστερά της ευθείας που περνάει από τα A,B. Είναι μηδέν όταν τα A, B, C είναι συνευθειακά.
    return A.X*B.Y-A.Y*B.X+B.X*C.Y-B.Y*C.X+C.X*A.Y-C.Y*A.X;
}

double dist(pll u, pll v) { // Απόσταση των σημείων u και v
    return sqrt(sq(u.X-v.X)+sq(u.Y-v.Y));
}

int N, hull[MAXN];
pii pt[MAXN];

int main() {
    scanf("%d", &N);
    for(int i=1; i<=N; ++i) {
        scanf("%d %d", &pt[i].X, &pt[i].Y);
    }
    sort(pt+1, pt+N+1);

    int top=0;
    for(int i=1; i<=N; ++i) { // Υπολογισμός του upper envelope
        while(top>=2 && CCW(pt[hull[top-1]], pt[hull[top]], pt[i])>=0) {
            --top;
        }
        hull[++top]=i;
    }
    for(int i=N-1; i>=1; --i) { // Υπολογισμός του lower envelope
        while(top>=2 && CCW(pt[hull[top-1]], pt[hull[top]], pt[i])>=0) {
            --top;
        }
        hull[++top]=i;
    }

    double length=0;
    printf("Convex Hull:\n");
    for(int i=1; i<top; ++i) {
        printf("%d %d\n", pt[hull[i]].X, pt[hull[i]].Y);
        length+=dist(pt[hull[i]], pt[hull[i+1]]);
    }
    printf("Convex Hull length: %lf\n", length);

    return 0;
}

