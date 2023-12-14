//#include <iostream>
//#include <map>
//#include <string>
//#include <algorithm>
//#include <vector>
//int main() {
//  std::string name, product;
//  int64_t count;
//  std::map<std::string, std::map<std::string, int64_t>> bd;
//  while (std::cin >> name) {
//    std::cin >> product >> count;
//    if (bd.find(name) != bd.end()) {
//      if (bd[name].find(product) != bd[name].end()) {
//        bd[name][product] += count;
//      } else {
//        bd[name][product] = count;
//      }
//    } else {
//      bd[name][product] = count;
//    }
//  }
//  for (auto man : bd) {
//    std::cout << man.first << '\n';
//    for (auto buy : bd[man.first]) {
//      std::cout << buy.first << ' ' << buy.second << '\n';
//    }
//  }
//}