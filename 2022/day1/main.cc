#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

int main() {
  std::ifstream fin("input.txt");
  std::vector<int> sums{};

  int sum = 0;

  for (std::string line; std::getline(fin, line);) {
    if (line.empty()) {
      sums.push_back(sum);
      sum = 0;
    } else {
      sum += std::stoi(line);
    }
  }

  sums.push_back(sum);

  const auto max = *std::max_element(sums.begin(), sums.end());
  std::cout << "Max Element: " << max << std::endl;

  std::sort(sums.begin(), sums.end(), std::greater<int>());
  const auto top3 = std::accumulate(sums.begin(), sums.begin() + 3, 0);

  std::cout << "Sum of Top 3: " << top3 << std::endl;

  return 0;
}
