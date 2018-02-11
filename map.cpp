#include "map.hpp"
using namespace std;
map::map(){
	start_X = 0;
	start_Y = 0;
	goal_X = 0; 
	goal_Y = 0; 
	width = 0; 
	height = 0;
}

map::map(const &map other){
	start_X = other.get_start_X();
	start_Y = other.get_start_Y();
	goal_X = other.get_goal_X(); 
	goal_Y = other.get_goal_Y(); 
	width = other.get_width(); 
	height = other.get_height();
}

bool load_map(string filename){

}

int map::X_coordinate(int position){
	return position%width;
}
int map::Y_coordiante(int position){
	int retval = 1.0*position;
	return (int)ceil(position/width);
}