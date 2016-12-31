#include <stdio.h> // scanf, printf
#include <stdlib.h> // rand, srand
#include <time.h> // time
#include <algorithm> // swap

using namespace std;

struct heap {
    heap *l, *r;
    int val;
} *h;

heap* merge(heap *h1, heap *h2) { // Ενώνει τις δύο heap h1 και h2
    if(h1==NULL) {
        return h2;
    }
    if(h2==NULL) {
        return h1;
    }

    if(h2->val < h1->val) {
        swap(h1, h2);
    }
    if(rand()%2==1) {
        swap(h1->l, h1->r);
    }

    h1->l=merge(h1->l, h2);
    return h1;
}

void insert(int val) { // Εισάγει την τιμή val στην heap
    heap *h1=(heap*)malloc(sizeof(heap));
    h1->l=NULL;
    h1->r=NULL;
    h1->val=val;
    h=merge(h1, h);
}

int find_min() { // Τυπώνει την ελάχιστη τιμή της heap
    return h->val;
}

void delete_min() { // Αφαιρεί την ελάχιστη τιμή από την heap
    h=merge(h->l, h->r);
}

int main() {
    srand(time(NULL));
    int N, num;
    scanf("%d", &N);
    for(int i=1; i<=N; ++i) {
        scanf("%d", &num);
        insert(num);
    }

    for(int i=1; i<=N; ++i) {
        num=find_min();
        delete_min();
        printf("%d ", num);
    }
    printf("\n");
    return 0;
}

