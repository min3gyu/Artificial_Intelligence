#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

#include "point.hpp"

using namespace std;

class Map{
	private:
		char** maze;
		int width;
		int height;
		point start;
		point* goals;
		int numGoals;
		int numExpanded;
		int pathLength;
	public:
		Map(string filename);
		void printMaze();
		void DFS();
		void BFS();
		void Greedy_BFS();
		void A_Star();
		int BFS_Multiple(int start_, int end_);
		void Multiple();
};

#endif
