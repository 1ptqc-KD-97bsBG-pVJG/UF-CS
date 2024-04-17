#include <vector>
#include <string>
#include <unordered_set>

std::vector<std::string> getUniqueBookTitles(const std::string A[n][m]) {
    std::unordered_set<std::string> titleSet;
    std::vector<std::string> uniqueTitles;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (titleSet.find(A[i][j]) == titleSet.end()) {
                uniqueTitles.push_back(A[i][j]);
                titleSet.insert(A[i][j]);
            }
        }
    }
    return uniqueTitles;
}