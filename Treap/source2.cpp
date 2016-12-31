#include <stdio.h> // scanf, printf
#include <stdlib.h> // rand, srand
#include <time.h> // time
#include <algorithm> // swap

using namespace std;

#define MAXPRIOR 0x3f3f3f3f

struct el {
    el *lft, *rgt;
    int val, prior, siz;
    bool islazy;

    el(int val) {
        this->val=val;
        prior=rand()%MAXPRIOR;
        siz=1;
        islazy=false;
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

void propagate(el *now) { // Ενημερώνει τα παιδιά του now για το αν έχουν αντιστραφεί τα στοιχεία τους
    if(now==NULL || !now->islazy) {
        return;
    }
    swap(now->lft, now->rgt);
    if(now->lft!=NULL) {
        now->lft->islazy^=true;
    }
    if(now->rgt!=NULL) {
        now->rgt->islazy^=true;
    }
    now->islazy=false;
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

    propagate(lft);
    propagate(rgt);

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

void Split(elpt now, elpt &lft, elpt &rgt, int pos, int offset=0) { // Χωρίζει την treap now στις treaps lft και rgt με βάση την θέση pos
    if(now==NULL) {
        lft=NULL;
        rgt=NULL;
        return;
    }

    propagate(now);
    int nowpos=siz(now->lft)+offset;

    if(nowpos<=pos) {
        Split(now->rgt, now->rgt, rgt, pos, nowpos+1);
        lft=now;
    }
    else {
        Split(now->lft, lft, now->lft, pos, offset);
        rgt=now;
    }

    update(lft);
    update(rgt);
}

void Insert(int pos, int val) { // Βάζει ένα στοιχείο στη θέση pos το οποίο έχει τιμή val, και μετακινεί τα στοιχεία μετά από αυτό μία θέση προς τα δεξιά
    el *tmp=new el(val), *t1, *t2;
    Split(root, t1, t2, pos-1);
    Merge(t1, t1, tmp);
    Merge(root, t1, t2);
}

void Delete(int pos) { // Σβήνει το στοιχείο στη θέση pos, και μετακινεί τα στοιχεία μετά από αυτό μία θέση προς τα αριστερά
    el *t1, *t2;
    Split(root, root, t2, pos);
    Split(root, t1, root, pos-1);
    Merge(root, t1, t2);
}

void Reverse(int from, int to) { // Αντιστρέφει τη σειρά των στοιχείων από τη θέση from μέχρι και τη θέση to
    el *t1, *t2;
    Split(root, root, t2, to);
    Split(root, t1, root, from-1);
    root->islazy^=true;
    Merge(root, t1, root);
    Merge(root, root, t2);
}

int Find(int pos) { // Επιστρέφει την τιμή του στοιχείου στη θέση pos
    el *t1, *t2;
    Split(root, root, t2, pos);
    Split(root, t1, root, pos-1);
    int out=root->val;
    Merge(root, t1, root);
    Merge(root, root, t2);
    return out;
}

int main() {
    int Q, pos, val, from, to;
    char op;
    scanf("%d\n", &Q);
    srand(time(NULL));
    for(int i=1; i<=Q; ++i) {
        scanf("%c", &op);
        if(op=='I') {
            scanf("%d %d\n", &pos, &val);
            Insert(pos, val);
        }
        else if(op=='D') {
            scanf("%d\n", &pos);
            Delete(pos);
        }
        else if(op=='R') {
            scanf("%d %d\n", &from, &to);
            Reverse(from, to);
        }
        else if(op=='F') {
            scanf("%d", &pos);
            printf("%d\n", Find(pos));
        }
    }
    return 0;
}

