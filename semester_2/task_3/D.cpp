//#include <vector>
//#include <iostream>
//class Graph {
//  std::vector<std::vector<int>> adj_list_;
//
// public:
//  explicit Graph(int n) {
//    adj_list_.resize(n + 1);
//  }
//  void AddEdge(int u, int v) {
//    adj_list_[u].push_back(v);
//    adj_list_[v].push_back(u);
//  }
//  void Vertex(int u) {
//    for (int v : adj_list_[u]) {
//      std::cout << v << ' ';
//    }
//    std::cout << std::endl;
//  }
//};
//int main() {
//  int n, k;
//  std::cin >> n >> k;
//  Graph graph = Graph(n);
//  int comand, u, v, vertex;
//  for (int i = 0; i < k; ++i) {
//    std::cin >> comand;
//    if (comand == 1) {
//      std::cin >> u >> v;
//      graph.AddEdge(u, v);
//    } else {
//      std::cin >> vertex;
//      graph.Vertex(vertex);
//    }
//  }
//}