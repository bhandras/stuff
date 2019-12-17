#include <array>
#include <utility>

#include "src/brandes.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace algo {
namespace {

using ::testing::Pair;
using ::testing::UnorderedElementsAre;

TEST(BrandesTest, TestEmpty) {
  Graph g;
  Brandes brandes;

  auto centrality = brandes.Run(g);
  EXPECT_TRUE(centrality.empty());
}

TEST(BrandesTest, TestOneEdge) {
  Graph g;
  g.AddEdge(1, 2);

  Brandes brandes;
  auto centrality = brandes.Run(g);
  EXPECT_THAT(centrality,
      UnorderedElementsAre(
        Pair(1, 0.0), Pair(2, 0.0)
      )
  );
}

TEST(BrandesTest, TestOneCentralNode) {
  Graph g;
  g.AddEdge(1, 2);
  g.AddEdge(2, 3);

  Brandes brandes;
  auto centrality = brandes.Run(g);
  EXPECT_THAT(centrality,
      UnorderedElementsAre(
        Pair(1, 0.0), Pair(2, 1.0), Pair(3, 0.0)
      )
  );
}

TEST(BrandesTest, TestWithLargerGraph) {
  const std::array<std::pair<int, int>, 14> kTestGraph = {{
    {0, 1}, {0, 2}, {0, 3}, {1, 2}, {2, 3}, {3, 4}, {3, 5},
    {4, 5}, {4, 6}, {4, 7}, {5, 6}, {5, 7}, {6, 7}, {6, 8}
  }};

  Graph g;
  for (auto edge : kTestGraph) {
    g.AddEdge(edge.first, edge.second);
  }

  Brandes brandes;
  const auto centrality = brandes.Run(g);
  EXPECT_THAT(centrality,
      UnorderedElementsAre(
        Pair(0, 3.0), Pair(1, 0.0), Pair(2, 3.0), Pair(3, 15.0),
        Pair(4, 6.0), Pair(5, 6.0), Pair(6, 7.0), Pair(7, 0.0), Pair(8, 0.0)
      )
  );
}



} // namespace
} // namespace algo
