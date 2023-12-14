//#include <iostream>
//#include <vector>
//#include <algorithm>
//
//int main() {
//  int animals, questions;
//  std::cin >> animals;
//  std::vector<int> animal_colors(animals);
//  for (int i = 0; i < animals; ++i) {
//    std::cin >> animal_colors[i];
//  }
//  std::cin >> questions;
//  for (int i = 0; i < questions; ++i) {
//    int color;
//    std::cin >> color;
//    auto up = std::upper_bound(animal_colors.begin(), animal_colors.end(), color);
//    auto down = std::lower_bound(animal_colors.begin(), up, color);
//    std::cout << up - down << std::endl;
//  }
//}