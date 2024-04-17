#include <string>
#include <map>
#include <vector>
using namespace std;


// adjacency list representation of a graph called Graph
class Graph {
    private:
        struct Vertex {
            string url;
            double degreeIn;
            double degreeOut;
            double rank;
            double sum;
            Vertex();
            Vertex(string url);
        };

        double numVertices;
        map<string, pair<Vertex, vector<Vertex>>> adjList;

    public:
        // Constructor
        Graph();

        // Add an edge from src to dest
        void addEdge(const string src, const string dest); 

        // Perform PageRank algorithm, return results as string
        void pageRank(double iterations); 
        
        
        // Print adjacency list
        // void printGraph(const unordered_map<string, double>& ranks);
        void printGraph();
};

