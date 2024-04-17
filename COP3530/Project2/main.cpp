#include <iostream>
#include "graph.h"

int main() {

  int numLines;
  double iterations;
  string src, dest;
  Graph graph;

  cin >> numLines;
  cin >> iterations;

  for (int i = 0; i < numLines; i++) {
    cin >> src >> dest;
    graph.addEdge(src, dest);
  }

  graph.pageRank(iterations);

}