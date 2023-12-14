//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//struct Command {
//  int number_ = 0;
//  int score_ = 0;
//  int fine_ = 0;
//  Command() = default;
//  Command(int number, int score, int fine) : number_(number), score_(score), fine_(fine) {
//  }
//  friend bool operator<(const Command&, const Command&);
//};
//bool operator<(const Command& command1, const Command& command2) {
//  if (command1.score_ > command2.score_) {
//    return true;
//  }
//  if (command1.score_ < command2.score_) {
//    return false;
//  }
//  if (command1.fine_ < command2.fine_) {
//    return true;
//  }
//  if (command1.fine_ > command2.fine_) {
//    return false;
//  }
//  return (command1.number_ < command2.number_);
//}
//
//bool Comp(const Command& command1, const Command& command2) {
//  return command1 < command2;
//}
//
//int main() {
//  int n, score, fine;
//  std::cin >> n;
//  std::vector<Command> commands(n);
//  for (int i = 0; i < n; ++i) {
//    std::cin >> score >> fine;
//    commands[i] = Command(i + 1, score, fine);
//  }
//  sort(commands.begin(), commands.end());
//  for (Command command: commands) {
//    std::cout << command.number_ << std::endl;
//  }
//}