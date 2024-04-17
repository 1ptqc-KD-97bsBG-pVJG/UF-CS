// #include <catch2/catch_test_macros.hpp>
// #include <iostream>

// #include "interquartile_range.h"

// using namespace std;

// // the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
// TEST_CASE("Example Test Name - Change me!", "[flag]"){
// 	// instantiate any class members that you need to test here
// 	int one = 1;

// 	// anything that evaluates to false in a REQUIRE block will result in a failing test 
// 	REQUIRE(one == 1); // fix me!

// 	// all REQUIRE blocks must evaluate to true for the whole test to pass
// 	REQUIRE(true); // also fix me!
// }

// TEST_CASE("Test 2", "[flag]"){
// 	// you can also use "sections" to share setup code between tests, for example:
// 	int one = 1;

// 	SECTION("num is 2") {
// 		int num = one + 1;
// 		REQUIRE(num == 2);
// 	};

// 	SECTION("num is 3") {
// 		int num = one + 2;
// 		REQUIRE(num == 3);
// 	};

// 	// each section runs the setup code independently to ensure that they don't affect each other
// }

// // you must write 5 unique, meaningful tests for credit on the testing portion of this quiz!
// TEST_CASE("Function: IQR with Negative Numbers", "[custom]") {
//     std::vector<int> v = {-10, -5, 0, 5, 10};
//     Node* head = nullptr;
//     for(int i: v)
//         head = insertEnd(head, i);

//     REQUIRE(interQuartile(head) == 15.00);
//     while (head != nullptr) {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }
// }

// TEST_CASE("Function: IQR with All Identical Elements", "[custom]") {
//     std::vector<int> v = {5, 5, 5, 5, 5, 5, 5};
//     Node* head = nullptr;
//     for(int i: v)
//         head = insertEnd(head, i);

//     REQUIRE(interQuartile(head) == 0.00);

//     while (head != nullptr) {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }
// }

// TEST_CASE("Function: IQR with Evenly Spaced Elements", "[custom]") {
//     std::vector<int> v = {10, 20, 30, 40, 50, 60, 70, 80};
//     Node* head = nullptr;
//     for(int i: v)
//         head = insertEnd(head, i);

//     REQUIRE(interQuartile(head) == 40.00);

//     while (head != nullptr) {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }
// }

// TEST_CASE("Function: IQR with Single Peak", "[custom]") {
//     std::vector<int> v = {1, 2, 3, 100, 101, 102, 103};
//     Node* head = nullptr;
//     for(int i: v)
//         head = insertEnd(head, i);

//     REQUIRE(interQuartile(head) == 100.00);

//     while (head != nullptr) {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }
// }

// TEST_CASE("Function: IQR with Large Range of Elements", "[custom]") {
//     std::vector<int> v = {1, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
//     Node* head = nullptr;
//     for(int i: v)
//         head = insertEnd(head, i);

//     REQUIRE(interQuartile(head) == 600.00);

//     while (head != nullptr) {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }
// }


// // the provided tests from edugator are below. Note that you must determine the correct output for the [output_hidden] tests yourself

// TEST_CASE("Function: IQR 1", "[given]") {
// 	std::vector<int> v = {2, 4, 4, 5, 6, 7, 8};
// 	Node* head = nullptr;
// 	for(int i: v)
// 		head = insertEnd(head, i);

// 	REQUIRE(interQuartile(head) == 3.00);
	
//     while (head != nullptr) 
//     {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }
// }

// TEST_CASE("Function: IQR 2", "[given]") {
// 	std::vector<int> v = {1, 2, 3, 4};
// 	Node* head = nullptr;
// 	for(int i: v)
// 		head = insertEnd(head, i);

// 	REQUIRE(interQuartile(head) == 2.00);
	
//     while (head != nullptr) 
//     {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }
// }


//  TEST_CASE("Function: IQR 3", "[output_hidden]") {
// 	std::vector<int> v = {1, 8, 15, 43, 82, 101, 110, 2456, 55345, 137556};
// 	Node* head = nullptr;
// 	for(int i: v)
// 		head = insertEnd(head, i);

// 	REQUIRE(interQuartile(head) == 2441.00);
	
//     while (head != nullptr) 
//     {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }
// } 

//  TEST_CASE("Function: IQR 4", "[output_hidden]") {
// 	std::vector<int> v = {2, 4, 4, 5, 6, 7, 8, 9, 10};
// 	Node* head = nullptr;
// 	for(int i: v)
// 		head = insertEnd(head, i);

// 	REQUIRE(interQuartile(head) == 4.5);
	
//     while (head != nullptr) 
//     {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }
// } 

// TEST_CASE("Function: IQR 5", "[output_hidden]") {
// 	std::vector<int> v = {1, 8, 15, 43, 82, 101, 110, 2456, 55345, 137556, 137576};
// 	Node* head = nullptr;
// 	for(int i: v)
// 		head = insertEnd(head, i);

// 	REQUIRE(interQuartile(head) == 55330);
	
//     while (head != nullptr) 
//     {
//         Node* temp = head;
//         head = head->next;
//         delete temp;
//     }
// } 
