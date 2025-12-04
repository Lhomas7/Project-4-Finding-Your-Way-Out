#include "UnionFind.h"
#include <algorithm>

UnionFind::UnionFind(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
    }

}

int UnionFind::find(int n) {
    if (parent[n] == n) return n;
    return parent[n] = find(parent[n]);
}

void UnionFind::unite(int i, int j) {
    int rootI = find(i);
    int rootJ = find(j);

    if (rootI != rootJ) {
        // Union by rank
        if (rank[rootI] < rank[rootJ]) {
            std::swap(rootI, rootJ); // Ensure rootI is the larger tree
        }
        parent[rootJ] = rootI;
        if (rank[rootI] == rank[rootJ]) {
            rank[rootI]++; // Increment rank only if they were equal
        }
    }
}

bool UnionFind::connected(int x, int y) {
    return find(x) == find(y);
}