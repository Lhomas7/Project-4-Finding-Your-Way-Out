#include "UnionFind.h"

UnionFind::UnionFind(int n) : parent{}, rank(10, 0) {
    parent.reserve(n);
    for (int i = 0; i < n; ++i) {
        parent.push_back(i);
    }

}

int UnionFind::find(int n) {
    if (parent[n] == n) return n;
    parent[n] = find(parent[n]);
    return parent[n];
}

void UnionFind::unite(int i, int j) {
    int parentI = find(i);
    int parentJ = find(j);

    if (parentI == parentJ) {
        std::cout << "same tree" << std::endl;
    }

    if (rank[parentI] < rank[parentJ]) {
        parent[parentI] = parentJ;
    }
    else if (rank[parentI > rank[parentJ]]) {
        parent[parentJ] = parentI;
    }
    else {
        parent[parentJ] = parentI;
        rank[parentI] += 1;
    }
}

bool UnionFind::connected(int x, int y) {
    return find(x) == find(y);
}