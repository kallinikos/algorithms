/*
Min Li Chao Segment Tree για το πλήρως δυναμικό Convex Hull Trick (CHT).
*/

#include <algorithm>
#include <cstdio>

using namespace std;

// Προσέξτε για overflows όταν επιλέγετε τύπο μεταβλητής!
typedef long long ftype;

const int MAX_N = 1e5 + 5;

struct line {
    ftype m, b;
} tree[MAX_N * 4];

ftype func(line f, ftype x) {
    return f.m * x + f.b;
}

// Αρχικοποιούμε με μία ακραία τιμή που ποτέ δεν
// πρόκειται να είναι η απάντηση.
void init() {
    // Αλλάξτε αυτό για το max CHT ή αν χρειάζεστε
    // μικρότερο τύπο μεταβλητής από long long.
    line sentinel = (line){0, (ftype)1e18};
    fill(tree, tree + MAX_N * 4, sentinel);
}

void add_line(int p, int L, int R, line nw) {
    int left = p << 1, right = left | 1;
    int mid = (L + R) >> 1;
    // Αλλάξτε τη σειρά σύγκρισης στις δυο επόμενες γραμμές
    // για το MAX CHT.
    bool left_check = func(nw, L) < func(tree[p], L);
    bool mid_check = func(nw, mid) < func(tree[p], mid);
    if (mid_check)
        swap(tree[p], nw);
    if (L == R)
        return;
    if (left_check != mid_check) {
        add_line(left, L, mid, nw);
    }
    else {
        add_line(right, mid + 1, R, nw);
    }
}

// Προσέξτε ότι το x θα πρέπει να είναι
// μεταξύ του L και του R.
ftype query(int p, int L, int R, int x) {
    ftype res = func(tree[p], x);
    if (L == R)
        return res;
    int left = p << 1, right = left | 1;
    int mid = (L + R) >> 1;
    if (x <= mid) {
        // Αλλάξτε το min σε max αν θέλετε το max CHT.
        return min(res, query(left, L, mid, x));
    }
    else {
        // Αλλάξτε το min σε max αν θέλετε το max CHT.
        return min(res, query(right, mid + 1, R, x));
    }
}

int main() {
    init();
    add_line(1, 0, MAX_N - 1, (line){1, -325});
    add_line(1, 0, MAX_N - 1, (line){-100, 3});
    add_line(1, 0, MAX_N - 1, (line){1000, -3421});
    printf("%lld\n", query(1, 0, MAX_N - 1, 24123));
    printf("%lld\n", query(1, 0, MAX_N - 1, 154));
    return 0;
}

