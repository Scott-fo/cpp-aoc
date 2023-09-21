#include <cassert>
#include <iostream>

enum moves_t { rock, paper, scissors };
enum outcomes_t { win, lose, draw };

moves_t get_move(char c) {
  switch (c) {
  case 'A':
    return rock;
  case 'X':
    return rock;
  case 'B':
    return paper;
  case 'Y':
    return paper;
  case 'C':
    return scissors;
  case 'Z':
    return scissors;
  default:
    assert("Unreachable");
    return rock;
  }
}

int get_move_score(moves_t m) {
  if (m == rock) {
    return 1;
  }

  if (m == paper) {
    return 2;
  }

  if (m == scissors) {
    return 3;
  }

  assert("Unreachable");
  return 0;
}

outcomes_t get_outcome(moves_t mx, moves_t my) {
  if (mx == my) {
    return draw;
  }

  if ((mx == rock && my == scissors) || (mx == paper && my == rock) ||
      (mx == scissors && my == paper)) {
    return win;
  }

  return lose;
}

int get_outcome_score(outcomes_t o) {
  if (o == win) {
    return 6;
  }

  if (o == lose) {
    return 0;
  }

  return 3;
}

int main() {
  std::string moves[] = {
      "A Y",
      "B X",
      "C Z",
  };

  int total_score = 0;
  for (auto move : moves) {
    moves_t opp_move = get_move(move[0]);
    moves_t your_move = get_move(move[2]);

    total_score += get_move_score(your_move);
    total_score += get_outcome_score(get_outcome(your_move, opp_move));
  }

  std::cout << "Total Score: " << total_score << std::endl;

  return 0;
}
