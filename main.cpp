#include "map.hpp"

int main() {
  Map map ("tiny.txt");
  //map.BFS();
  //map.Greedy_BFS();
  //map.A_Star();
  map.Multiple();
  map.printMaze();
  return 0;
}
