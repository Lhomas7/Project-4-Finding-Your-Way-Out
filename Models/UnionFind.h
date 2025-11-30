#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <iostream>
#include <vector>

class UnionFind {
	std::vector<int> parent;

	public:
		UnionFind(int);
		int find(int);
		void unite(int, int);
		bool connected(int, int);
};

#endif