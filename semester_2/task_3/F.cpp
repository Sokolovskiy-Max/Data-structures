//#include <iostream>
//#include <unordered_map>
//#include <string>
//int main() {
//  int n, pay;
//  std::cin >> n;
//  std::unordered_map<std::string, int> dict;
//  std::string name;
//  for (int i = 0; i < n; ++i) {
//    int command;
//    std::cin >> command;
//    if (command == 1) {
//      std::cin >> name >> pay;
//      if (dict.find(name) == dict.end()) {
//        dict[name] = pay;
//      } else {
//        dict[name] += pay;
//      }
//    } else {
//      std::cin >> name;
//      if (dict.find(name) == dict.end()) {
//        std::cout << "ERROR" << "\n";
//      } else {
//        std::cout << dict[name] << "\n";
//      }
//    }
//   }
//}