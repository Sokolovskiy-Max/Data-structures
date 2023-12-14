//#include <iostream>
//#include <vector>
//
//class Kosaraju {
//public:
//  int n_;
//  std::vector<std::vector<int>> graph_;
//  std::vector<std::vector<int>> tr_graph_;
//
//private:
//  int count_;
//  std::vector<int> used_;
//  std::vector<int> component_;
//  std::vector<int> order_;
//  std::vector<std::vector<int>> all_components_;
//
//public:
//  Kosaraju(int n, std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& tr_graph)
//    : n_(n), graph_(graph), tr_graph_(tr_graph), count_(0) {
//  }
//  void FindGroups() {
//    used_.assign(n_, false);
//    for (int i = 0; i < n_; ++i) {
//      if (!used_[i]) {
//        Dfs1(i);
//      }
//    }
//    used_.assign(n_, false);
//    for (int i = 0; i < n_; ++i) {
//      int v = order_[n_ - 1 - i];
//      if (!used_[v]) {
//        Dfs2(v);
//        all_components_.emplace_back(component_);
//        ++count_;
//        component_.clear();
//      }
//    }
//  }
//  void ToString() {
//    std::cout << count_ << std::endl;
//    std::vector<int> top_cond(n_);
//
//    for (int i = 0; i < count_; ++i) {
//      for (int j : all_components_[i]) {
//        top_cond[j] = i;
//      }
//    }
//    for (int i = 0; i < n_; ++i) {
//      std::cout << top_cond[i] + 1 << ' ';
//    }
//  }
//
//private:
//  void Dfs1(int v) {
//    used_[v] = true;
//    for (size_t i = 0; i < graph_[v].size(); ++i) {
//      if (!used_[graph_[v][i]]) {
//        Dfs1(graph_[v][i]);
//      }
//    }
//    order_.push_back(v);
//  }
//  void Dfs2(int v) {
//    used_[v] = true;
//    component_.push_back(v);
//    for (size_t i = 0; i < tr_graph_[v].size(); ++i) {
//      if (!used_[tr_graph_[v][i]]) {
//        Dfs2(tr_graph_[v][i]);
//      }
//    }
//  }
//};
//
//int main() {
//  int n, m;
//  std::cin >> n >> m;
//  std::vector<std::vector<int>> graph(n, std::vector<int>());
//  std::vector<std::vector<int>> tr_graph(n, std::vector<int>());
//  int vertex1, vertex2;
//  for (int i = 0; i < m; ++i) {
//    std::cin >> vertex1 >> vertex2;
//    graph[--vertex1].emplace_back(--vertex2);
//    tr_graph[vertex2].emplace_back(vertex1);
//  }
//  Kosaraju comps = Kosaraju(n, graph, tr_graph);
//  comps.FindGroups();
//  comps.ToString();
//}