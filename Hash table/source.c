#include <stdio.h> // scanf, printf
#include <stdlib.h> // malloc
#include <string.h> // memcpy, strlen, strcmp

#define MAXHASH 1000003 // Είναι πρώτος αριθμός, άρα μειώνει τα collisions. Ανά πάσα στιγμή, το hash table πρέπει να έχει λιγότερες από MAXHASH λέξεις!
#define WORDSIZE 32 // Το μέγιστο μέγεθος της κάθε λέξης (προσοχή! πρέπει να υπάρχει χώρος για έναν έξτρα χαρακτήρα στο τέλος που υποδηλώνει το τέλος της λέξης, οπότε στην πραγματικότητα το μέγιστο μέγεθος λέξης είναι 31)

char keys[MAXHASH][WORDSIZE];
int values[MAXHASH];

int hash(char *key) { // Επιστρέφει έναν ακέραιο που αντιστοιχεί στο δεδομένο κλειδι. Για κάθε key1, key2, P[hash(key1)==hash(key2)]<=1/MAXHASH
    long long out=0;
    int s=strlen(key);
    for(int i=0; i<s; ++i) {
        out<<=8;
        out+=key[i];
        out%=MAXHASH;
    }
    return (int)out;
}

void Insert(char *key, int value) { // Εισάγει το ζευγάρι (key,value) στο hash table.
    int pos=hash(key);
    for(; keys[pos][0]!=0; pos=(pos+1)%MAXHASH) {
        if(strcmp(key, keys[pos])==0) {
            values[pos]=value;
            return;
        }
    }
    memcpy(keys[pos], key, strlen(key)+1);
    values[pos]=value;
}

void Delete(char *key) { // Αφαιρεί το κλειδί key (και το αντίστοιχο value) από το hash table.
    for(int pos=hash(key); keys[pos][0]!=0; pos=(pos+1)%MAXHASH) {
        if(strcmp(key, keys[pos])==0) {
            keys[pos][0]=0;
            return;
        }
    }
}

int Query(char *key) { // Επιστρέφει τη θέση στο hash table στην οποία βρίσκεται το key. Εάν δεν υπάρχει το key, τότε επιστρέφει -1.
    for(int pos=hash(key); keys[pos][0]!=0; pos=(pos+1)%MAXHASH) {
        if(strcmp(key, keys[pos])==0) {
            return pos;
        }
    }
    return -1;
}

int main() {
    int Q, value;
    char key[WORDSIZE], op;
    scanf("%d\n", &Q);
    for(int i=1; i<=Q; ++i) {
        scanf("%c", &op);
        if(op=='I') {
            scanf("%s %d\n", key, &value);
            Insert(key, value);
        }
        else if(op=='D') {
            scanf("%s\n", key);
            Delete(key);
        }
        else if(op=='Q') {
            scanf("%s\n", key);
            int pos=Query(key);
            if(pos==-1) {
                printf("Key does not exist!\n");
            }
            else {
                printf("%d\n", values[pos]);
            }
        }
    }
}
