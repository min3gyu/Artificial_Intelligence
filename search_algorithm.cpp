#include "search_algorithm.hpp"

using namespace std;

algorithm::algorithm(){
	step = 0;
	node = 0;
}

int algorithm::DFS(map* maze){
	stack<int> path;
	vector<int> visited;
	//row-major
	int start_point = maze->get_start_X() + maze->get_width() * maze->get_start_Y();
	int goal = maze->get_goal_X() + maze->get_width() * maze->get_goal_Y(); 
	//check the initial point is goal point.
	if(start_point == goal){
		return step;
	}
	path.push(start_point);

	while(!path.empty()){
		int current = path.top();
		if(first_visted(current)){
			visited.push_back(current);
			map[current] = '.';
			step++;
			path.pop();
			int NEWS[4] = {}; //up(N), right(E), down(S), left(W)
			char adjacent_path[4] = {'\0', '\0', '\0', '\0'}; 

			NEWS[0] = current - maze->get_width();
			NEWS[1] = current + 1;
			NEWS[2] = current + maze->get_width();
			NEWS[3] = current - 1;

			adjacent_path[0] = maze[NEWS[0]]; // up
			adjacent_path[1] = maze[NEWS[1]]; // right
			adjacent_path[2] = maze[NEWS[2]]; // down
			adjacent_path[3] = maze[NEWS[3]]; // left
			//check those positions are within boundary && already visited
			for(int i=0; i<4; i++){
				int next_position = NEWS[i];
				//reach the new path
				if(within_boundary(next_position) && first_visted(next_position, visited) && (adjacent_path[i] == ' ')){
					//if conditions are true 
					path.push(next_position);
					node++;
				}
				//reach the goal case
				else if(within_boundary(next_position) && first_visted(next_position, visited) && (adjacent_path[i] == '.')){
					step++;
					return step;
				}
			}
		}
		else{
			path.pop();
		}
	}
}


int algorithm::BFS(map* maze){

	queue<int> path;
	vector<int> visited;

	//row-major 
	int start_point = maze->get_start_X() + maze->get_width() * maze->get_start_Y();
	int goal = maze->get_goal_X() + maze->get_width() * maze->get_goal_Y();
	//check the initial point is goal point.
	if(start_point == goal){
		return step;
	}
	path.push(start_point);

	while(!path.empty()){

		int current = path.front();
		visited.push_back(current); // add current position in visited vector
		map[current] = '.'
		step++;
		int NEWS[4] = {}; //up(N), right(E), down(S), left(W)
		char adjacent_path[4] = {'\0', '\0', '\0', '\0'}; 

		NEWS[0] = current - maze->get_width();
		NEWS[1] = current + 1;
		NEWS[2] = current + maze->get_width();
		NEWS[3] = current - 1;

		adjacent_path[0] = maze[NEWS[0]]; // up
		adjacent_path[1] = maze[NEWS[1]]; // right
		adjacent_path[2] = maze[NEWS[2]]; // down
		adjacent_path[3] = maze[NEWS[3]]; // left

		//check those positions are within boundary && already visited
		for(int i=0; i<4; i++){
			int next_position = NEWS[i];
			//reach the new path
			if(within_boundary(next_position) && first_visted(next_position, visited) && (adjacent_path[i] == ' ')){
				//if conditions are true 
				path.push(next_position);
				node++;
			}
			//reach the goal case
			else if(within_boundary(next_position) && first_visted(next_position, visited) && (adjacent_path[i] == '.')){
				step++;
				return step;
			}
		}
	}
}

int algorithm::Greedy_BFS(map* maze){

	queue<int> path;
	vector<int> visited;

	//row-major 
	int start_point = maze->get_start_X() + maze->get_width() * maze->get_start_Y();
	int goal = maze->get_goal_X() + maze->get_width() * maze->get_goal_Y();
	//check the initial point is goal point.
	if(start_point == goal){
		return step;
	}
	path.push(start_point);

	while(!path.empty()){

		int current = path.front();
		visited.push_back(current); // add current position in visited vector
		map[current] = '.'
		step++;
		int NEWS[4] = {}; //up(N), right(E), down(S), left(W)
		int m_distance[4] ={}; // node's manhattan distance (4 directions)
		int min = 0;  //minimum manhattan distance
		char adjacent_path[4] = {'\0', '\0', '\0', '\0'}; 

		NEWS[0] = current - maze->get_width();
		NEWS[1] = current + 1;
		NEWS[2] = current + maze->get_width();
		NEWS[3] = current - 1;

		adjacent_path[0] = maze[NEWS[0]]; // up
		adjacent_path[1] = maze[NEWS[1]]; // right
		adjacent_path[2] = maze[NEWS[2]]; // down
		adjacent_path[3] = maze[NEWS[3]]; // left

		//check those positions are within boundary && already visited
		for(int i=0; i<4 i++){
			m_distance[i] = manhattan_distance(NEWS[i]);
			if(min >= m_distance[i]){
				min = m_distance[i];
			}
		}
		/*
		qsort(m_distance, 4, sizeof(int), qsort_helper);
		min_d = m_distance[0];
		*/
		for(int i=0; i<4; i++){
			int next_position = NEWS[i];
			//reach the new path
			if((manhattan_distance(NEWS[i])==min) && within_boundary(next_position) && first_visted(next_position, visited) && (adjacent_path[i] == ' ')){
				//if conditions are true 
				path.push(next_position);
				node++;
			}
			//reach the goal case
			else if(within_boundary(next_position) && first_visted(next_position, visited) && (adjacent_path[i] == '.')){
				step++;
				return step;
			}
		}
	}
}
/* 
within_boundary(int position)
Description: Maze is already surrounded by wall '%'
			 so, we just check the index of maze_array is within range.
*/
bool algorithm::within_boundary(int position){
	int sizeofmaze = maze->get_width()*maze->get_hieght();
	if(position >=0 && position < sizeofmaze){
		return true;
	}
	return false;
}

bool algorithm::first_visted(int position, vector<int> &visited){
	vector<int>::iterator ptr;
	for(ptr=visited.begin(); ptr<visited.end(); ptr++){
		if(*ptr == position)
			return false;
	}
	return true;
}

int algorithm::manhattan_distance(int position){
	int x = abs(get_goal_X() - X_coordinate(position));
	int y = abs(get_goal_Y() - Y_coordinate(position));
	return (x+y);
}
/*
int alogrithm::qsort_helper(int* a, int* b){
	return (*a - *b);
}
*/






