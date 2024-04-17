#include "graph.h"
#include <iostream>
#include <iomanip>
#include <map>

// Constructor for graph
Graph::Graph() {
  numVertices = 0;
}

// Constructor for vertex
Graph::Vertex::Vertex() {
  url = "";
  degreeIn = 0;
  degreeOut = 0;
  rank = 0;
  sum = 0;
}

// Constructor for vertex
Graph::Vertex::Vertex(string url) {
    this->url = url;
    degreeIn = 0;
    degreeOut = 0;
    rank = 0;
    sum = 0;
}

// Performing PageRank algorithm
// improved version maybe
void Graph::pageRank(double iterations) {
      vector<double> rank(numVertices, 1.0 / numVertices);
      map<string, int> indexMap;
      int idx = 0;

      // Map each vertex to an index
      for (const auto& vertex : adjList) {
          indexMap[vertex.first] = idx++;  
      }

      // Perform power iterations
      while (iterations > 1) {
          vector<double> newRank(numVertices, 0.0);

          // Calculate new rank based on outgoing edges
          for (const auto& vertex : adjList) {
              for (const auto& adjVertex : vertex.second.second) {
                  int j = indexMap[adjVertex.url];

                  newRank[j] += rank[indexMap[vertex.first]] / vertex.second.first.degreeOut;
              }
          }

          rank = newRank;
          iterations--;
      }

      // Sort by conveting to map
      map<string, double> sortedRank;
      for (const auto& vertex : adjList) {
          sortedRank[vertex.first] = rank[indexMap[vertex.first]];
      }

      // Print sorted pageranks
      for (const auto& vertex : sortedRank) {
          cout << vertex.first << " " << fixed << setprecision(2) << vertex.second << endl;
      }
  }

// Inserting edge from src to dest
void Graph::addEdge(const string src, const string dest) {
    // If src not in the graph, add it
    if (adjList.find(src) == adjList.end()) {
        Vertex v(src);
        adjList[src].first = v;
        numVertices++;
    }
    // If dest not in the graph, add it
    if (adjList.find(dest) == adjList.end()) {
        Vertex v(dest);
        adjList[dest].first = v;
        numVertices++;
    }
    // Add edge from src to dest
    adjList[src].second.push_back(adjList[dest].first);
    adjList[dest].first.degreeIn++;
    adjList[src].first.degreeOut++;
}

