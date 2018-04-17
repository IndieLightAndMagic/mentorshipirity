/*
Precondition: at least one of the lists must be not empty.
Comments:
Put up a new list with both lists integers.
To build the list set up two pointers, one for each list, these pointers will iterate through the lists.
Each iteration compared the values pointed by each pointer, the lesser would create a new Node in memory, would copy the lesser value and will increment the lesser pointer by one.
When one of the the pointers points to nullptr, stop the iteration through the lists.
Select the non-nullptr left and


Unitary tests to make:

High Level tests:
Que se solapen
Que tengan elementos repetidos
…….

Test cases:
[0,2,4,5,8] [-11,3,4,10,23]
[][12,130,1000]
[][]
[-1,0,101][]
[1,2,3,4,5,6][10,11,12,13,14]
[10,12,18,23][9,14,16,25]
[0,0,130,1000][1,1,1,1,1]
[][8,12,14,14]

Google tests. (codigo)
*/
#include <vector>
#include <iostream>
#include "gtest/gtest.h"


struct Node
{
private:
    int val;
    Node* next;
    Node(const int& v, Node* parent = nullptr):val(v), next(nullptr)
    {
        if (parent) parent -> next = this;
    }
public:
    static Node* CreateList(const std::vector<int> &ru);
    static Node* CreateListUsingNodes(Node* s0, Node* s1);

    bool IsOrdered(Node* ps) const;
};
