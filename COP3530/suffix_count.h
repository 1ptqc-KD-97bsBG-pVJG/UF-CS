#include <iostream>
#include <string>

int suffixCount(std::string S, int L) {
  int total = 0;
  std::string suffix = S.substr(S.length() - L);

  for (int i = 0; i <= S.length() - L; i++) {
    if (S.substr(i, L) == suffix) {
        total++;
    }
  }
  return total;
}