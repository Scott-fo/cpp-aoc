#include <fstream>
#include <future>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

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

outcomes_t get_outcome_from_char(char c) {
  static const std::unordered_map<char, outcomes_t> char_to_outcome = {
      {'X', outcomes_t::lose},
      {'Y', outcomes_t::draw},
      {'Z', outcomes_t::win},
  };

  auto outcome = char_to_outcome.find(c);
  if (outcome == char_to_outcome.end()) {
    throw std::runtime_error("Unexpected character: " + std::string(1, c));
  }

  return outcome->second;
}

moves_t get_win(moves_t m) {
  static const std::unordered_map<moves_t, moves_t> winning_move = {
      {moves_t::rock, moves_t::paper},
      {moves_t::paper, moves_t::scissors},
      {moves_t::scissors, moves_t::rock},
  };

  return winning_move.at(m);
}

moves_t get_lose(moves_t m) {
  static const std::unordered_map<moves_t, moves_t> losing_move = {
      {moves_t::rock, moves_t::scissors},
      {moves_t::paper, moves_t::rock},
      {moves_t::scissors, moves_t::paper},
  };

  return losing_move.at(m);
}

moves_t fix_outcome(moves_t opp_move, outcomes_t target) {
  if (target == outcomes_t::draw) {
    return opp_move;
  }

  if (target == outcomes_t::win) {
    return get_win(opp_move);
  }

  return get_lose(opp_move);
}

int part_one(const std::vector<std::string> &lines) {
  int total_score = 0;

  for (const auto &line : lines) {
    moves_t opp_move = get_move(line[0]);
    moves_t your_move = get_move(line[2]);

    total_score += get_move_score(your_move);
    total_score += get_outcome_score(get_outcome(your_move, opp_move));
  }

  return total_score;
}

int part_two(const std::vector<std::string> &lines) {
  int total_score = 0;

  for (const auto &line : lines) {
    moves_t opp_move = get_move(line[0]);
    outcomes_t desired_outcome = get_outcome_from_char(line[2]);
    moves_t your_move = fix_outcome(opp_move, desired_outcome);

    total_score +=
        get_move_score(your_move) + get_outcome_score(desired_outcome);
  }

  return total_score;
}

std::vector<std::string> read_file(const std::string &filename) {
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cerr << "Failed to open " << filename << std::endl;
    exit(1);
  }

  std::vector<std::string> lines;
  for (std::string line; std::getline(fin, line);) {
    lines.push_back(line);
  }

  return lines;
}

int main() {
  auto lines = read_file("input.txt");

  // Trying out concurrency
  std::future<int> future_one =
      std::async(std::launch::async, part_one, std::ref(lines));
  std::future<int> future_two =
      std::async(std::launch::async, part_two, std::ref(lines));

  auto part_one_score = future_one.get();
  std::cout << "Part One Score: " << part_one_score << std::endl;

  auto part_two_score = future_two.get();
  std::cout << "Part Two Score: " << part_two_score << std::endl;

  return 0;
}
