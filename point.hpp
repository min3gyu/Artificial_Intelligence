#ifndef __POINT_H__
#define __POINT_H__

#include <vector>

using namespace std;

/* point class
 * used in part 1:
 * each grid on the maze is a point
 * operators overloaded for priority_queue compare and easy assignments
 */
class point{
	public:
    static point goal;
    int x;
    int y;
    int distance;
    bool operator==(const point& rhs) const;
    bool operator!=(const point& rhs) const;
    bool operator<(const point& rhs) const;
    bool operator<=(const point& rhs) const;
    bool operator>(const point& rhs) const;
    bool operator>=(const point& rhs) const;
    point& operator=(const point& other);
};

/* node class
 * used in part 2:
 * each goal is a node
 * operators overloaded for priority_queue compare and easy assignments
 */
class node{
	public:
		static vector<int> mins;
		node();
		node(int id_, int distance_, vector<int> adj_, vector<bool> vis_);
		int id;
		int distance;
    vector<int> adjacent;
		vector<bool> visited;
		vector<int> order;
    bool operator<(const node& rhs) const;
    bool operator<=(const node& rhs) const;
    bool operator>(const node& rhs) const;
    bool operator>=(const node& rhs) const;
		node& operator=(const node& other);
};

#endif
