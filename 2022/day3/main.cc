#include <cstddef>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

int char_to_number(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a' + 1;
  }

  if (c >= 'A' && c <= 'Z') {
    return c - 'A' + 27;
  }

  throw std::runtime_error("Unexpected character: " + std::string(1, c));
}

std::vector<std::string> read_file(const std::string &filename) {
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cerr << "Failed to open: " << filename << std::endl;
    exit(1);
  }

  std::vector<std::string> lines;
  for (std::string line; std::getline(fin, line);) {
    lines.push_back(line);
  }

  return lines;
}

int part_one(const std::vector<std::string> &lines) {
  int total_priority = 0;

  for (auto backpack : lines) {
    const auto length = backpack.length();
    const auto midpoint = length / 2;

    std::unordered_set<char> item_set{backpack.begin(),
                                      backpack.begin() + midpoint};

    for (auto i = midpoint; i < length; ++i) {
      if (item_set.count(backpack[i])) {
        total_priority += char_to_number(backpack[i]);
        break;
      }
    }
  }

  return total_priority;
}

int part_two(const std::vector<std::string> &lines) {
  int total_priority = 0;

  for (auto it = lines.begin(); it != lines.end(); it += 3) {
    const auto &elf_one = *it;
    const auto &elf_two = *(it + 1);
    const auto &elf_three = *(it + 2);

    std::unordered_set<char> elf_one_set{elf_one.begin(), elf_one.end()};
    std::unordered_set<char> elf_two_set{elf_two.begin(), elf_two.end()};

    for (char c : elf_three) {
      if (elf_one_set.count(c) && elf_two_set.count(c)) {
        total_priority += char_to_number(c);
        break;
      }
    }
  }

  return total_priority;
}

int main() {
  auto lines = read_file("input.txt");

  std::cout << "Part One Priority: " << part_one(lines) << std::endl;
  std::cout << "Part Two Priority: " << part_two(lines) << std::endl;

  return 0;
}
