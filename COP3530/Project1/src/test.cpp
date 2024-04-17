// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"
// #include "AVLTree.h"

// #include <vector>
// #include <algorithm>
// #include <cstdlib>

// std::string generateRandomString(size_t length) {
//     const char charset[] =
//         "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//         "abcdefghijklmnopqrstuvwxyz";
//     std::string random_string;
//     for (size_t i = 0; i < length; i++) {
//         random_string += charset[rand() % (sizeof(charset) - 1)];
//     }
//     return random_string;
// }

// std::string generateUniqueId(const std::vector<std::string> &existingIds) {
//     std::string id;
//     do {
//         id = std::to_string(rand() % 90000000 + 10000000);
//     } while (std::find(existingIds.begin(), existingIds.end(), id) != existingIds.end());
//     return id;
// }

// TEST_CASE("Incorrect Commands", "[AVLTree]") {
//     AVLTree tree;

//     SECTION("Insert with non-numeric ID") {
//         REQUIRE_FALSE(tree.insertNode("Alice", "ABCDEF12"));
//     }

//     SECTION("Insert with incorrect ID length") {
//         REQUIRE_FALSE(tree.insertNode("Bob", "123456"));
//     }

//     SECTION("Insert with invalid name characters") {
//         REQUIRE_FALSE(tree.insertNode("C@rl3", "12345678"));
//     }

//     SECTION("Remove non-existent ID") {
//         REQUIRE_FALSE(tree.removeNode("99999999"));
//     }

//     SECTION("Search for non-existent ID") {
//         REQUIRE(tree.searchId("88888888").empty());
//     }
// }

// TEST_CASE("Edge Cases", "[AVLTree]") {
//     AVLTree tree;
//     std::vector<std::string> ids;

//     ids.push_back(tree.insertNode("Duplicate Name", "12345678"));
//     ids.push_back(tree.insertNode("Duplicate Name", "23456789"));

//     SECTION("Remove non-existent node") {
//         REQUIRE_FALSE(tree.removeNode("87654321"));
//     }

//     SECTION("Search for a name with multiple instances") {
//         auto searchResults = tree.searchName("Duplicate Name");
//         REQUIRE(searchResults.size() == 2);
//     }

//     SECTION("Insert a node with an existing ID") {
//         REQUIRE_FALSE(tree.insertNode("New Name", ids[0]));
//     }
// }

// TEST_CASE("Rotation Cases", "[AVLTree]") {
//     AVLTree tree;

//     SECTION("Left Rotation") {
//         tree.insertNode("Node1", "10000000");
//         tree.insertNode("Node2", "20000000");
//         tree.insertNode("Node3", "30000000");

//         REQUIRE(tree.isBalanced());
//     }

//     SECTION("Right Rotation") {
//         tree.insertNode("Node3", "30000000");
//         tree.insertNode("Node2", "20000000");
//         tree.insertNode("Node1", "10000000");

//         REQUIRE(tree.isBalanced());
//     }


//     SECTION("Left-Right Rotation") {
//         tree.insertNode("Node3", "30000000");
//         tree.insertNode("Node1", "10000000");
//         tree.insertNode("Node2", "20000000");

//         REQUIRE(tree.isBalanced());
//     }

//     SECTION("Right-Left Rotation") {
//         tree.insertNode("Node1", "10000000");
//         tree.insertNode("Node3", "30000000");
//         tree.insertNode("Node2", "20000000");

//         REQUIRE(tree.isBalanced());
//     }
// }

// TEST_CASE("Deletion Cases", "[AVLTree]") {
//     AVLTree tree;
//     tree.insertNode("Node1", "10000000");
//     tree.insertNode("Node2", "20000000");
//     tree.insertNode("Node3", "30000000");

//     SECTION("Delete a node with no children") {
//         REQUIRE(tree.removeNode("30000000"));
//         REQUIRE(tree.isBalanced());
//     }

//     SECTION("Delete a node with one child") {
//         REQUIRE(tree.removeNode("20000000"));
//         REQUIRE(tree.isBalanced());
//     }

//     SECTION("Delete a node with two children") {
//         tree.insertNode("Node4", "40000000");
//         REQUIRE(tree.removeNode("20000000"));
//         REQUIRE(tree.isBalanced());
//     }
// }

// TEST_CASE("Insert and Remove Bulk Nodes", "[AVLTree]") {
//     AVLTree tree;
//     std::vector<std::string> ids;

//     // Insert 100 nodes
//     for (int i = 0; i < 100; ++i) {
//         std::string id = generateUniqueId(ids);
//         ids.push_back(id);
//         std::string name = generateRandomString(5);
//         REQUIRE(tree.insertNode(name, id));
//     }

//     // Randomly remove 10 nodes
//     std::random_shuffle(ids.begin(), ids.end());
//     for (int i = 0; i < 10; ++i) {
//         REQUIRE(tree.removeNode(ids[i]));
//     }

//     REQUIRE(tree.isBalanced());
// }
