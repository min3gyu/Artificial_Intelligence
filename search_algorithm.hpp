#ifndef __SEARCH_ALGORITHM_H__
#define __SEARCH_ALGORITHM_H__

#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdio.h>
using namespace std;

class algorithm{
	private:
		int step;
		int node;
	public:
		algorithm(); // initializer
		int DFS(map* maze);
		int BFS(map* maze);
		int Greedy_DFS(map* maze);
		bool within_boundary(int position);
		bool first_visted(int position, vector<int> &visited);;
		//int manhattan_distance(int position)
};