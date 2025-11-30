#include "UnionFind.h"

UnionFind::UnionFind(int n) : parent{} {
    parent.reserve(n);
    for (int i = 0; i < n; ++i) {
        parent.push_back(i);
    }

}

int UnionFind::find(int n) {
    if (parent[n] == n) return n;
    return find(parent[n]);
}

void UnionFind::unite(int i, int j) {
    int parentI = find(i);
    int parentJ = find(j);

    if (parentI == parentJ) {
        std::cout << "same tree" << std::endl;
    }
    else {
        parent[parentI] = parentJ;
    }
}

bool UnionFind::connected(int x, int y) {
    return find(x) == find(y);
}