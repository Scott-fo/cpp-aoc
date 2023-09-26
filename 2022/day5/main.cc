#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

struct Instruction {
  uint quantity;
  uint origin;
  uint destination;

  void execute_instruction(std::vector<std::vector<char>> &stacks) const {
    for (uint ui = 0; ui < quantity; ++ui) {
      char c = stacks[origin - 1].back();
      stacks[origin - 1].pop_back();
      stacks[destination - 1].push_back(c);
    }
  }

  void execute_multi_crate_instruction(std::vector<std::vector<char>> &stacks) {
    std::vector<char> crates_in_motion;
    for (uint ui = 0; ui < quantity; ++ui) {
      char c = stacks[origin - 1].back();
      stacks[origin - 1].pop_back();

      crates_in_motion.push_back(c);
    }

    while (!crates_in_motion.empty()) {
      stacks[destination - 1].push_back(crates_in_motion.back());
      crates_in_motion.pop_back();
    }
  }
};

struct Crane {
  std::vector<std::vector<char>> stacks;

  void execute_instructions(const std::vector<Instruction> &instructions) {
    for (auto instruction : instructions) {
      instruction.execute_instruction(stacks);
    }
  }

  void execute_multi_crate_instructions(
      const std::vector<Instruction> &instructions) {
    for (auto instruction : instructions) {
      instruction.execute_multi_crate_instruction(stacks);
    }
  }

  void print_stacks() const {
    for (const auto &ss : stacks) {
      for (const auto &s : ss) {
        std::cout << s;
      }

      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  void print_tops() const {
    for (const auto &s : stacks) {
      std::cout << s.back();
    }

    std::cout << std::endl << std::endl;
  }
};

std::pair<std::string, std::string> parse_input() {
  std::ifstream fin("input.txt");
  if (!fin.is_open()) {
    throw std::runtime_error("Failed to open input file");
  }

  std::stringstream buffer;
  std::string line;

  while (std::getline(fin, line)) {
    if (line.empty()) {
      break;
    }

    buffer << line << '\n';
  }

  std::string crates = buffer.str();

  buffer.str("");
  while (std::getline(fin, line)) {
    buffer << line << '\n';
  }

  std::string instructions = buffer.str();
  return {crates, instructions};
}

int count_stacks(const std::string s) {
  return std::count_if(s.begin(), s.end(),
                       [](unsigned char c) { return !std::isspace(c); });
}

Crane new_crane(const std::string &crates) {
  std::vector<std::string> crates_vector;
  std::istringstream iss{crates};
  std::string line;

  while (std::getline(iss, line)) {
    crates_vector.push_back(line);
  }

  int num_stacks = count_stacks(crates_vector[crates_vector.size() - 1]);
  std::vector<std::vector<char>> stacks(num_stacks);

  for (size_t i = crates_vector.size() - 1; i-- > 0;) {
    std::string s = crates_vector[i];
    for (uint k = 1; k <= s.size(); k += 4) {
      if (s[k] != ' ') {
        int stack_idx = (k - 1) / 4;
        char c = s[k];
        stacks[stack_idx].push_back(c);
      }
    }
  }

  Crane c;
  c.stacks = std::move(stacks);

  return c;
}

std::vector<Instruction> parse_instructions(const std::string &instructions) {
  size_t num_instructions =
      std::count(instructions.begin(), instructions.end(), '\n');
  std::vector<Instruction> parsed_instructions;
  parsed_instructions.reserve(num_instructions);

  std::istringstream iss{instructions};
  std::string line;

  while (std::getline(iss, line)) {
    std::istringstream ss(line);
    Instruction i;
    std::string t;

    ss >> t >> i.quantity >> t >> i.origin >> t >> i.destination;
    parsed_instructions.emplace_back(i);
  }

  return parsed_instructions;
}

int main() {
  auto [crates, instructions] = parse_input();

  auto crane = new_crane(crates);
  auto crate_mover_9001 = new_crane(crates);

  auto parsed_instructions = parse_instructions(instructions);

  crane.execute_instructions(parsed_instructions);
  // crane.print_stacks();
  crane.print_tops();

  crate_mover_9001.execute_multi_crate_instructions(parsed_instructions);
  // crate_mover_9001.print_stacks();
  crate_mover_9001.print_tops();

  return 0;
}
