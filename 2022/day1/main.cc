#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int main() {
  std::ifstream fin("input.txt");

  std::vector<int> sums = {};
  int sum = 0;

  while (fin) {
    std::string calorie;
    getline(fin, calorie);

    if (calorie.empty()) {
      sums.push_back(sum);
      sum = 0;

      continue;
    }

    sum += std::stoi(calorie);
  }

  sums.push_back(sum);

  double max = *std::max_element(sums.begin(), sums.end());
  std::cout << "Max Element: " << max << std::endl;

  std::sort(sums.begin(), sums.end(), std::greater<int>());

  int top3 = 0;
  for (int i = 0; i < 3; ++i) {
    top3 += sums[i];
  }

  std::cout << "Sum of Top 3: " << top3 << std::endl;

  return 0;
}
