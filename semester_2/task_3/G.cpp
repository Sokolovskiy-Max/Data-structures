//#include <iostream>
//#include <map>
//#include <string>
//#include <algorithm>
//#include <vector>
//
//struct WordCount {
//  int count_ = 0;
//  std::string word_ = "";
//  WordCount() = default;
//  WordCount(int count, std::string word) : count_(count), word_(word) {
//  }
//  friend bool operator<(const WordCount&, const WordCount&);
//};
//
//bool operator<(const WordCount& first, const WordCount& second) {
//  if (first.count_ > second.count_) {
//    return true;
//  }
//  if (first.count_ < second.count_) {
//    return false;
//  }
//  return (first.word_ < second.word_);
//}
//
//int main() {
//  std::string word;
//  std::map<std::string, int> read_dict;
//  while (std::cin >> word) {
//    if (read_dict.find(word) != read_dict.end()) {
//      ++read_dict[word];
//    } else {
//      read_dict[word] = 1;
//    }
//  }
//  std::vector<WordCount> output_list;
//  for (auto counter : read_dict) {
//    output_list.push_back(WordCount(counter.second, counter.first));
//  }
//  sort(output_list.begin(), output_list.end());
//  for (auto const& counter : output_list) {
//    std::cout << counter.word_ << '\n';
//  }
//}
//
//
////#include <iostream>
////#include <map>
////#include <string>
////#include <algorithm>
////#include <vector>
////bool Comp(std::pair<int, std::string> a, std::pair<int, std::string> b) {
////  if (a.first > b.first) {
////    return true;
////  }
////  if (a.first < b.first) {
////    return false;
////  }
////  return (a.second < b.second);
////}
////int main() {
////  std::string word;
////  std::map<std::string, int> dict;
////  while (std::cin >> word) {
////    if (dict.find(word) != dict.end()) {
////      ++dict[word];
////    } else {
////      dict[word] = 1;
////    }
////  }
////  std::vector<std::pair<int, std::string>> dict2;
////  for (std::pair<std::string, int> pair : dict) {
////    dict2.emplace_back(std::make_pair(pair.second, pair.first));
////  }
////  sort(dict2.begin(), dict2.end(), Comp);
////  for (auto const& pair : dict2) {
////    std::cout << pair.second << '\n';
////  }
////}