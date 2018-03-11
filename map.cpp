#include "map.hpp"

using namespace std;

/* Map constructor
 * creates a new map from a input text filename
 * stores the maze in the Map class
 */
Map::Map(string filename, string outputname){
	// find the width and height of the maze
	string line;
	ifstream myfile (filename);
	if(myfile.is_open()) {
		getline(myfile, line);
		width = line.length();
		height = 1;
		while(getline(myfile, line)) {
			height++;
		}
		myfile.close();
	}

	// creates a new maze
	maze = new char*[width];
	for(int i = 0; i < width; i++)
		maze[i] = new char[height];

	// finds goals and player position
	point goals_[50];
	numGoals = 0;
	int h = 0;
	myfile.open(filename, std::ifstream::in);
	while(getline(myfile, line)) {
		for(unsigned w = 0; w < line.length(); w++) {
			maze[w][h] = line[w];
			// player
			if(maze[w][h] == 'P') {
				start.x = w;
				start.y = h;
				start.distance = 0;
			}
			// goals
			else if(maze[w][h] == '.') {
				goals_[numGoals].x = w;
				goals_[numGoals].y = h;
				numGoals++;
			}
		}
		h++;
	}
	myfile.close();
	outputfilename = outputname;

	// store goals in Map class
	goals = new point[numGoals];
	for(int i = 0; i < numGoals; i++)
		goals[i] = goals_[i];
}

/* printMaze
 * prints a solved maze, path cost, and number of nodes expanded
 */
void Map::printMaze() {
	// prints a console output
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			cout << maze[w][h];
		}
		cout << '\n';
	}
	cout << "Path cost: " << pathLength << endl;
	cout << "Number of nodes expanded: " << numExpanded << endl;

	// creates an output file (same as console output)
	ofstream myfile;
	myfile.open(outputfilename);
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			myfile << maze[w][h];
		}
		myfile << '\n';
	}
	myfile << "Path cost: " << pathLength << endl;
	myfile << "Number of nodes expanded: " << numExpanded << endl;
}

/* DFS
 * finds the path to the goal using depth-first search algorithm
 */
void Map::DFS() {
	// using stack for DFS
	stack<point> s;
	point p;

	// creates visited variable for each grid
	bool** visited = new bool*[width];
	for(int i = 0; i < width; i++) {
		visited[i] = new bool[height];
		for(int j = 0; j < height; j++)
			visited[i][j] = false;
	}

	// creates previous variable for each grid, for temporary path tracking
	point** previous = new point*[width];
	for(int i = 0; i < width; i++)
		previous[i] = new point[height];

	// creates path variable for each grid, for actual path tracking
	point** path = new point*[width];
	for(int i = 0; i < width; i++)
		path[i] = new point[height];

	// starts depth-first search
	numExpanded = 0;
	bool b = false;
	s.push(start);
	while(!s.empty()) {
		// get a new element from stack to search
		p = s.top();
		s.pop();

		// when ariving at goal, finish searching
		for(int i = 0; i < numGoals; i++) {
			if(goals[i].x == p.x && goals[i].y == p.y) {
				b = true;
				path[p.x][p.y] = previous[p.x][p.y];
				break;
			}
		}
		if(b) break;

		// if point is unvisited, push adjacent elements to the stack
		if(!visited[p.x][p.y]) {
			visited[p.x][p.y] = true;
			numExpanded++;
			path[p.x][p.y] = previous[p.x][p.y];

			// right
			if(maze[p.x + 1][p.y] != '%') {
				s.push(point{p.x + 1, p.y, 0});
				previous[p.x + 1][p.y] = p;
			}
			// left
			if(maze[p.x - 1][p.y] != '%') {
				s.push(point{p.x - 1, p.y, 0});
				previous[p.x - 1][p.y] = p;
			}
			// down
			if(maze[p.x][p.y + 1] != '%') {
				s.push(point{p.x, p.y + 1, 0});
				previous[p.x][p.y + 1] = p;
			}
			// up
			if(maze[p.x][p.y - 1] != '%') {
				s.push(point{p.x, p.y - 1, 0});
				previous[p.x][p.y - 1] = p;
			}
		}
	}

	// obtain path by backtracking path variable
	pathLength = 0;
	while(p != start) {
		maze[p.x][p.y] = '.';
		p = path[p.x][p.y];
		pathLength++;
	}
}

/* BFS
 * finds the path to the goal using breadth-first search algorithm
 */
void Map::BFS() {
	// using queue for BFS
	queue<point> q;
	point p;

	// creates visited variable for each grid
	bool** visited = new bool*[width];
	for(int i = 0; i < width; i++) {
		visited[i] = new bool[height];
		for(int j = 0; j < height; j++)
			visited[i][j] = false;
	}

	// creates previous variable for each grid, for temporary path tracking
	point** previous = new point*[width];
	for(int i = 0; i < width; i++)
		previous[i] = new point[height];

	// creates path variable for each grid, for actual path tracking
	point** path = new point*[width];
	for(int i = 0; i < width; i++)
		path[i] = new point[height];

	// starts breadth-first search
	numExpanded = 0;
	bool b = false;
	q.push(start);
	while(!q.empty()) {
		// get a new element from queue to search
		p = q.front();
		q.pop();

		// when ariving at goal, finish searching
		for(int i = 0; i < numGoals; i++) {
			if(goals[i].x == p.x && goals[i].y == p.y) {
				b = true;
				path[p.x][p.y] = previous[p.x][p.y];
				break;
			}
		}
		if(b) break;

		// if point is unvisited, push adjacent elements to the queue
		if(!visited[p.x][p.y]) {
			visited[p.x][p.y] = true;
			numExpanded++;
			path[p.x][p.y] = previous[p.x][p.y];

			// down
			if(maze[p.x][p.y + 1] != '%') {
				q.push(point{p.x, p.y + 1, 0});
				previous[p.x][p.y + 1] = p;
			}
			// right
			if(maze[p.x + 1][p.y] != '%') {
				q.push(point{p.x + 1, p.y, 0});
				previous[p.x + 1][p.y] = p;
			}
			// up
			if(maze[p.x][p.y - 1] != '%') {
				q.push(point{p.x, p.y - 1, 0});
				previous[p.x][p.y - 1] = p;
			}
			// left
			if(maze[p.x - 1][p.y] != '%') {
				q.push(point{p.x - 1, p.y, 0});
				previous[p.x - 1][p.y] = p;
			}
		}
	}

	// obtain path by backtracking path variable
	pathLength = 0;
	while(p != start) {
		maze[p.x][p.y] = '.';
		p = path[p.x][p.y];
		pathLength++;
	}
}

/* Greedy_BFS
 * finds the path to the goal using greedy-best-first search algorithm
 */
void Map::Greedy_BFS() {
	start.goal = goals[0];
	// using priority queue for Greedy BFS
	priority_queue<point, vector<point>, greater<point>> q;
	point p;

	// creates visited variable for each grid
	bool** visited = new bool*[width];
	for(int i = 0; i < width; i++) {
		visited[i] = new bool[height];
		for(int j = 0; j < height; j++)
			visited[i][j] = false;
	}

	// creates previous variable for each grid, for temporary path tracking
	point** previous = new point*[width];
	for(int i = 0; i < width; i++)
		previous[i] = new point[height];

	// creates path variable for each grid, for actual path tracking
	point** path = new point*[width];
	for(int i = 0; i < width; i++)
		path[i] = new point[height];

	// starts greedy best-first search
	numExpanded = 0;
	bool b = false;
	q.push(start);
	while(!q.empty()) {
		// get a new element from priority queue to search
		p = q.top();
		q.pop();

		// when ariving at goal, finish searching
		for(int i = 0; i < numGoals; i++) {
			if(goals[i].x == p.x && goals[i].y == p.y) {
				b = true;
				path[p.x][p.y] = previous[p.x][p.y];
				break;
			}
		}
		if(b) break;

		// if point is unvisited, push adjacent elements to the priority queue
		if(!visited[p.x][p.y]) {
			visited[p.x][p.y] = true;
			numExpanded++;
			path[p.x][p.y] = previous[p.x][p.y];

			// right
			if(maze[p.x + 1][p.y] != '%') {
				q.push(point{p.x + 1, p.y, 0});
				previous[p.x + 1][p.y] = p;
			}
			// left
			if(maze[p.x - 1][p.y] != '%') {
				q.push(point{p.x - 1, p.y, 0});
				previous[p.x - 1][p.y] = p;
			}
			// down
			if(maze[p.x][p.y + 1] != '%') {
				q.push(point{p.x, p.y + 1, 0});
				previous[p.x][p.y + 1] = p;
			}
			// up
			if(maze[p.x][p.y - 1] != '%') {
				q.push(point{p.x, p.y - 1, 0});
				previous[p.x][p.y - 1] = p;
			}
		}
	}

	// obtain path by backtracking path variable
	pathLength = 0;
	while(p != start) {
		maze[p.x][p.y] = '.';
		p = path[p.x][p.y];
		pathLength++;
	}
}

/* A_Star
 * finds the path to the goal using A* search algorithm
 */
void Map::A_Star() {
	start.goal = goals[0];
	// using priority queue for A*
	priority_queue<point, vector<point>, greater<point>> q;
	point p;

	// creates visited variable for each grid
	bool** visited = new bool*[width];
	for(int i = 0; i < width; i++) {
		visited[i] = new bool[height];
		for(int j = 0; j < height; j++)
			visited[i][j] = false;
	}

	// creates previous variable for each grid, for temporary path tracking
	point** previous = new point*[width];
	for(int i = 0; i < width; i++)
		previous[i] = new point[height];

	// creates path variable for each grid, for actual path tracking
	point** path = new point*[width];
	for(int i = 0; i < width; i++)
		path[i] = new point[height];

	// creates a dist variable for each grid, for distance travelled from start
	int** dist = new int*[width];
	for(int i = 0; i < width; i++) {
		dist[i] = new int[height];
		for(int j = 0; j < height; j++)
			dist[i][j] = 99999;
	}

	// starts A* search
	numExpanded = 0;
	bool b = false;
	q.push(start);
	while(!q.empty()) {
		// get a new element from priority queue to search
		p = q.top();
		q.pop();

		// when ariving at goal, finish searching
		for(int i = 0; i < numGoals; i++) {
			if(goals[i].x == p.x && goals[i].y == p.y) {
				b = true;
				path[p.x][p.y] = previous[p.x][p.y];
				break;
			}
		}
		if(b) break;

		// if point is unvisited, push adjacent elements to the priority queue
		if(!visited[p.x][p.y]) {
			visited[p.x][p.y] = true;
			numExpanded++;
			path[p.x][p.y] = previous[p.x][p.y];

			// right
			if(maze[p.x + 1][p.y] != '%' && dist[p.x + 1][p.y] > p.distance + 1) {
				dist[p.x + 1][p.y] = p.distance + 1;
				q.push(point{p.x + 1, p.y, p.distance + 1});
				previous[p.x + 1][p.y] = p;
			}
			// left
			if(maze[p.x - 1][p.y] != '%' && dist[p.x - 1][p.y] > p.distance + 1) {
				dist[p.x - 1][p.y] = p.distance + 1;
				q.push(point{p.x - 1, p.y, p.distance + 1});
				previous[p.x - 1][p.y] = p;
			}
			// down
			if(maze[p.x][p.y + 1] != '%' && dist[p.x][p.y + 1] > p.distance + 1) {
				dist[p.x][p.y + 1] = p.distance + 1;
				q.push(point{p.x, p.y + 1, p.distance + 1});
				previous[p.x][p.y + 1] = p;
			}
			// up
			if(maze[p.x][p.y - 1] != '%' && dist[p.x][p.y - 1] > p.distance + 1) {
				dist[p.x][p.y - 1] = p.distance + 1;
				q.push(point{p.x, p.y - 1, p.distance + 1});
				previous[p.x][p.y - 1] = p;
			}
		}
	}

	// obtain path by backtracking path variable
	pathLength = 0;
	while(p != start) {
		maze[p.x][p.y] = '.';
		p = path[p.x][p.y];
		pathLength++;
	}
}

/* Multiple
 * finds the optimal path to obtain multiple goals
 */
void Map::Multiple() {
	// finds the distance between ALL the goals (nodes)
	vector<vector<int>> distances_all(numGoals + 1);
	for(int i = 0; i < numGoals + 1; i++)
		distances_all[i] = vector<int>(numGoals + 1);
	for(int i = 0; i < numGoals + 1; i++) {
		for(int j = i + 1; j < numGoals + 1; j++) {
			distances_all[i][j] = BFS_Multiple(i, j);
			distances_all[j][i] = distances_all[i][j]
		}
	}

	// for each node, finds the distance to closest adjacent node
	// sum of these from unvisited nodes gives heuristics
	int min;
	vector<int> mins = vector<int>(numGoals + 1);
	for(int i = 0; i < numGoals + 1; i++) {
		min = 99999;
		for(int j = 0; j < numGoals + 1; j++) {
			if(i == j) continue;
			if(min > distances_all[i][j])
				min = distances_all[i][j];
		}
		mins[i] = min;
	}

	// creates visited variable for each node
	node n = node();
	n.mins = mins;
	node nn = node();
	vector<bool> visited = vector<bool>(numGoals + 1);
	for(int i = 0; i < numGoals + 1; i++)
		visited[i] = false;

	// creates a starting node and put it in the priority queue
	node startNode = node(numGoals, 0, distances_all[numGoals], visited);
	startNode.order = vector<int>();
	priority_queue<node, vector<node>, greater<node>> q;
	q.push(startNode);

	// starts the A* search for nodes
	bool b = false;
	numExpanded = 0;
	while(!q.empty()) {
		n = q.top();
		q.pop();

		// if node is unvisited, push new unvisited adjacents to the priority queue
		if(!n.visited[n.id]) {
			n.visited[n.id] = true;
			numExpanded++;

			// when ariving at goal, finish searching
			for(int i = 0; i < numGoals + 1; i++) {
				if(!n.visited[i]) break;
				if(i == numGoals) b = true;
			}
			if(b) break;

			// push new unvisited adjacent to the priority queue
			for(int i = 0; i < numGoals; i++) {
				if(i == n.id) continue;
				if(n.visited[i]) continue;
				nn = n;
				nn.id = i;
				nn.distance += n.adjacent[i];
				nn.adjacent = distances_all[i];
				nn.order.push_back(i);
				q.push(nn);
			}
		}
	}

	// obtain path by backtracking and modify maze accordingly
	pathLength = n.distance;
	for(int i = 0; i < numGoals; i++) {
		if(i < 10)
			maze[goals[n.order[i]].x][goals[n.order[i]].y] = (char) i + 48;
		else if(i < 36)
			maze[goals[n.order[i]].x][goals[n.order[i]].y] = (char) i + 87;
		else
			maze[goals[n.order[i]].x][goals[n.order[i]].y] = (char) i + 29;
	}
}

/* BFS_Multiple
 * BFS algorithm to find shortest path between two points
 * input: start_: starting position, end_: ending position
 * output: length of shortest path between start and end position
 */
int Map::BFS_Multiple(int start_, int end_) {
	// assign points to given goal id
	point start_point, end_point;
	if(start_ == numGoals)
		start_point = start;
	else
		start_point = goals[start_];
	if(end_ == numGoals)
		end_point = start;
	else
		end_point = goals[end_];

	// using queue for BFS
	queue<point> q;
	point p;

	// creates visited variable for each grid
	bool** visited = new bool*[width];
	for(int i = 0; i < width; i++) {
		visited[i] = new bool[height];
		for(int j = 0; j < height; j++)
			visited[i][j] = false;
	}

	// creates previous variable for each grid, for temporary path tracking
	point** previous = new point*[width];
	for(int i = 0; i < width; i++)
		previous[i] = new point[height];

	// creates path variable for each grid, for actual path tracking
	point** path = new point*[width];
	for(int i = 0; i < width; i++)
		path[i] = new point[height];

	// starts BFS search
	numExpanded = 0;
	q.push(start_point);
	while(!q.empty()) {
		p = q.front();
		q.pop();

		// when arriving at endpoint finish searching
		if(end_point == p) {
			path[p.x][p.y] = previous[p.x][p.y];
			break;
		}

		// if point is unvisited, push adjacent elements to the queue
		if(!visited[p.x][p.y]) {
			visited[p.x][p.y] = true;
			numExpanded++;
			path[p.x][p.y] = previous[p.x][p.y];

			// down
			if(maze[p.x][p.y + 1] != '%') {
				q.push(point{p.x, p.y + 1, 0});
				previous[p.x][p.y + 1] = p;
			}
			// right
			if(maze[p.x + 1][p.y] != '%') {
				q.push(point{p.x + 1, p.y, 0});
				previous[p.x + 1][p.y] = p;
			}
			// up
			if(maze[p.x][p.y - 1] != '%') {
				q.push(point{p.x, p.y - 1, 0});
				previous[p.x][p.y - 1] = p;
			}
			// left
			if(maze[p.x - 1][p.y] != '%') {
				q.push(point{p.x - 1, p.y, 0});
				previous[p.x - 1][p.y] = p;
			}
		}
	}

	// obtain path by backtracking path variable
	pathLength = 0;
	while(p != start_point) {
		//maze[p.x][p.y] = '.';
		p = path[p.x][p.y];
		pathLength++;
	}

	// delete all dynamically allocated variables
	for(int i = 0; i < width; i++) {
		delete visited[i];
		delete previous[i];
		delete path[i];
	}
	delete visited;
	delete previous;
	delete path;

	// return length of shortest path
	return pathLength;
}
