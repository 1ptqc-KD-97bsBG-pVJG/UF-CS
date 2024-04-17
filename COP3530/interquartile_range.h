#include <iostream>
#include <iomanip>

class Node {
public:
    int value;
    Node* next = nullptr;
};

Node* insertEnd(Node* head, int key)
{
    Node* temp = new Node();
    temp->value = key;
    if (head == nullptr)
    {
        head = temp;
    }
    else
    {
        Node* curr = head;
        while (curr->next != nullptr)
            curr = curr->next;
        curr->next = temp;
    }
    return head;
}

float interQuartile(Node* head)
{
    Node* ptrSlow = head;
    Node* ptrMedium = head->next;
    Node* ptrFast = head->next->next;
    Node* ptrFaster = head->next->next->next;
    // start count at 4 because given in assumptions
    int count = 4;

    // this hurts me but I couldn't get it working with 2 pointers :()
    while (ptrFaster != nullptr 
          && ptrFaster->next != nullptr 
          && ptrFaster->next->next != nullptr 
          && ptrFaster->next->next->next != nullptr 
          && ptrFaster->next->next->next->next != nullptr
          )
    {
        ptrSlow = ptrSlow->next;
        ptrMedium = ptrMedium->next->next;
        ptrFast = ptrFast->next->next->next;
        ptrFaster = ptrFaster->next->next->next->next;
        count += 4;
    }

    // check if count is not a multiple of 4 and adjust if necessary
    if (ptrFaster 
        && ptrFaster->next 
        && ptrFaster->next->next 
        && ptrFaster->next->next->next 
        && ptrFaster->next->next->next->next == nullptr
        ) {
        count += 3;
    }
    else if (ptrFaster 
            && ptrFaster->next 
            && ptrFaster->next->next 
            && ptrFaster->next->next->next == nullptr
            ) {
        count += 2;
    }
    else if (ptrFaster && ptrFaster->next && ptrFaster->next->next == nullptr) {
        count += 1;
    }

    // checks divisibility of list and decides whether to calculate or extract quatriles
    if (count % 4 == 0){
        return ((ptrFast->value + ptrFast->next->value)/ 2.00) - ((ptrSlow->value + ptrSlow->next->value) / 2.00);
    }
    else if (count % 4 == 1){
        return ((ptrFast->next->value + ptrFast->next->next->value)/ 2.00) - ((ptrSlow->value + ptrSlow->next->value) / 2.00);
    }
    else if (count % 4 == 2){
        return ptrFast->next->next->value - ptrSlow->next->value;
    }
    else if (count % 4 == 3){
        return ptrFast->next->next->next->value - ptrSlow->next->value;
    }
    

    return 0.00;
}