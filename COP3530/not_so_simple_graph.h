#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

// Graph class represents directed graph with possible self loops and parallel edges
class Graph {
   private:
      // Adjacency list to store the graph
      map<int, vector<pair<int, int>>> adjList;

    public:
      // Inserts new edge with specified weight
      void insertEdge(int from, int to, int weight) {
          adjList[from].push_back({to, weight});
      }

      // Checks if there is at least one edge
      bool isEdge(int from, int to) {
          if (adjList.find(from) != adjList.end()) {
              for (auto &edge : adjList[from]) {
                  if (edge.first == to) {
                      return true;
                  }
              }
          }
          return false;
      }

      // Calculates sum of weights of all edges
      int sumEdge(int from, int to) {
          int sum = 0;
          if (adjList.find(from) != adjList.end()) {
              for (auto &edge : adjList[from]) {
                  if (edge.first == to) {
                      sum += edge.second;
                  }
              }
          }
          return sum;
      }

      // Returns sorted vector of weights of all edges
      vector<int> getWeight(int from, int to) {
          vector<int> weights;
          if (adjList.find(from) != adjList.end()) {
              for (auto &edge : adjList[from]) {
                  if (edge.first == to) {
                      weights.push_back(edge.second);
                  }
              }
          }
          sort(weights.begin(), weights.end());
          return weights;
      }

      // Returns sorted vector of vertices adjacent to vertex
      vector<int> getAdjacent(int vertex) {
          vector<int> adjacent;
          if (adjList.find(vertex) != adjList.end()) {
              for (auto &edge : adjList[vertex]) {
                  adjacent.push_back(edge.first);
              }
          }
          sort(adjacent.begin(), adjacent.end());
          return adjacent;
      }
};