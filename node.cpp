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
private:
	int val;
	Node* next;
    Node(const int& v, Node* parent = nullptr):val(v), next(nullptr){
        if (parent) parent -> next = this;
    }
public:
	static Node* CreateList(const std::vector<int> &ru);
	static Node* CreateListUsingNodes(Node* s0, Node* s1);	
	
	bool IsOrdered(Node* ps);     
};
Node* Node::CreateList(const std::vector<int> &ru){

    Node* head = nullptr;
    Node* parent = nullptr;
    for (auto r: ru){

        auto n = new Node(r,parent);
        if (!parent) head = parent = n;
        else parent = n;
    }
    return head;
}
Node* Node::CreateListUsingNodes(Node* s0, Node* s1)
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
bool Node::IsOrdered(Node* ps){

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
                {Node::CreateList({0,2,4,5,8}),Node::CreateList({-11,3,4,10,23})},
                {Node::CreateList({}),Node::CreateList({12,130,1000})},
                {Node::CreateList({}),Node::CreateList({})},
                {Node::CreateList({-1,0,101}),Node::CreateList({})},
                {Node::CreateList({1,2,3,4,5,6}),Node::CreateList({10,11,12,13,14})},
                {Node::CreateList({10,12,18,23}),Node::CreateList({9,14,16,25})},
                {Node::CreateList({0,0,130,1000}),Node::CreateList({1,1,1,1,1})},
                {Node::CreateList({}),Node::CreateList({8,12,14,14})}
        };
        for (auto&t : ts){
            auto mrg = Node::CreateListUsingNodes(t.first,t.second);
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
        EXPECT_EQ(result->IsOrdered(result), true);
    }
}
} //testingFixture
int main(int argc, char **argv){


    ::testing::InitGoogleTest(&argc,argv);
    if (RUN_ALL_TESTS())
    {
    	std::cout << "*** Test program failed ***\n";
    }
    else 
    {
    	std::cout << "*** Test program success ***\n";
    }
}
