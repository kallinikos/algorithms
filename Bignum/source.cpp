#include <stdio.h> // scanf, printf
#include <string.h> // strlen, memset

#define llint long long
#define MAXDIG 16
#define POWR 9
#define BASE 1000000000 //= 10^POWR = 10^9

struct bignum { //Ο μέγιστος αριθμός είναι 10^(POWR*MAXDIG)-1 = 10^144-1
    int d[MAXDIG]; // Ο πίνακας αυτός αποτελείται από sizeof(int)*MAXDIG = 4*16 = 64 bytes

    void print() { // Τυπώνει τον αριθμό
        bool started=false;
        for(int i=MAXDIG-1; i>=0; --i) {
            if(!started && d[i]==0) {
                continue;
            }
            if(!started) {
                started=true;
                printf("%d", d[i]);
            }
            else {
                if(d[i]<0) {
                    printf("%.9d", -d[i]);
                }
                else {
                    printf("%.9d", d[i]);
                }
            }
        }
        if(!started) {
            printf("0");
        }
    }

    void to_bignum(char *str) { // Μετατρέπει το str σε bignum. Το str είναι βάση 10, και το most significant bit είναι το δεξιότερο
        int S, powr[POWR];
        powr[0]=1;
        if(str[0]=='-') {
            powr[0]=-1;
            ++str;
        }
        S=strlen(str);
        for(int i=1; i<POWR; ++i) {
            powr[i]=powr[i-1]*10;
        }

        memset(d, 0, sizeof(d));
        for(int i=0; i<S; ++i) {
            d[i/POWR]+=powr[i%POWR]*(str[S-i-1]-'0');
        }
    }
} ZERO;

bignum abs(bignum val) { // Επιστρέφει την απόλυτη τιμή του αριθμού
    for(int i=0; i<MAXDIG; ++i) {
        if(val.d[i]<0) {
            val.d[i]=-val.d[i];
        }
    }
    return val;
}

bignum neg(bignum val) { // Επιστρέφει το αρνητικό του αριθμού val
    for(int i=0; i<MAXDIG; ++i) {
        val.d[i]=-val.d[i];
    }
    return val;
}

bool comp(bignum u, bignum v) { // Επιστρέφει true μόνο όταν u<v
    for(int i=MAXDIG-1; i>=0; --i) {
        if(u.d[i]==v.d[i]) {
            continue;
        }
        return u.d[i]<v.d[i];
    }
    return false; // Εάν έχουμε φτάσει μέχρι εδώ u=v
}

bignum add_unsigned(bignum u, bignum v) { // Επιστρέφει το άθροισμα u+v θεωρώντας ότι θα είναι θετικό
    bignum out;
    int carry=0;
    memset(&out, 0, sizeof(out));
    for(int i=0; i<MAXDIG; ++i) {
        out.d[i]=u.d[i]+v.d[i]+carry;
        if(out.d[i]>=BASE) {
            carry=1;
        }
        else if(out.d[i]<0) {
            carry=-1;
        }
        out.d[i]-=carry*BASE;
    }
    return out;
}

bignum add(bignum u, bignum v) { // Επιστρέφει το άθροισμα u+v
    if(comp(abs(u), abs(v))) {
        return add(v, u);
    }
    if(comp(u, ZERO)) {
        return neg(add_unsigned(neg(u),neg(v)));
    }
    return add_unsigned(u,v);
}

bignum subtract(bignum u, bignum v) { // Επιστρέφει τη διαφορά u-v
    return add(u,neg(v));
}

bignum mult(bignum u, bignum v) { // Επιστρέφει το γινόμενο u*v
    if(comp(ZERO, u) != comp(ZERO, v)) {
        return neg(mult(abs(u), abs(v)));
    }
    bignum out;
    llint carry=0, tmp;
    memset(&out, 0, sizeof(out));

    for(int i=0; i<MAXDIG; ++i) {
        for(int j=0; i+j<MAXDIG; ++j) {
            tmp=u.d[i]*(llint)v.d[j]+out.d[i+j]+carry;
            out.d[i+j]=tmp%BASE;
            carry=tmp-(llint)out.d[i+j];
            carry/=BASE;
        }
    }

    return out;
}

int main() {
    char str1[MAXDIG], str2[MAXDIG], op;
    scanf("%s %c %s", str1, &op, str2);
    bignum A,B;
    A.to_bignum(str1);
    B.to_bignum(str2);
    if(op=='+') {
        add(A,B).print();
    }
    else if(op=='-') {
        subtract(A,B).print();
    }
    else if(op=='*') {
        mult(A,B).print();
    }
    printf("\n");
    return 0;
}

