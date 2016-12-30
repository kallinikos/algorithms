#include <bits/stdc++.h>

using namespace std;

#define MAXN 1000010

int inpt[MAXN];

void quicksort(int *arr, int n) {
    if(n<=1) {
        return;
    }
    int m=rand()%n;
    swap(arr[0], arr[m]);
    m=0;
    for(int i=1; i<n; ++i) {
        if(arr[i]<arr[m]) {
            swap(arr[m+1], arr[i]);
            swap(arr[m], arr[m+1]);
            ++m;
        }
    }
    quicksort(arr, m);
    quicksort(arr+m+1, n-m-1);
}

int main() {
    srand(time(NULL));
    int N;
    scanf("%d", &N);
    for(int i=0; i<N; ++i) {
        scanf("%d", &inpt[i]);
    }
    quicksort(inpt, N);
    for(int i=0; i<N; ++i) {
        printf("%d ", inpt[i]);
    }
    printf("\n");
    return 0;
}

