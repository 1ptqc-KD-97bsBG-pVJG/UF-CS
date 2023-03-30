#include <iostream>
#include <string>
using namespace std;

// You will create here a class called: MyTodoList
// This list will have four elements:
// 1) an array of strings called "list"
// 2) a string which will store the name of the list. This variable should be called "nameoflist"
// 3) an integer to store the** number of elements** in the list "numberofitems"
// 4) an integer to store the size of the array called "size"

// For this exercise:

// 1) create the default constructor for the class which will construct an instance of the class with a list of size = 1, the name of the list equals to "list_1", and the "numberofitems" equals to zero. In addition the all list element should be initialized to "not provided"

// 2) A display function which will print the following information:
// name: "Whatever the name of the list is"
// number of items: numbeofitems
// item1 item2 item3 This function should not return anything.

// 3) create the parametrized constructor of the class in which the user can provide the name of their list and the number of items they want to put in their list. This constructor should allocate memory of the size provided by the user in the heap. In addition the all list element should be initialized to "not yet provided".

// 4) create a push function that will take a string and will assign the string to the next available location in the array following a stack data structure. This function should return the element pushed. This function should increase the number of items by one.


// Note: All functions should be public


class MyTodoList{
   // TODO 1: elements of my list: nameoflist, numberofitems, list
   private:
      string list[1];
      string nameoflist;
      int numberofitems;
      int size;
      
   // TODO 2: default constructor
   public:
      MyTodoList() {
         list[1] = { "not provided" };
         nameoflist = "list_1";
         numberofitems = 0;
      };
   
   // TODO 3: parametrized constructor
   // 3) create the parametrized constructor of the class in which the user can provide the name of their list and the number of items they want to put in their list. This constructor should allocate memory of the size provided by the user in the heap. In addition the all list element should be initialized to "not yet provided".
    MyTodoList(string nameoflist, int size) {
      this->nameoflist = nameoflist;
      this->size = size;
      numberofitems = size;
      list[size] = { "not yet provided" };
    };
   
   // TODO 4: display function
    void display();
   
   // TODO 5: push function
    string push(string item);
   
   
};