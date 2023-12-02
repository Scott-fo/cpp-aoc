#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct Bag {
  int red;
  int green;
  int blue;
};

struct ValidCounts {
  bool red;
  bool green;
  bool blue;
};

int main() {
  std::ifstream fin("data/day2.txt");

  Bag bag;
  bag.red = 12;
  bag.green = 13;
  bag.blue = 14;

  int sum = 0;
  int idx = 0;

  int power_sum = 0;

  for (std::string g; std::getline(fin, g);) {
    ++idx;
    std::string::size_type colon_pos = g.find(':');
    std::string segments =
        (colon_pos != std::string::npos) ? g.substr(colon_pos + 1) : g;

    std::stringstream ss(segments);
    std::string item;

    ValidCounts valid;
    valid.red = true;
    valid.green = true;
    valid.blue = true;

    Bag min_counts;
    min_counts.red = 0;
    min_counts.green = 0;
    min_counts.blue = 0;

    while (std::getline(ss, item, ';')) {
      std::stringstream item_stream(item);
      std::string colour;
      int number;

      while (item_stream >> number >> colour) {
        colour.erase(std::remove(colour.begin(), colour.end(), ','),
                     colour.end());

        if (colour == "red") {
          if (number > min_counts.red) {
            min_counts.red = number;
          }
          if (number > bag.red) {
            valid.red = false;
          }
        }
        if (colour == "green") {
          if (number > min_counts.green) {
            min_counts.green = number;
          }
          if (number > bag.green) {
            valid.green = false;
          }
        }
        if (colour == "blue") {
          if (number > min_counts.blue) {
            min_counts.blue = number;
          }
          if (number > bag.blue) {
            valid.blue = false;
          }
        }
      }
    }

    power_sum += min_counts.blue * min_counts.red * min_counts.green;

    if (valid.red && valid.green && valid.blue) {
      sum += idx;
    }
  }

  std::cout << "Sum: " << sum << std::endl;
  std::cout << "Power Sum: " << power_sum << std::endl;

  return 0;
}
