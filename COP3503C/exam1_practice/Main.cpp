#include <iostream>
#include <string>
#include "MyTodoList.h"
using namespace std;

int main()
{
   int input;
   cin >> input;
   
   if (input == 1)
   {
      MyTodoList defaultlist;
      defaultlist.display();
   }
   else if (input == 2)
   {
      MyTodoList defaultlist("COP 3503", 3);
      defaultlist.display();

   }
   else if (input == 3)
   {
      MyTodoList defaultlist("COP 3503", 4);
      
      defaultlist.push("lab1");
      defaultlist.push("lab2");
      defaultlist.push("lab3");
      defaultlist.push("lab4");
      defaultlist.display();
      
   }
   else if (input == 4)
   {
      MyTodoList defaultlist("COP 3503", 4);
      defaultlist.push("lab1");
      defaultlist.push("lab2");
      defaultlist.push("lab3");
      defaultlist.push("lab4");
      defaultlist.display();
   }
   else if (input == 5)
    {
        MyTodoList defaultlist("COP 3503", 4);
        defaultlist.push("lab1");
        defaultlist.push("lab2");
        defaultlist.display();
    }
   
   return 0;
}