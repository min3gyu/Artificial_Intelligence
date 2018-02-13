#ifndef __MAP_H__
#define __MAP_H__

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <queue>

#include "point.hpp"

using namespace std;

/* point class
 * used in part 1 and 2:
 * the maze and its relevant information is stored in Map class
 * search algorithms implemented to find optimal paths
 */
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
		string outputfilename;
	public:
		Map(string filename, string outputname);
		void printMaze();
		void DFS();
		void BFS();
		void Greedy_BFS();
		void A_Star();
		int BFS_Multiple(int start_, int end_);
		void Multiple();
};

#endif
