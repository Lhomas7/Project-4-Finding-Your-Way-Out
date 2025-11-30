#ifndef UNIONFIND_H
#define UNIONFIND_H

#include <iostream>
#include <vector>

class UnionFind {
	public:
		UnionFind(int);
		int find(int);
		void unite(int, int);
		bool connected(int, int);

	private:
		std::vector<int> parent;
};

#endif

#include "UnionFind.tpp"