#include "point.hpp"

// static variables used for calculating heuristics
point point::goal;
vector<int> node::mins;

/* operator==
 * overloaded in order to compare two points
 */
bool point::operator==(const point& rhs) const {
  return this->x == rhs.x && this->y == rhs.y;
}

/* operator!=
 * overloaded in order to compare two points
 */
bool point::operator!=(const point& rhs) const {
  return !(*this == rhs);
}

/* operator<
 * overloaded in order to compare the heuristics between two points
 */
bool point::operator<(const point& rhs) const {
  // finds f = g + h for each one of them
  // g = distance travelled
  // h = manhattan distance to goal
  int distx, disty, dist1, dist2;
  distx = goal.x - this->x;
  disty = goal.y - this->y;
  if(distx < 0) distx = 0 - distx;
  if(disty < 0) disty = 0 - disty;
  dist1 = distx + disty + this->distance;

  distx = goal.x - rhs.x;
  disty = goal.y - rhs.y;
  if(distx < 0) distx = 0 - distx;
  if(disty < 0) disty = 0 - disty;
  dist2 = distx + disty + rhs.distance;

  return dist1 < dist2;
}

/* operator<=
 * overloaded in order to compare the heuristics between two points
 */
bool point::operator<=(const point& rhs) const {
  // finds f = g + h for each one of them
  // g = distance travelled
  // h = manhattan distance to goal
  int distx, disty, dist1, dist2;
  distx = goal.x - this->x;
  disty = goal.y - this->y;
  if(distx < 0) distx = 0 - distx;
  if(disty < 0) disty = 0 - disty;
  dist1 = distx + disty + this->distance;

  distx = goal.x - rhs.x;
  disty = goal.y - rhs.y;
  if(distx < 0) distx = 0 - distx;
  if(disty < 0) disty = 0 - disty;
  dist2 = distx + disty + rhs.distance;

  return dist1 <= dist2;
}

/* operator>
 * overloaded in order to compare the heuristics between two points
 */
bool point::operator>(const point& rhs) const {
  return !(*this <= rhs);
}

/* operator<=
 * overloaded in order to compare the heuristics between two points
 */
bool point::operator>=(const point& rhs) const {
  return !(*this < rhs);
}

/* operator=
 * overloaded in order to assign point values easily
 */
point& point::operator=(const point& other) {
  // copies all the member variables if referring to different objects
  if(this != &other) {
    this->x = other.x;
    this->y = other.y;
    this->distance = other.distance;
  }
  return *this;
}

/* node constructor without parameters
 * creates an empty node
 */
node::node() {}

/* node constructor with parameters
 * creates a node with all parameters
 */
node::node(int id_, int distance_, vector<int> adj_, vector<bool> vis_) {
  id = id_;
  distance = distance_;
  adjacent = adj_;
  visited = vis_;
}

/* operator<
 * overloaded in order to compare the heuristics between two nodes
 */
bool node::operator<(const node& rhs) const {
  // finds f = g + h for each one of them
  // g = distance travelled
  // h = sum of minimum adjacent distances of unvisited nodes
  int dist1 = this->distance;
  for(int i = 0; i < (int) this->adjacent.size() - 1; i++) {
    if(!this->visited[i] && i != this->id)
      dist1 += mins[i];
  }

  int dist2 = rhs.distance;
  for(int i = 0; i < (int) rhs.adjacent.size() - 1; i++) {
    if(!rhs.visited[i] && i != rhs.id)
      dist2 += mins[i];
  }

  return dist1 < dist2;
}

/* operator<=
 * overloaded in order to compare the heuristics between two nodes
 */
bool node::operator<=(const node& rhs) const {
  // finds f = g + h for each one of them
  // g = distance travelled
  // h = sum of minimum adjacent distances of unvisited nodes
  int dist1 = this->distance;
  for(int i = 0; i < (int) this->adjacent.size() - 1; i++) {
    if(!this->visited[i] && i != this->id)
      dist1 += mins[i];
  }

  int dist2 = rhs.distance;
  for(int i = 0; i < (int) rhs.adjacent.size() - 1; i++) {
    if(!rhs.visited[i] && i != rhs.id)
      dist2 += mins[i];
  }

  return dist1 <= dist2;
}

/* operator>
 * overloaded in order to compare the heuristics between two nodes
 */
bool node::operator>(const node& rhs) const {
  return !(*this <= rhs);
}

/* operator>=
 * overloaded in order to compare the heuristics between two nodes
 */
bool node::operator>=(const node& rhs) const {
  return !(*this < rhs);
}

/* operator=
 * overloaded in order to assign a node to another
 */
node& node::operator=(const node& other) {
  // copies all the member variables if referring to different objects
  if(this != &other) {
    this->id = other.id;
    this->distance = other.distance;
    this->adjacent = other.adjacent;
    this->visited = other.visited;
    this->order = other.order;
  }
  return *this;
}
