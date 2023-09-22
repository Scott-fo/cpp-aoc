#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

enum class moves_t { rock, paper, scissors };
enum class outcomes_t { win, lose, draw };

moves_t get_move(char c) {
  static const std::unordered_map<char, moves_t> char_to_move = {
      {'A', moves_t::rock},  {'X', moves_t::rock},     {'B', moves_t::paper},
      {'Y', moves_t::paper}, {'C', moves_t::scissors}, {'Z', moves_t::scissors},
  };

  auto move = char_to_move.find(c);
  if (move == char_to_move.end()) {
    throw std::runtime_error("Unexepected character: " + std::string(1, c));
  }

  return move->second;
}

int get_move_score(moves_t m) {
  static const std::unordered_map<moves_t, int> move_to_score = {
      {moves_t::rock, 1},
      {moves_t::paper, 2},
      {moves_t::scissors, 3},
  };

  return move_to_score.at(m);
}

int get_outcome_score(outcomes_t o) {
  static const std::unordered_map<outcomes_t, int> outcome_to_score = {
      {outcomes_t::win, 6},
      {outcomes_t::draw, 3},
      {outcomes_t::lose, 0},
  };

  return outcome_to_score.at(o);
}

outcomes_t get_outcome(moves_t mx, moves_t my) {
  if (mx == my) {
    return outcomes_t::draw;
  }

  if ((mx == moves_t::rock && my == moves_t::scissors) ||
      (mx == moves_t::paper && my == moves_t::rock) ||
      (mx == moves_t::scissors && my == moves_t::paper)) {
    return outcomes_t::win;
  }

  return outcomes_t::lose;
}

int main() {
  std::ifstream fin("input.txt");
  if (!fin.is_open()) {
    std::cerr << "Failed to open input.txt" << std::endl;
    return 1;
  }

  int total_score = 0;

  for (std::string line; std::getline(fin, line);) {
    moves_t opp_move = get_move(line[0]);
    moves_t your_move = get_move(line[2]);

    total_score += get_move_score(your_move);
    total_score += get_outcome_score(get_outcome(your_move, opp_move));
  }

  std::cout << "Total Score: " << total_score << std::endl;

  return 0;
}
