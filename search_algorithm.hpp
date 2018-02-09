#ifndef __SEARCH_ALGORITHM_H__
#define __SEARCH_ALGORITHM_H__

#include <queue>
#include <stack>
#include <vector>
#include <stdio.h>

class algorithm{
	private:
		int step;
		int node;
	public:
		algorithm(); // initializer
		int DFS(map* maze);
		int BFS(map* maze);
		bool within_boundary(int position);
		bool first_visted(int position, vector<int> &visited);
};