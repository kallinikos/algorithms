#include <stdio.h> // scanf, printf
#include <stdlib.h> // rand, srand
#include <time.h> // time

#define MAXPRIOR 0x3f3f3f3f

struct el {
    el *lft, *rgt;
    int key, prior, siz;

    el(int key) {
        this->key=key;
        prior=rand()%MAXPRIOR;
        siz=1;
        lft=NULL;
        rgt=NULL;
    }
} *root;
typedef el* elpt;

int siz(el *now) { // Επιστρέφει το μέγεθος του υποδέντρου με ρίζα το now
    if(now==NULL) {
        return 0;
    }
    return now->siz;
}

void update(el *now) { // Ενημερώνει το μέγεθος του now
    if(now==NULL) {
        return;
    }
    now->siz=siz(now->lft)+siz(now->rgt)+1;
}

void Merge(elpt &now, elpt lft, elpt rgt) { // Ενώνει τις treaps lft και rgt και αποθηκεύει το αποτέλεσμα στο now
    if(lft==NULL) {
        now=rgt;
        return;
    }
    if(rgt==NULL) {
        now=lft;
        return;
    }

    if(lft->prior<rgt->prior) {
        Merge(lft->rgt, lft->rgt, rgt);
        now=lft;
    }
    else {
        Merge(rgt->lft, lft, rgt->lft);
        now=rgt;
    }

    update(now);
}

void Split(elpt now, elpt &lft, elpt &rgt, int key) { // Χωρίζει την treap now στις treaps lft και rgt με βάση το κλειδί key
    if(now==NULL) {
        lft=NULL;
        rgt=NULL;
        return;
    }

    if(now->key<=key) {
        Split(now->rgt, now->rgt, rgt, key);
        lft=now;
    }
    else {
        Split(now->lft, lft, now->lft, key);
        rgt=now;
    }

    update(lft);
    update(rgt);
}

void Insert(int val) { // Εισάγει ένα στοιχείο με κλειδί val στην treap
    el *tmp=new el(val), *t1, *t2;
    Split(root, t1, t2, val);
    Merge(t1, t1, tmp);
    Merge(root, t1, t2);
}

void Delete(int val) { // Σβήνει όλα τα στοιχεία με κλειδί val από την treap
    el *t1, *t2;
    Split(root, root, t2, val);
    Split(root, t1, root, val-1);
    Merge(root, t1, t2);
}

int FindPosition(int val) { // Βρίσκει την θέση του πρώτου στοιχείου με κλειδί val (εάν τα στοιχεία ήταν ταξινομημένα)
    el *t1, *t2;
    bool flag=true;
    Split(root, root, t2, val);
    Split(root, t1, root, val-1);
    if(root==NULL) {
        flag=false;
    }
    Merge(root, t1, root);
    Merge(root, root, t2);
    if(!flag) {
        return -1;
    }
    Split(root, t1, t2, val-1);
    int out=siz(t1);
    Merge(root, t1, t2);
    return out;
}

int main() {
    int Q, val;
    char op;
    scanf("%d\n", &Q);
    srand(time(NULL));
    for(int i=1; i<=Q; ++i) {
        scanf("%c %d\n", &op, &val);
        if(op=='I') {
            Insert(val);
        }
        else if(op=='D') {
            Delete(val);
        }
        else if(op=='P') {
            int tmp=FindPosition(val);
            if(tmp==-1) {
                printf("%d cannot be found\n", val);
            }
            else {
                printf("%d is in position %d\n", val, tmp);
            }
        }
    }
    return 0;
}

