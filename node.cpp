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


struct Node {
	int val;
	Node* next;
    Node(const int& v, Node* parent = nullptr):val(v), next(nullptr){
        if (parent) parent -> next = this;
    }
};
Node* createList(std::vector<int> u){

    Node* head = nullptr;
    Node* parent = nullptr;
    for (int& r: u){

        auto n = new Node(r,parent);
        if (!parent) head = parent = n;
        else parent = n;
    }
    return head;
}
Node* merge(Node* s0, Node* s1)
{

	Node* nlist = nullptr;
	Node* lastptr = nullptr;
	while (s0 && s1)
	{

		Node* newnode = new Node(s0->val < s1->val ? s0->val : s1->val, lastptr);
		if (!lastptr) nlist = lastptr = newnode;
        else lastptr = newnode;
        if (s0->val < s1->val) s0 = s0 ->next;
		else s1 = s1 ->next;

	}

    Node*aux = s0 ? s0 : s1;
	while (aux){
		Node* newnode = new Node(aux->val,lastptr);
		aux = aux->next;
	}
	return nlist;
}
bool isOrdered(Node* ps){

    if(!ps) return true;
    bool first = true;
    int lastvalue = 0;


    for (auto elem = ps; elem; elem = elem->next){
        if (first){
            lastvalue = elem->val;
            first = false;
            continue;
        }
        if (lastvalue > elem->val) return false;
    }
    return true;

}

using test = std::pair<Node*, Node*>;
using tests = std::vector<test>;

namespace {
class NodeTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        tests ts{
                {createList({0,2,4,5,8}),createList({-11,3,4,10,23})},
                {createList({}),createList({12,130,1000})},
                {createList({}),createList({})},
                {createList({-1,0,101}),createList({})},
                {createList({1,2,3,4,5,6}),createList({10,11,12,13,14})},
                {createList({10,12,18,23}),createList({9,14,16,25})},
                {createList({0,0,130,1000}),createList({1,1,1,1,1})},
                {createList({}),createList({8,12,14,14})}
        };
        for (auto&t : ts){
            auto mrg = merge(t.first,t.second);
            results.push_back(mrg);
        }
        for (auto&t : ts){
            free(t.first);
            free(t.second);
        }
    }
    std::vector<Node*>results;

    virtual void TearDown()
    {
        for(auto&result : results){
            free(result);
        }
    }
};

TEST_F(NodeTest, mergerOrdered)
{
    for(auto& result: results) {
        EXPECT_EQ(isOrdered(result), true);
    }
}
} //testingFixture
int main(int argc, char **argv){


    ::testing::InitGoogleTest(&argc,argv);
    RUN_ALL_TESTS();

}
