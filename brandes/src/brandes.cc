#include <cstdarg>
#include <stack>
#include <list>
#include <queue>
#include <algorithm>
//#include <execution>

#include "src/brandes.h"


namespace algo {

int get_with_default(const std::unordered_map<int, int>& m,
    int key, int default_value) {
  auto it = m.find(key);
  if (it == m.end()) {
    return default_value;
  }

  return it->second;
}

std::unordered_map<int, float> Brandes::ProcessVertex(int vertex, const Graph& g) {
  std::unordered_map<int, float> centrality;
  centrality[vertex] = 0;

  const auto& adj = g.adj();  
  std::unordered_map<int, std::list<int>> P;
  std::stack<int> S;

  std::unordered_map<int, int> sigma;
  sigma[vertex] = 1; // sigma[t] = 0, t != s

  std::unordered_map<int, int> d;
  d[vertex] = 0; // d[t] = -1, t != s

  std::queue<int> Q;
  Q.push(vertex);

  while (!Q.empty()) {
    int v = Q.front();
    Q.pop();
    S.push(v);

    auto it = adj.find(v);
    if (it == adj.end()) {
      continue;
    }

    const auto& v_neighbors = it->second;

    for (const auto w : v_neighbors) {
      if (get_with_default(d, w, -1) < 0) {
        Q.push(w);
        d[w] = get_with_default(d, v, -1) + 1;
      }

      if (get_with_default(d, w, -1) == get_with_default(d, v, -1) + 1) {
        sigma[w] += sigma[v];
        P[w].push_back(v);
      }
    }
  }

  std::unordered_map<int, float> delta;
  while (!S.empty()) {
    auto w = S.top();
    S.pop();

    for (const auto v : P[w]) {
      delta[v] += (float(sigma[v]) / float(sigma[w])) * (1.0 + delta[w]);
    }
    
    if (w != vertex) {
      centrality[w] += delta[w];
    }
  }

  return centrality;
}

std::unordered_map<int, float> Brandes::Run(const Graph& graph) {
  std::unordered_map<int, float> centrality;
  
  for (const auto v : graph.adj()) {
    auto parital = ProcessVertex(v.first, graph);

    for (const auto& bc : parital) {
      centrality[bc.first] += bc.second;
    }
  }

  // normalize
  for (auto& bc : centrality) {
    bc.second /= 2.0;
  }

  return centrality;
}

} // namespace example
