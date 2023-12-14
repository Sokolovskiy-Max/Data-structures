//#include <iostream>
//#include <vector>
//#include <queue>
//int main() {
//  std::priority_queue<int, std::vector <int>, std::greater<int>> queue;
//  int n;
//  double pay = 0;
//  std::cin >> n;
//  int a, first_min, second_min;
//  for (int i = 0; i < n; ++i) {
//    std::cin >> a;
//    queue.push(a);
//  }
//  while (queue.size() != 1) {
//    first_min = queue.top();
//    queue.pop();
//    second_min = queue.top();
//    queue.pop();
//    pay += 0.05 * (first_min + second_min);
//    queue.push(first_min + second_min);
//  }
//  std::cout << pay;
//}
