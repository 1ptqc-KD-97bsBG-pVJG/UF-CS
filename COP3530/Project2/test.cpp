// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"
// #include "Graph.h"

// TEST_CASE("Initialization of Graph", "[Graph]") {
//     Graph graph;

//     SECTION("Graph is initialized empty") {
//         REQUIRE(graph.pageRank(0).empty());
//     }
// }

// TEST_CASE("Adding Edges and Calculating PageRank", "[Graph]") {
//     Graph graph;

//     SECTION("Add single edge and perform PageRank") {
//         graph.addEdge("page1.com", "page2.com");
//         auto rank = graph.pageRank(1);
//         REQUIRE(!rank.empty());
//     }

//     SECTION("Add multiple edges and perform PageRank") {
//         graph.addEdge("page1.com", "page2.com");
//         graph.addEdge("page2.com", "page3.com");
//         auto rank = graph.pageRank(1);
//         REQUIRE(!rank.empty());
//     }

//     SECTION("Add circular edges and perform PageRank") {
//         graph.addEdge("page1.com", "page2.com");
//         graph.addEdge("page2.com", "page1.com");
//         auto rank = graph.pageRank(2);
//         REQUIRE(!rank.empty());
//     }
// }

// TEST_CASE("PageRank with Zero Iterations", "[Graph]") {
//     Graph graph;
//     graph.addEdge("page1.com", "page2.com");
//     graph.addEdge("page2.com", "page3.com");

//     SECTION("Zero iterations should return initial rank values") {
//         auto rank = graph.pageRank(0);
//         REQUIRE(rank.find("page1.com") != rank.end());
//         REQUIRE(rank["page1.com"] == Approx(1.0 / 3).epsilon(0.01));
//     }
// }

// TEST_CASE("PageRank with Convergence", "[Graph]") {
//     Graph graph;
//     graph.addEdge("page1.com", "page2.com");
//     graph.addEdge("page2.com", "page3.com");
//     graph.addEdge("page3.com", "page1.com");

//     SECTION("Convergence after a large number of iterations") {
//         auto rank = graph.pageRank(10000);
//         REQUIRE(rank["page1.com"] > 0);
//         REQUIRE(rank["page2.com"] > 0);
//         REQUIRE(rank["page3.com"] > 0);
//     }
// }

// TEST_CASE("PageRank with Dangling Nodes", "[Graph]") {
//     Graph graph;
//     graph.addEdge("page1.com", "page2.com");

//     SECTION("Handling of nodes with no outgoing edges") {
//         auto rank = graph.pageRank(1);
//         REQUIRE(rank["page1.com"] > 0);
//         REQUIRE(rank["page2.com"] > 0);
//     }
// }
