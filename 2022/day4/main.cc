#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Pair {
  int lb;
  int ub;

  bool fully_contains(const Pair &other) const {
    return lb <= other.lb && ub >= other.ub;
  }

  bool overlaps(const Pair &other) const {
    return lb <= other.lb && ub >= other.lb;
  }
};

std::vector<Pair> parse_pair(const std::string &str) {
  std::vector<Pair> pairs;
  std::stringstream ss{str};
  std::string num;
  Pair p1, p2;

  std::getline(ss, num, '-');
  p1.lb = std::stoi(num);

  std::getline(ss, num, ',');
  p1.ub = std::stoi(num);

  std::getline(ss, num, '-');
  p2.lb = std::stoi(num);

  std::getline(ss, num);
  p2.ub = std::stoi(num);

  pairs.push_back(p1);
  pairs.push_back(p2);

  return pairs;
}

int main() {
  std::ifstream fin("input.txt");

  uint overlaps = 0;
  uint contains = 0;

  for (std::string pair; std::getline(fin, pair);) {
    auto ps = parse_pair(pair);

    if (ps[0].overlaps(ps[1]) || ps[1].overlaps(ps[0])) {
      overlaps++;
      if (ps[0].fully_contains(ps[1]) || ps[1].fully_contains(ps[0])) {
        contains++;
      }
    }
  }

  std::cout << "Contains Count: " << contains << std::endl;
  std::cout << "Overlaps Count: " << overlaps << std::endl;

  return 0;
}
