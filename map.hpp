#ifndef __MAP_H__
#define __MAP_H__

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
class map{
	private:
		int start_X, start_Y, goal_X, goal_Y, width, height;
	public:
		map();
		map(const &map other);
		bool load_map(string filename);
		int get_start_X();
		int get_start_Y();
		int get_goal_X();
		int get_goal_Y();
		int get_width();
		int get_height();
		int X_coordinate(int position);
		int	Y_coordinate(int position);
};