#include "map.hpp"

using namespace std;

Map::Map(string filename){
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

	maze = new char*[width];
	for(int i = 0; i < width; i++)
		maze[i] = new char[height];

	point goals_[50];
	numGoals = 0;
	int h = 0;
	myfile.open(filename, std::ifstream::in);
	while(getline(myfile, line)) {
		for(unsigned w = 0; w < line.length(); w++) {
			maze[w][h] = line[w];
			if(maze[w][h] == 'P') {
				start.x = w;
				start.y = h;
				start.distance = 0;
			}
			else if(maze[w][h] == '.') {
				goals_[numGoals].x = w;
				goals_[numGoals].y = h;
				numGoals++;
			}
		}
		h++;
	}
	myfile.close();

	goals = new point[numGoals];
	for(int i = 0; i < numGoals; i++)
		goals[i] = goals_[i];
}

void Map::printMaze() {
	for(int h = 0; h < height; h++) {
		for(int w = 0; w < width; w++) {
			cout << maze[w][h];
		}
		cout << '\n';
	}
	cout << "Path cost: " << pathLength << endl;
	cout << "Number of nodes expanded: " << numExpanded << endl;
}

void Map::DFS() {
	stack<point> s;
	point p;
	bool** visited = new bool*[width];
	for(int i = 0; i < width; i++) {
		visited[i] = new bool[height];
		for(int j = 0; j < height; j++)
			visited[i][j] = false;
	}

	point** previous = new point*[width];
	for(int i = 0; i < width; i++)
		previous[i] = new point[height];

	point** path = new point*[width];
	for(int i = 0; i < width; i++)
		path[i] = new point[height];

	numExpanded = 0;
	bool b = false;
	s.push(start);
	while(!s.empty()) {
		p = s.top();
		s.pop();

		for(int i = 0; i < numGoals; i++) {
			if(goals[i].x == p.x && goals[i].y == p.y) {
				b = true;
				path[p.x][p.y] = previous[p.x][p.y];
				break;
			}
		}
		if(b) break;

		if(!visited[p.x][p.y]) {
			visited[p.x][p.y] = true;
			numExpanded++;
			path[p.x][p.y] = previous[p.x][p.y];

			if(maze[p.x + 1][p.y] != '%') {
				s.push(point{p.x + 1, p.y, 0});
				previous[p.x + 1][p.y] = p;
			}
			if(maze[p.x - 1][p.y] != '%') {
				s.push(point{p.x - 1, p.y, 0});
				previous[p.x - 1][p.y] = p;
			}
			if(maze[p.x][p.y + 1] != '%') {
				s.push(point{p.x, p.y + 1, 0});
				previous[p.x][p.y + 1] = p;
			}
			if(maze[p.x][p.y - 1] != '%') {
				s.push(point{p.x, p.y - 1, 0});
				previous[p.x][p.y - 1] = p;
			}
		}
	}

	pathLength = 0;
	while(p != start) {
		maze[p.x][p.y] = '.';
		p = path[p.x][p.y];
		pathLength++;
	}
}

void Map::BFS() {
	queue<point> q;
	point p;
	bool** visited = new bool*[width];
	for(int i = 0; i < width; i++) {
		visited[i] = new bool[height];
		for(int j = 0; j < height; j++)
			visited[i][j] = false;
	}

	point** previous = new point*[width];
	for(int i = 0; i < width; i++)
		previous[i] = new point[height];

	point** path = new point*[width];
	for(int i = 0; i < width; i++)
		path[i] = new point[height];

	numExpanded = 0;
	bool b = false;
	q.push(start);
	while(!q.empty()) {
		p = q.front();
		q.pop();

		for(int i = 0; i < numGoals; i++) {
			if(goals[i].x == p.x && goals[i].y == p.y) {
				b = true;
				path[p.x][p.y] = previous[p.x][p.y];
				break;
			}
		}
		if(b) break;

		if(!visited[p.x][p.y]) {
			visited[p.x][p.y] = true;
			numExpanded++;
			path[p.x][p.y] = previous[p.x][p.y];

			if(maze[p.x][p.y + 1] != '%') {
				q.push(point{p.x, p.y + 1, 0});
				previous[p.x][p.y + 1] = p;
			}
			if(maze[p.x + 1][p.y] != '%') {
				q.push(point{p.x + 1, p.y, 0});
				previous[p.x + 1][p.y] = p;
			}
			if(maze[p.x][p.y - 1] != '%') {
				q.push(point{p.x, p.y - 1, 0});
				previous[p.x][p.y - 1] = p;
			}
			if(maze[p.x - 1][p.y] != '%') {
				q.push(point{p.x - 1, p.y, 0});
				previous[p.x - 1][p.y] = p;
			}
		}
	}

	pathLength = 0;
	while(p != start) {
		maze[p.x][p.y] = '.';
		p = path[p.x][p.y];
		pathLength++;
	}
}

void Map::Greedy_BFS() {
	start.goal = goals[0];
	priority_queue<point, vector<point>, greater<point>> q;
	point p;
	bool** visited = new bool*[width];
	for(int i = 0; i < width; i++) {
		visited[i] = new bool[height];
		for(int j = 0; j < height; j++)
			visited[i][j] = false;
	}

	point** previous = new point*[width];
	for(int i = 0; i < width; i++)
		previous[i] = new point[height];

	point** path = new point*[width];
	for(int i = 0; i < width; i++)
		path[i] = new point[height];

	numExpanded = 0;
	bool b = false;
	q.push(start);
	while(!q.empty()) {
		p = q.top();
		q.pop();

		for(int i = 0; i < numGoals; i++) {
			if(goals[i].x == p.x && goals[i].y == p.y) {
				b = true;
				path[p.x][p.y] = previous[p.x][p.y];
				break;
			}
		}
		if(b) break;

		if(!visited[p.x][p.y]) {
			visited[p.x][p.y] = true;
			numExpanded++;
			path[p.x][p.y] = previous[p.x][p.y];

			if(maze[p.x + 1][p.y] != '%') {
				q.push(point{p.x + 1, p.y, 0});
				previous[p.x + 1][p.y] = p;
			}
			if(maze[p.x - 1][p.y] != '%') {
				q.push(point{p.x - 1, p.y, 0});
				previous[p.x - 1][p.y] = p;
			}
			if(maze[p.x][p.y + 1] != '%') {
				q.push(point{p.x, p.y + 1, 0});
				previous[p.x][p.y + 1] = p;
			}
			if(maze[p.x][p.y - 1] != '%') {
				q.push(point{p.x, p.y - 1, 0});
				previous[p.x][p.y - 1] = p;
			}
		}
	}

	pathLength = 0;
	while(p != start) {
		maze[p.x][p.y] = '.';
		p = path[p.x][p.y];
		pathLength++;
	}
}

void Map::A_Star() {
	start.goal = goals[0];
	priority_queue<point, vector<point>, greater<point>> q;
	point p;
	bool** visited = new bool*[width];
	for(int i = 0; i < width; i++) {
		visited[i] = new bool[height];
		for(int j = 0; j < height; j++)
			visited[i][j] = false;
	}

	point** previous = new point*[width];
	for(int i = 0; i < width; i++)
		previous[i] = new point[height];

	point** path = new point*[width];
	for(int i = 0; i < width; i++)
		path[i] = new point[height];

	int** dist = new int*[width];
	for(int i = 0; i < width; i++) {
		dist[i] = new int[height];
		for(int j = 0; j < height; j++)
			dist[i][j] = 99999;
	}

	numExpanded = 0;
	bool b = false;
	q.push(start);
	while(!q.empty()) {
		p = q.top();
		q.pop();

		for(int i = 0; i < numGoals; i++) {
			if(goals[i].x == p.x && goals[i].y == p.y) {
				b = true;
				path[p.x][p.y] = previous[p.x][p.y];
				break;
			}
		}
		if(b) break;

		if(!visited[p.x][p.y]) {
			visited[p.x][p.y] = true;
			numExpanded++;
			path[p.x][p.y] = previous[p.x][p.y];
			//maze[p.x][p.y] = '?';

			if(maze[p.x + 1][p.y] != '%' && dist[p.x + 1][p.y] > p.distance + 1) {
				dist[p.x + 1][p.y] = p.distance + 1;
				q.push(point{p.x + 1, p.y, p.distance + 1});
				previous[p.x + 1][p.y] = p;
			}
			if(maze[p.x - 1][p.y] != '%' && dist[p.x - 1][p.y] > p.distance + 1) {
				dist[p.x - 1][p.y] = p.distance + 1;
				q.push(point{p.x - 1, p.y, p.distance + 1});
				previous[p.x - 1][p.y] = p;
			}
			if(maze[p.x][p.y + 1] != '%' && dist[p.x][p.y + 1] > p.distance + 1) {
				dist[p.x][p.y + 1] = p.distance + 1;
				q.push(point{p.x, p.y + 1, p.distance + 1});
				previous[p.x][p.y + 1] = p;
			}
			if(maze[p.x][p.y - 1] != '%' && dist[p.x][p.y - 1] > p.distance + 1) {
				dist[p.x][p.y - 1] = p.distance + 1;
				q.push(point{p.x, p.y - 1, p.distance + 1});
				previous[p.x][p.y - 1] = p;
			}
		}
	}

	pathLength = 0;
	while(p != start) {
		maze[p.x][p.y] = '.';
		p = path[p.x][p.y];
		pathLength++;
	}
}

void Map::Multiple() {
	vector<vector<int>> distances_all(numGoals + 1);
	for(int i = 0; i < numGoals + 1; i++)
		distances_all[i] = vector<int>(numGoals + 1);
	for(int i = 0; i < numGoals + 1; i++) {
		for(int j = i + 1; j < numGoals + 1; j++) {
			distances_all[i][j] = BFS_Multiple(i, j);
			distances_all[j][i] = BFS_Multiple(i, j);
		}
	}

	for(int i = 0; i < numGoals + 1; i++) {
		for(int j = 0; j < numGoals + 1; j++)
			cout << distances_all[i][j] << ' ';
		cout << '\n';
	}
}

int Map::BFS_Multiple(int start_, int end_) {
	point start_point, end_point;
	if(start_ == numGoals)
		start_point = start;
	else
		start_point = goals[start_];
	if(end_ == numGoals)
		end_point = start;
	else
		end_point = goals[end_];

	queue<point> q;
	point p;
	bool** visited = new bool*[width];
	for(int i = 0; i < width; i++) {
		visited[i] = new bool[height];
		for(int j = 0; j < height; j++)
			visited[i][j] = false;
	}

	point** previous = new point*[width];
	for(int i = 0; i < width; i++)
		previous[i] = new point[height];

	point** path = new point*[width];
	for(int i = 0; i < width; i++)
		path[i] = new point[height];

	numExpanded = 0;
	q.push(start_point);
	while(!q.empty()) {
		p = q.front();
		q.pop();

		if(end_point == p) {
			path[p.x][p.y] = previous[p.x][p.y];
			break;
		}

		if(!visited[p.x][p.y]) {
			visited[p.x][p.y] = true;
			numExpanded++;
			path[p.x][p.y] = previous[p.x][p.y];

			if(maze[p.x][p.y + 1] != '%') {
				q.push(point{p.x, p.y + 1, 0});
				previous[p.x][p.y + 1] = p;
			}
			if(maze[p.x + 1][p.y] != '%') {
				q.push(point{p.x + 1, p.y, 0});
				previous[p.x + 1][p.y] = p;
			}
			if(maze[p.x][p.y - 1] != '%') {
				q.push(point{p.x, p.y - 1, 0});
				previous[p.x][p.y - 1] = p;
			}
			if(maze[p.x - 1][p.y] != '%') {
				q.push(point{p.x - 1, p.y, 0});
				previous[p.x - 1][p.y] = p;
			}
		}
	}

	pathLength = 0;
	while(p != start_point) {
		//maze[p.x][p.y] = '.';
		p = path[p.x][p.y];
		pathLength++;
	}

	for(int i = 0; i < width; i++) {
		delete visited[i];
		delete previous[i];
		delete path[i];
	}
	delete visited;
	delete previous;
	delete path;

	return pathLength;
}
