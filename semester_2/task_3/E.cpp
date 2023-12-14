//#include <iostream>
//#include <string>
//#include <unordered_map>
//int main() {
//  std::ios::sync_with_stdio(false);
//  std::cin.tie(0);
//  int n;
//  std::cin >> n;
//  std::string str1, str2;
//  std::unordered_map<std::string, std::string> dict1(n);
//  std::unordered_map<std::string, std::string> dict2(n);
//  for (int i = 0; i < n; ++i) {
//    std::cin >> str1 >> str2;
//    dict1[str1] = str2;
//    dict2[str2] = str1;
//  }
//  int q;
//  std::cin >> q;
//  std::string question;
//  for (int i = 0; i < q; ++i) {
//    std::cin >> question;
//    if (dict1.find(question) != dict1.end()) {
//      std::cout << dict1[question] << "\n";
//    } else {
//      std::cout << dict2[question] << "\n";
//    }
//  }
//}