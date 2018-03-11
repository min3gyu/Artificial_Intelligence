#include "map.hpp"

int main() {
  //Map map1 ("medium.txt", "output/astar_medium.txt");
  //Map map2 ("big.txt", "output/astar_big.txt");
  //Map map3 ("open.txt", "output/astar_open.txt");
  Map map1 ("multiple_tiny.txt", "output/multiple_tiny.txt");
  Map map2 ("multiple_small.txt", "output/multiple_small.txt");
  Map map3 ("multiple_medium.txt", "output/multiple_medium.txt");
  map1.Multiple();
  map1.printMaze();

  map2.Multiple();
  map2.printMaze();

  map3.Multiple();
  map3.printMaze();
  //map.DFS();
  //map.BFS();
  //map.Greedy_BFS();
  //map.A_Star();
  //map.Multiple();

  //map1.printMaze();
  //map2.printMaze();
  //map3.printMaze();
  return 0;
}
