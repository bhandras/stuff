#ifndef _BRANDES_H_
#define _BRANDES_H_

#include <unordered_map>
#include <set>

namespace algo {

class Graph {
public:
  void AddEdge(int u, int v) {
    adj_[u].insert(v);
    adj_[v].insert(u);
  }

  const std::unordered_map<int, std::set<int>>& adj() const { return adj_; }

private:
  std::unordered_map<int, std::set<int>> adj_;
};


class Brandes {
public:
  std::unordered_map<int, float> Run(const Graph& graph);

private:
  std::unordered_map<int, float> ProcessVertex(int vertex, const Graph& graph);
};

} // namespace example

#endif // _BRANDES_H_
