#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int traverse(vector<string> &graph) {
    int rows = graph.size();
    int cols = graph[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    queue<pair<int, int>> q;
    // All possible moves
    vector<pair<int, int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    // Starting point is always (0, 0) given s is at graph[0][0]
    q.push({0, 0});
    visited[0][0] = true;
    int pathLength = 0;

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; ++i) {
            pair<int, int> front = q.front();
            int r = front.first;
            int c = front.second;
            q.pop();

            // If reached target return path length
            if (graph[r][c] == 't') return pathLength;

            // Explore all possible moves from current position
            for (const pair<int, int>& dir : directions) {
                int newR = r + dir.first;
                int newC = c + dir.second;

                // Check if new position within bounds and not visited
                if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && 
                    !visited[newR][newC] && graph[newR][newC] != '#') {
                    q.push({newR, newC});
                    visited[newR][newC] = true;
                }
            }
        }
        pathLength++;
    }

    // No path found
    return -1;
}