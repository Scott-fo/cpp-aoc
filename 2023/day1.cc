#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> string_to_digit_map{
    {"one", "1"}, {"two", "2"},   {"three", "3"}, {"four", "4"}, {"five", "5"},
    {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"},
};

int get_first_int(std::string s) {
  std::string temp = "";

  for (auto c : s) {
    if (isdigit(c)) {
      return c - '0';
    }
  }

  return 0;
}

std::string replace_last_occurence(std::string s) {
  bool replaced;
  do {
    replaced = false;
    std::string::size_type last_pos = std::string::npos;
    std::string key_to_replace;

    for (const auto &pair : string_to_digit_map) {
      std::string::size_type pos = s.rfind(pair.first);
      if (pos != std::string::npos &&
          (last_pos == std::string::npos || pos > last_pos)) {
        last_pos = pos;
        key_to_replace = pair.first;
      }
    }

    if (last_pos != std::string::npos) {
      s.replace(last_pos, key_to_replace.length(),
                string_to_digit_map.at(key_to_replace));
      replaced = true;
    }
  } while (replaced);

  return s;
}

std::string replace_first_occurence(std::string s) {
  bool replaced;
  do {
    replaced = false;
    std::string::size_type earliest_pos = std::string::npos;
    std::string key_to_replace;

    for (const auto &pair : string_to_digit_map) {
      std::string::size_type pos = s.find(pair.first);
      if (pos != std::string::npos &&
          (earliest_pos == std::string::npos || pos < earliest_pos)) {
        earliest_pos = pos;
        key_to_replace = pair.first;
      }
    }

    if (earliest_pos != std::string::npos) {
      s.replace(earliest_pos, key_to_replace.length(),
                string_to_digit_map.at(key_to_replace));
      replaced = true;
    }
  } while (replaced);

  return s;
}

void p1() {
  std::ifstream fin("data/day1.txt");
  int sum = 0;

  for (std::string l; std::getline(fin, l);) {
    auto first = get_first_int(l);
    std::reverse(l.begin(), l.end());
    auto second = get_first_int(l);

    sum += (first * 10) + second;
  }

  std::cout << "Sum: " << sum << std::endl;
}

int main() {
  std::ifstream fin("data/day1.txt");
  int sum = 0;

  for (std::string l; std::getline(fin, l);) {
    auto first = get_first_int(replace_first_occurence(l));

    auto last_occurence_l = replace_last_occurence(l);
    std::reverse(last_occurence_l.begin(), last_occurence_l.end());
    auto second = get_first_int(last_occurence_l);

    sum += (first * 10) + second;
  }

  std::cout << "Sum: " << sum << std::endl;

  return 0;
}
