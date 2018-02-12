#include "point.hpp"

point point::goal;

bool point::operator==(const point& rhs) const {
  return this->x == rhs.x && this->y == rhs.y;
}

bool point::operator!=(const point& rhs) const {
  return !(*this == rhs);
}

bool point::operator<(const point& rhs) const {
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

bool point::operator<=(const point& rhs) const {
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

bool point::operator>(const point& rhs) const {
  return !(*this <= rhs);
}

bool point::operator>=(const point& rhs) const {
  return !(*this < rhs);
}

point& point::operator=(const point& other) {
  if(this != &other) {
    this->x = other.x;
    this->y = other.y;
    this->distance = other.distance;
  }
  return *this;
}
